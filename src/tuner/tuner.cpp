#include <tuner/tuner.h>

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
	std::cout << "Receiving " << data_size << " bytes from sound system" << std::endl;
	for (int i = 0; i < data_size; i++) {
		std::cout << data[i] <<" ";
	}
	std::cout << std::endl;

}


Tuner::Tuner() : Tuner(TUNER_DEFAULT_SOUND_SYSTEM) {}


Tuner::Tuner(s_system_t sst) 
{
	sound_system_type = sst;
	sound.select_sound_system(sst);
	sound.setCallback(callback);
	sound.record();

	/* global Tuner ptr have to be able to call the 
	 * tuner object callbackData */
	tunerPtr = this;

}

Tuner::~Tuner()
{
	sound.stop();
	tunerPtr = NULL;
}
