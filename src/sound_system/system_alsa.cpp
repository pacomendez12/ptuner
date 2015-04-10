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
	system_alsa(SYSTEM_PLAYER | SYSTEM_RECORDER, 128)
{}

system_alsa::system_alsa(system_mode_t mode, buffer_size_t size){
	status = STOPPED;
	buffer_size = size;
	
	buffer = nullptr;
	playback_handle = nullptr;
	hw_params = nullptr;

	buffer = new (std::nothrow) buffer_data_t[buffer_size];
	strncpy(card_name, "default", CARD_NAME_SIZE);
	if(buffer == nullptr){
		return;
	}


	/*Here is where the system starts*/
	init_system();
}

system_alsa::~system_alsa(){
}

int
system_alsa::init_system(){
	int dir;
	snd_pcm_t * playback_handle;
	snd_pcm_hw_params_t * hw_params;

	if((err = snd_pcm_open(&playback_handle, card_name, 
					SND_PCM_STREAM_PLAYBACK | SND_PCM_STREAM_CAPTURE, 0)) < 0){
		fprintf(stderr, "Cannot open audio device %s (%s)\n", card_name, snd_strerror(err));
		exit(1);
	}
/*
	if((err = snd_pcm_hw_params_malloc(&hw_params)) < 0){
		fprintf(stderr, "Cannot allocate hardate parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_any(playback_handle, hw_params)) < 0){
		fprintf(stderr, "Cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_access(playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0){
		fprintf(stderr, "Cannot set access type (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_format(playback_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0){
		fprintf(stderr, "Cannot set sample format (%s)\n", snd_strerror(err));
		exit(1);
	}

	rate = 44100;

	if((err = snd_pcm_hw_params_set_rate_near(playback_handle, hw_params, &rate, &dir)) < 0){
		fprintf(stderr, "Cannot set sample rate (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_channels(playback_handle, hw_params, 2)) < 0){
		fprintf(stderr, "Cannot set channel count (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params(playback_handle, hw_params)) < 0){
		fprintf(stderr, "Cannot set parameters (%s)\n", snd_strerror(err));
		exit(1);
	}

	snd_pcm_hw_params_free(hw_params);

	if((err = snd_pcm_prepare(playback_handle)) < 0){
		fprintf(stderr, "Cannot prepare audio interface for use (%s)\n", snd_strerror(err));
		exit(1);
	}

	for(i = 0; i < 10; ++i){
		if((err = snd_pcm_writei(playback_handle, buf, 128)) != 128){
			fprintf(stderr, "Write to audio interface failed (%s)\n", snd_strerror(err));
			exit(1);
		}
	}

	snd_pcm_close(playback_handle);
*/
}

void
system_alsa::finish_system(){
	/*We need to stop every transaction yet alive*/
	switch(status){
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
	if( recorder != NULL)
		delete recorder;

	if( player != NULL)
		delete player;
	
}
