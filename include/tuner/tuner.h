#include <sound_system/sound_system.h>
#include <util/complex.h>
#include <sound_system/definitions.h>
#include <tuner/filter.h>

#include <cmath>

#ifndef TUNER_H

#define TUNER_H

using namespace Sound_system;


#define TUNER_DEFAULT_SOUND_SYSTEM ALSA

#define TAG "TUNER"

enum {
	DEFAULT_OVERSAMPLING = 25,
	DEFAULT_DOWNSAMPLE = true,
};


enum TunerStatus {
	TUNING,
	NOT_TUNING
};

class Fft;

class Tuner {
	friend class Fft;
	private:
	sound_system * sound;
	s_system_t sound_system_type;
	TunerStatus status;

	double * buffer;
	double * complete_buffer;
	double * complete_buffer_with_window;
	complex  * complex_buffer;
	double * hanWindow;
	double * han_fft;


	/* parameters from sound system */
	unsigned int sample_rate;
	int sound_system_buffer_size;

	unsigned int oversampling;
	unsigned int peak_number;

	/* the goal */
	double frequency;

	/* Tnuning parameters */
	bool useFilter;
	FilterType filter_type;
	Filter * filter;
	bool downsample;

	/* other parameters */
	double time_window;  /* seconds */
	unsigned int complete_buffer_size;

	int fft_size;
	/* fourier variables */
	double delta_fft;
	double _1_n2;

	int dii; /* decimation intput index */ 

	/* FFT object */
	Fft * fft;

	public:
	Tuner();
	Tuner(s_system_t sst);
	
	~Tuner();

	void startTuning();
	void stopTuning();


	void callbackData(double * data, int size_data, void * dummy);


	/* main methods */
	void decimate();
	void findFrequency();


	double getFundamentalFrequency() {
		return frequency;
	}


};

#endif /* end of include guard: TUNER_H */
