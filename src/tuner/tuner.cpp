#include <tuner/tuner.h>
#include <tuner/filter.h>
#include <fft/fft.h>
#include <util/array.h>

static Tuner * tunerPtr;

void
callback(double * data, int data_size, void * arg)
{
	tunerPtr->callbackData(data, data_size, arg);
}

void
Tuner::callbackData(double * data, int data_size, void * arg)
{
	//data received from sound system
	
	/* once que have de new data it needs to reorganize it,
	and memmove is perfect for this task */
	int size_data_keept = (TUNER_SAMPLES - data_size) * sizeof(double);
	memmove(buffer, buffer + data_size, size_data_keept);
	
	/* copy data to buffer array, the filter also have to copy de data */
	if (useFilter && filter == BUTTERWORTH) {
		Filter::Butterworth(data, data_size, buffer, TUNER_SAMPLES);
	} else {
		memcpy(buffer + size_data_keept / sizeof(double), data, data_size 
				* sizeof(double));
	}


	/* now buffer has the new data */

	/* it's time to apply the window and normalize buffer */

	if (dmax < 4096.0) {
		dmax = 4096.0;
	}

	double normalization = dmax;
	dmax = 0.0;

	for (int i = 0; i < TUNER_SAMPLES; i++) {
		dmax = dmax < fabs(buffer[i])? fabs(buffer[i]): dmax;
		complex_buffer[i].setReal(buffer[i] / normalization * hanWindow[i]);
	}

	/* calculatin Fourier transform */
	Fft::fft(complex_buffer, TUNER_SAMPLES);

	/* post processing fft */
	postFftProccess(complex_buffer, data_size);

	/* down sampling */
	if (downsample)
		downSampling();

	for (int i = 0; i < OUTPUT_BUFFER_SIZE; i++) {
		//std::cout << dx[i] <<" ";
		/*if (data[i] != buffer[size_data_keept / sizeof(double) + i]) {
			well = false;
			break;
		}*/
	}
	//std::cout << std::endl;

}


void
Tuner::postFftProccess(complex * complex_buffer, int data_read)
{
	double expected = M_PI * 2.0 * (double)data_read / TUNER_SAMPLES;

	for (int i = 1; i < OUTPUT_BUFFER_SIZE; i++) {
		double real = complex_buffer[i].real;
		double imag = complex_buffer[i].imag;

		xa[i] = hypot(real, imag);

		/* calculing frequency */
		double p = atan2(imag, real);

		double dp = xp[i] - p;
		xp[i] = p;

		dp -= (double)i * expected;

		int qpd = dp / M_PI;

		if (qpd >= 0) {
			qpd += qpd & 1;
		} else {
			qpd -= qpd & 1;
		}

		dp -= M_PI * (double)qpd;


		double df =  oversampling * dp / (2.0 * M_PI);


		xf[i] = (i * fps + df * fps);

		dx[i] = xa[i] - xa[i - 1];
	}
}


void
Tuner::downSampling()
{
	/* all work is done based on members bufers x2, x3, x4, x5 */
	DOWNSAMPLING_METHOD(2); 
	DOWNSAMPLING_METHOD(3);
	DOWNSAMPLING_METHOD(4);
	DOWNSAMPLING_METHOD(5);

	for (int i = 1; i < ARRAY_SIZE(xa); i++) {
		if (i < ARRAY_SIZE(x2))
			xa[i] += x2[i];

		if (i < ARRAY_SIZE(x3))
			xa[i] += x3[i];

		if (i < ARRAY_SIZE(x4))
			xa[i] += x4[i];

		if (i < ARRAY_SIZE(x5))
			xa[i] += x5[i];

		dx[i] = xa[i] - xa[i - 1];
	}
}


Tuner::Tuner() : Tuner(TUNER_DEFAULT_SOUND_SYSTEM) {}


Tuner::Tuner(s_system_t sst) 
{
	sound_system_type = sst;
	sound = new sound_system(sst, callback);

	/* get real values from sound system */
	sound_system_buffer_size = sound->getSoundSystemBufferSize();
	sample_rate = sound->getSampleRate();
	fps = sample_rate / TUNER_SAMPLES;
	oversampling = DEFAULT_OVERSAMPLING; // we need to use a variable here;
	peak_number = 3;
	downsample = DEFAULT_DOWNSAMPLE;


	/* enable filter by default */
	useFilter = true;
	//useFilter = false;
	filter = BUTTERWORTH;


	/* Han window */
	for (int i = 0; i < TUNER_SAMPLES; i++) {
		hanWindow[i] = 0.5 * (1 - cos(2 * M_PI * i / (TUNER_SAMPLES - 1.0)));
	}

	dmax = 0;
	
	/* global Tuner ptr have to be able to call the 
	 * tuner object callbackData */
	tunerPtr = this;
}

Tuner::~Tuner()
{
	if (status == TUNING) {
		stopTuning();
	}
	delete sound;
	sound = NULL;
	tunerPtr = NULL;
}


void
Tuner::startTuning()
{
	status = TUNING;
	/* init capturing from sound system */
	sound->record();
}

void
Tuner::stopTuning()
{
	status = NOT_TUNING;
	sound->stop();
}
