#ifndef SYSTEM_ALSA_H
#define SYSTEM_ALSA_H

#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <new>
#include <alsa/asoundlib.h>
#include "system.h"
#include "recorder_alsa.h"


/* This flag will be used to define what flags are we going to use */
#define ALSA_CONFIGS 1

/* Defines the max size for the name of the device (example: default) */
#define CARD_NAME_SIZE 50

/* Defines the default buffer size for ALSA */
//#define ALSA_DEFAULT_BUFFER_SIZE 256
#define ALSA_DEFAULT_BUFFER_SIZE 128

/* Default number of channels */
#define ALSA_DEFAULT_NUMBER_CHANNELS 2

#define ALSA_DEFAULT_RATES 44100

/* Tag for logs */
#define ALSA_TAG "SYSTEM_ALSA"

class alsa_system_parameters : public system_parameters {

public:
	alsa_system_parameters();
	~alsa_system_parameters();
	snd_pcm_t * playback_handle;
	snd_pcm_t * capture_handle;
	snd_pcm_hw_params_t * hw_params;
	snd_pcm_format_t format;

	char card_name[CARD_NAME_SIZE];
};


class system_alsa :public A_system
 {
	 friend class Recorder_Alsa;

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

	alsa_system_parameters parameters;

private:
	/*for error handling purposes*/
	int err;

};

	/* TODO try to keep this value inside the class */
	const static unsigned int alsa_valid_rates[] = { 8000, 11025, 22050, 44100, 48000 };

//constexpr const unsigned int system_alsa::alsa_valid_rates[1];
#endif /* end of include guard: SYSTEM_H */
