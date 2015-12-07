#include <sound_system/sound_system.h>
#include <util/complex.h>
#include <sound_system/definitions.h>
#include <gui/ProyectImplementation.h>
#include <tuner/filter.h>
#include <mutex>
#include <cmath>
#include <string>

#ifndef TUNER_H

#define TUNER_H

using namespace Sound_system;
//using namespace std;



#define TUNER_DEFAULT_SOUND_SYSTEM ALSA

#define TAG "TUNER"

enum {
	DEFAULT_OVERSAMPLING = 25,
	DEFAULT_DOWNSAMPLE = true,
	DEFAULT_DFT_SIZE = 15,
};


enum TunerStatus {
	TUNING,
	NOT_TUNING
};

class Fft;
class Signal;
//class Interface;

class Tuner {
	friend class Fft;
	friend class Signal;
	private:
	sound_system * sound;
	s_system_t sound_system_type;
	TunerStatus status;

	/* mutex to protect complete_buffer */
	std::mutex buffer_mutex;

	double * buffer;
	double * complete_buffer;
	double * complete_buffer_with_window;
	double * windowed_buffer;
	double * fft_spd_buffer;
	double * fft_spd_diff_buffer;
	double * spd_dft;
	complex  * complex_buffer;
	double * hanWindow;
	double * han_fft;
	double * representable_data;


	/* parameters from sound system */
	unsigned int sample_rate;
	int sound_system_buffer_size;

	unsigned int oversampling;
	unsigned int peak_number;
	unsigned int dft_size;

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
	Signal * signal; /* signal object */


	/* after frequency is calculated */
	double error;
	double note;
	std::string note_string;
	std::string notes[12];

	double stringsGuitar[6];
	double stringsViolin[4];

	std::string getNoteFromFrequency(double freq);
	double getErrorFromFrequency(double freq);
	void calculateNoteAndFrequency(double freq);
	std::string getString(double f, double note, int inst);
	int closestString(int instument);



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

	double * getProcessedArray();

	/* GUI */
	Interface * gui;

	bool isTuning() {
		if (status == TUNING) {
			return true;
		}
		return false;
	}

};

#endif /* end of include guard: TUNER_H */
