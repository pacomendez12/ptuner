#include <tuner/tuner.h>
#include <tuner/filter.h>
#include <fft/fft.h>

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

	/* valida data from fft are in the size of 0 - buffer length * 3 / 8 */
	const int output_buffer_size = TUNER_SAMPLES * 3 / 8;


	double xa[output_buffer_size];
	double xp[output_buffer_size];
	double xf[output_buffer_size];
	double dx[output_buffer_size];
	double expected = M_PI * 2.0 * (double)data_size / TUNER_SAMPLES;

	for (int i = 1; i < output_buffer_size; i++) {
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
	}

	bool well = true;
	std::cout << "Receiving " << data_size << " bytes from sound system" << std::endl;
	for (int i = 0; i < data_size; i++) {
		std::cout << data[i] <<" ";
		/*if (data[i] != buffer[size_data_keept / sizeof(double) + i]) {
			well = false;
			break;
		}*/
	}
	//std::cout << well << std::endl;
	std::cout << std::endl;

}


Tuner::Tuner() : Tuner(TUNER_DEFAULT_SOUND_SYSTEM) {}


Tuner::Tuner(s_system_t sst) 
{
	sound_system_type = sst;
	sound = new sound_system(sst, callback);
//	sound.select_sound_system(sst);
//	sound.setCallback(callback);
	/* get real values from sound system */
	sound_system_buffer_size = sound->getSoundSystemBufferSize();
	sample_rate = sound->getSampleRate();


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
