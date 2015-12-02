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
	if (useFilter) {
		if (filter_type == BUTTERWORTH) {
			Filter::Butterworth(data, data_size, buffer, TUNER_SAMPLES);
		} else if (filter_type == CHEBY_TYPE) {
			filter->filter(data_size, data, &buffer[size_data_keept
										/ sizeof(double)]);
		}
	} else {
		memcpy(buffer + size_data_keept / sizeof(double), data, data_size
				* sizeof(double));
	}

}


void
Tuner::decimate()
{


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

	/* enable filter by default */
	useFilter = true;
	//filter = BUTTERWORTH;
	filter_type = CHEBY_TYPE;


	/* Initialize filter */
	filter = new Filter(filter_type, oversampling);


	/* Han window */
	for (int i = 0; i < TUNER_SAMPLES; i++) {
		hanWindow[i] = 0.5 * (1 - cos(2 * M_PI * i / (TUNER_SAMPLES - 1.0)));
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

	if (sound) {
		delete sound;
		sound = NULL;
	}

	if (filter) {
		delete filter;
		filter = NULL;
	}
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
