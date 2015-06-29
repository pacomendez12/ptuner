/* Here is where the alsa system starts, and where the paremeters
 * are setted, it's important to remember that this is a subclass 
 * of the class "system" and therefore this class inherits a
 * recorder and a player
 * */

#include <sound_system/system_alsa.h>

system_alsa::system_alsa(): 
	system_alsa(SYSTEM_PLAYER | SYSTEM_RECORDER)
{}

system_alsa::system_alsa(system_mode_t mode):
	system_alsa(mode, ALSA_DEFAULT_BUFFER_SIZE)
{}

system_alsa::system_alsa(system_mode_t mode, buffer_size_t size)
{
	slog(ALSA_TAG, "System Alsa constructor, with mode = %d, and buffer size=%d",
			mode, size);
	status = STOPPED;
	parameters.buffer_size = size;

#ifdef ALSA_CONFIGS
	if (parameters.buffer_size < ALSA_DEFAULT_BUFFER_SIZE) {
		slog(ALSA_TAG, "ALSA default buffer size used (%d)", 
				ALSA_DEFAULT_BUFFER_SIZE);
		parameters.buffer_size = ALSA_DEFAULT_BUFFER_SIZE;
	}
#else
	if (parameters.buffer_size < SYSTEM_DEFAULT_BUFFER_SIZE) {
		slog(ALSA_TAG, "SYSTEM default buffer size used (%d)", 
				SYSTEM_DEFAULT_BUFFER_SIZE);
		parameters.buffer_size = SYSTEM_DEFAULT_BUFFER_SIZE;
	}
#endif
	
	parameters.buffer = NULL;
	parameters.capture_handle = NULL;
	parameters.hw_params = NULL;

	strncpy(parameters.card_name, "default", CARD_NAME_SIZE);
	parameters.buffer = new (std::nothrow) buffer_data_t[parameters.buffer_size];
	if(parameters.buffer == NULL){
		return;
	}

	/* setting default number of channels */
	parameters.set_number_channels(ALSA_DEFAULT_NUMBER_CHANNELS);

	/*Here is where the system starts*/
	init_system();
}

system_alsa::~system_alsa(){
}

int
system_alsa::init_system(){
	int dir;

	slog(ALSA_TAG, "Starting alsa sound system");

	if((err = snd_pcm_open(&parameters.capture_handle, parameters.card_name, 
					SND_PCM_STREAM_CAPTURE, 0)) < 0){
		slog(ALSA_TAG, "Cannot open audio device %s (%s)\n", 
				parameters.card_name, snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_malloc(&parameters.hw_params)) < 0){
		slog(ALSA_TAG, "Cannot allocate hardate parameter structure (%s)\n", 
				snd_strerror(err));
		exit(1);
	}
	if((err = snd_pcm_hw_params_any(parameters.capture_handle, 
					parameters.hw_params)) < 0) {
		slog(ALSA_TAG, "Cannot initialize hardware parameter structure (%s)\n", 
				snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_access(parameters.capture_handle, 
					parameters.hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		slog(ALSA_TAG, "Cannot set access type (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_format(parameters.capture_handle, 
					parameters.hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
		slog(ALSA_TAG, "Cannot set sample format (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_rate_near(parameters.capture_handle, 
					parameters.hw_params, &parameters.rate, &dir)) < 0) {
		slog(ALSA_TAG, "Cannot set sample rate (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_channels(parameters.capture_handle, 
					parameters.hw_params, parameters.channels)) < 0){
		slog(ALSA_TAG, "Cannot set channel count (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params(parameters.capture_handle, parameters.hw_params)) < 0){
		slog(ALSA_TAG, "Cannot set parameters (%s)\n", snd_strerror(err));
		exit(1);
	}

	snd_pcm_hw_params_free(parameters.hw_params);

/*
	if((err = snd_pcm_prepare(capture_handle)) < 0){
		fprintf(stderr, "Cannot prepare audio interface for use (%s)\n", snd_strerror(err));
		exit(1);
	}

	for(i = 0; i < 10; ++i){
		if((err = snd_pcm_writei(capture_handle, buf, 128)) != 128){
			fprintf(stderr, "Write to audio interface failed (%s)\n", snd_strerror(err));
			exit(1);
		}
	}

	snd_pc_close(capture_handle);
*/
}

result_t
system_alsa::play() {}


result_t
system_alsa::stop() {}


result_t
system_alsa::record() {}

void
system_alsa::finish_system(){
	/*We need to stop every transaction yet alive*/
	switch (status) {
		case PLAYING:
			player->stop();
			status = STOPPED;
		break;
		case RECORDING:
			recorder->stop();
			status = STOPPED;
			break;

		default:
			status = STOPPED;
	}

	/*we can delete objects*/
	if (recorder != NULL)
		delete recorder;

/*	if ( player != NULL)
		delete player;*/
	
}
