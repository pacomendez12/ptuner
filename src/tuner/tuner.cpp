#include <tuner/tuner.h>
#include <tuner/filter.h>
#include <tuner/signal.h>
#include <fft/fft.h>
#include <util/array.h>
#include <util/mem.h>

static Tuner * tunerPtr;

using namespace std;
void
callback(double * data, int data_size, void * arg)
{
	tunerPtr->callbackData(data, data_size, arg);
}

void
Tuner::callbackData(double * data, int data_size, void * arg)
{
	/* data received from sound system, copy as fast as posible */
	memcpy(buffer, data, data_size * sizeof(double));


	/* apply decimation to have better results */
	decimate();

	/* finding fundamental frequency */
	findFrequency();
}


void
Tuner::decimate()
{
	int data_size = sound_system_buffer_size;
	int dec_out_len = 1 + (data_size - (dii + 1)) / oversampling;

	//printf("dec_out_len = %d\n", dec_out_len);
	buffer_mutex.lock();

	if (complete_buffer_size > dec_out_len) {
		/* once que have de new data it needs to reorganize it,
		   and memmove is perfect for this task */
		unsigned int size_data_moved = (complete_buffer_size - dec_out_len);
		memmove(complete_buffer, complete_buffer + dec_out_len,
				size_data_moved * sizeof(double));
		//printf("moved = %u\n", size_data_moved);
	}

	if (oversampling > 1) {
		double * in = buffer;
		double * out = complete_buffer + (complete_buffer_size - dec_out_len);

		/* filtering data */
		/* the input is also de output for the filter */
		filter->filter(data_size, in, in);

		/* downsampling */
		for (int doi = 0; dii < data_size; doi++, dii += oversampling) {
			out[doi] = in[dii];
//			cout << out[doi] << " ";
		}
//		cout << endl;
		dii -= data_size;
	} else {
		memcpy(complete_buffer + complete_buffer_size - dec_out_len, buffer,
				dec_out_len * sizeof(double));
	}
	/*for (int i = 0; i < 10; i++) {
		printf("%lf ", complete_buffer[i]);
	}
	cout << endl << endl << endl;*/
	buffer_mutex.unlock();
}

void
Tuner::findFrequency()
{
	/* applying window */
	for (int i = 0; i < fft_size; i++) {
		complete_buffer_with_window[i] =
			complete_buffer[complete_buffer_size - fft_size + i] * han_fft[i];
	}

	/* do fft */
	fft->fft(complete_buffer_with_window, complex_buffer, fft_size);

	for (int i = 0; i < fft_size / 2; i++) {
		fft_spd_buffer[i] = (complex_buffer[i].real * complex_buffer[i].real +
				complex_buffer[i].imag * complex_buffer[i].imag) * _1_n2;
	}

	
	/* copying representable data (that could be in a chart */
	memcpy(representable_data, fft_spd_buffer, fft_size / 2 * sizeof(double));

	/* I thing the nerual network will use representable data        ****** */ 

	fft_spd_diff_buffer[0] = 0.0;
	for (int i = 1; i < fft_size / 2 - 1; i++) {
		fft_spd_diff_buffer[i] = 2.0 * fft_spd_buffer[i] - fft_spd_buffer[i - 1] -
			fft_spd_buffer[i + 1];
		if (fft_spd_diff_buffer[i] < 0) {
			fft_spd_diff_buffer[i] = 0.0;
		}
	}
	/*for (int i = 0; i < 10; i++) {
		printf("%lf ", fft_spd_diff_buffer[i]);
	}
	cout << endl << endl;*/

	/* look for peak */
	int m = signal->get_fundamental_peak(fft_spd_buffer,
										fft_spd_diff_buffer, fft_size / 2);
	std::cout << "M = " << m << endl;
	double w = (m - 1) * delta_fft;

	if (m == (signed) fft_size / 2) {
		/* setting frequency to 0 because there is no a good signal */
		frequency = 0.0;
	} else {
		/* there a a frequency to show */
		const unsigned int n_dft = 2;
		double dw = delta_fft;

		for (int k = 0; k < n_dft; k++) {
			dw = 2.0 * dw / (n_dft - 1);

			if (0 == k) {
				fft->fft_spd(complete_buffer_with_window, fft_size, w + dw, dw,
						spd_dft + 1, dft_size - 2);
				spd_dft[0] = spd_dft[m - 1];
				spd_dft[dft_size - 1] = spd_dft[m + 1];
			} else {
				fft->fft_spd(complete_buffer_with_window, fft_size, w, dw,
						spd_dft, dft_size);
			}

			m = signal->get_max(spd_dft, dft_size);
			w +=  (m - 1) * dw;
		}

		w += dw;

		/* window again */
		for (int i = 0; i < complete_buffer_size; i++) {
			windowed_buffer[i] = complete_buffer[i] * hanWindow[i];
		}

		/* Newtown Raphson */
		const unsigned int n_iter = 10;
		double wk = -1.0e5;
		double wkm1 = m;
		double d1, d2;


		for (int k = 0; k < n_iter && fabs(wk - wkm1) > 1.0e-8; k++) {
			wk = wkm1;

			fft->fft_spd_diff(windowed_buffer, complete_buffer_size, wk, d1, d2);
			wkm1 = wk - d1 / d2;
		}

		w = wkm1;
		frequency = (w * sample_rate) / (2.0 * M_PI * oversampling);
		printf("Freq = %lf\n", frequency);
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
	oversampling = DEFAULT_OVERSAMPLING; // we need to use a variable here;
	peak_number = 3;
	downsample = DEFAULT_DOWNSAMPLE;
	dft_size = DEFAULT_DFT_SIZE;
	time_window = 0.5; /* 0.5 seconds */
	complete_buffer_size = (unsigned int) ceil(sample_rate * 
											time_window / oversampling);
	fft_size = 512;
	delta_fft = M_PI * 2.0 / fft_size;
	_1_n2 = 1.0 / (fft_size * fft_size);
	dii = 0;


	/* instanciate fft object */
	fft = new Fft(this);
	signal = new Signal(this);

	/* initializing buffers */
	complete_buffer = new double[complete_buffer_size]();
	windowed_buffer = new double[complete_buffer_size]();
	hanWindow = new double[complete_buffer_size]();
	complete_buffer_with_window = new double[fft_size]();
	buffer = new double[sound_system_buffer_size]();
	han_fft = new double[fft_size]();
	complex_buffer = new complex[fft_size](); // i'm not sure about size
	fft_spd_buffer = new double[fft_size / 2]();
	fft_spd_diff_buffer = new double[fft_size]();
	spd_dft = new double[dft_size]();
	representable_data = new double[fft_size / 2]();


	/* enable filter by default */
	useFilter = true;
	//filter = BUTTERWORTH;
	filter_type = CHEBY_TYPE;


	/* Initialize filter */
	filter = new Filter(filter_type, oversampling);


	/* Han window */
	for (int i = 0; i < complete_buffer_size; i++) {
		/* han */
//		hanWindow[i] = 0.5 * (1 - cos(2 * M_PI * i / (complete_buffer_size - 1.0)));
		/* hamming */
		hanWindow[i] = 0.53836 - 0.46164 * cos((2 * M_PI * i) / (complete_buffer_size - 1.0));
	}

	/* Han for fft */
	for (int i = 0; i < fft_size; i++) {
		//han_fft[i] = 0.5 * (1 - cos(2 * M_PI * i / (fft_size - 1.0)));
		han_fft[i] = 0.53836 - 0.46164 * cos((2 * M_PI * i) / (fft_size - 1.0));
	}

	/* global Tuner ptr have to be able to call the 
	 * tuner object callbackData */
	tunerPtr = this;
}

Tuner::~Tuner()
{
	if (status == TUNING) {
		stopTuning();
	}

	safe_delete(sound);
	safe_delete(filter);
	safe_delete(signal);
	safe_delete_array(complete_buffer);
	safe_delete_array(windowed_buffer);
	safe_delete_array(complete_buffer_with_window);
	safe_delete_array(buffer);
	safe_delete_array(hanWindow);
	safe_delete_array(han_fft);
	safe_delete_array(fft_spd_buffer);
	safe_delete_array(fft_spd_diff_buffer);

	safe_delete(fft);

	tunerPtr = NULL;
}


void
Tuner::startTuning()
{
	status = TUNING;
	/* start capture from sound system */
	sound->record();
}

void
Tuner::stopTuning()
{
	status = NOT_TUNING;
	sound->stop();
}
