#ifndef SYSTEM_ALSA_H
#define SYSTEM_ALSA_H

#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <new>
#include <alsa/asoundlib.h>
#include "system.h"

#define CARD_NAME_SIZE 50

class system_alsa :public A_system
{
public:
	system_alsa();
	system_alsa(system_mode_t mode);
	system_alsa(system_mode_t mode, buffer_size_t size);

	~system_alsa();

	/*The most abstract methods*/
	result_t play();
	result_t stop();
	result_t record();

protected:
	int init_system();
	void finish_system();

private:
	snd_pcm_t * playback_handle;
	snd_pcm_hw_params_t * hw_params;

	char card_name[CARD_NAME_SIZE];

	/*for error handling purposes*/
	int err;
};


#endif /* end of include guard: SYSTEM_H */
