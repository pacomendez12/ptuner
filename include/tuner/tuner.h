#include <sound_system/sound_system.h>
#include <util/complex.h>
#include <sound_system/definitions.h>

#ifndef TUNER_H

#define TUNER_H

using namespace Sound_system;


#define TUNER_DEFAULT_SOUND_SYSTEM ALSA

#define TAG "TUNER"

class Tuner {
	private:
	sound_system sound;
	s_system_t sound_system_type;


	public:
	Tuner();
	Tuner(s_system_t sst);
	~Tuner();


	void callbackData(double * data, int size_data, void * dummy);


};


#endif /* end of include guard: TUNER_H */
