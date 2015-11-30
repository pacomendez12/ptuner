#include <sound_system/sound_system.h>
#include <util/complex.h>
#include <sound_system/definitions.h>

#include <cmath>

#ifndef TUNER_H

#define TUNER_H

using namespace Sound_system;


#define TUNER_DEFAULT_SOUND_SYSTEM ALSA

#define TAG "TUNER"

enum {
	/* it needs at least 16384 samples to get at most ~8000 hz frequency */
	TUNER_SAMPLES = 16384,
	DEFAULT_OVERSAMPLING = 64,
	DEFAULT_DOWNSAMPLE = true,
};


enum TunerStatus {
	TUNING,
	NOT_TUNING
};


enum Filters {
	BUTTERWORTH,
};

class Tuner {
	private:
	sound_system * sound;
	s_system_t sound_system_type;
	TunerStatus status;

	double buffer[TUNER_SAMPLES];
	complex complex_buffer[TUNER_SAMPLES];
	double hanWindow[TUNER_SAMPLES];


	/* parameters from sound system */
	unsigned int sample_rate;
	int sound_system_buffer_size;

	unsigned int oversampling;
	unsigned int peak_number;

	/* the goal */
	double frequency;

	/* dmax is used for normalization */
	double dmax;


	/* Tnuning parameters */
	bool useFilter;
	Filters filter;
	bool downsample;


	/* valid data from fft are in the size of 0 - buffer lenght * 3 /8 */
#define  OUTPUT_BUFFER_SIZE TUNER_SAMPLES * 3 / 8
	double fps = sample_rate;

	/* auxiliar buffers */
	double xa[OUTPUT_BUFFER_SIZE];
	double xp[OUTPUT_BUFFER_SIZE];
	double xf[OUTPUT_BUFFER_SIZE];
	double dx[OUTPUT_BUFFER_SIZE];


	/* buffers for downsampling */
	double x2[OUTPUT_BUFFER_SIZE / 2];
	double x3[OUTPUT_BUFFER_SIZE / 3];
	double x4[OUTPUT_BUFFER_SIZE / 4];
	double x5[OUTPUT_BUFFER_SIZE / 5];






	public:
	Tuner();
	Tuner(s_system_t);
	
	~Tuner();

	void startTuning();
	void stopTuning();


	void callbackData(double * data, int size_data, void * dummy);


	/* main methods */
	void postFftProccess(complex * complex_buffer, int buffer_size);
	void downSampling();
	void findFrequency();


	double getFundamentalFrequency() {
		return frequency;
	}


};



#define DOWNSAMPLING_METHOD(n) \
	for (int i = 0; i < ARRAY_SIZE(x##n); i++) { \
		x##n[i] = 0.0; \
		for (int j = 0; j < n; j++) { \
			x##n[i] += xa[(i * n) + j] / (double)n; \
		} \
	}\

#endif /* end of include guard: TUNER_H */
