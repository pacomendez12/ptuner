#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include "recorder.h"
#include "player.h"
#define ALSA 1
#define JACK 2

#define DEFAULT_SOUND_SYSTEM 1


typedef int s_system_t;

class sound_system{
private:
	s_system_t type;

	Recorder recorder;
	Player player;

public:
	sound_system();
	sound_system(s_system_t);
	~sound_system();
	void select_sound_system(s_system_t);
};


#endif
