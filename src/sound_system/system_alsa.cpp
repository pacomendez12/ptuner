/* Here is where the alsa system starts, and where the paremeters
 * are setted, it's important to remember that this is a subclass 
 * of the class "system" and therefore this class inherits a
 * recorder and a player
 * */

#include <sound_system/system_alsa.h>
#include <string.h>

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
	buffer = NULL;
	status = STOPPED;
	parameters.buffer_size = size;
	parameters.format = SND_PCM_FORMAT_S16_LE;

	int format_width = snd_pcm_format_width(parameters.format);
	slog(ALSA_TAG, "Format width = %d", format_width);

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
	
	/* FIXME i'm using dafault name only for testing purposes */
	strncpy(parameters.card_name, "default", CARD_NAME_SIZE);
	//buffer = new (std::nothrow) buffer_data_t[parameters.buffer_size * 
	//			snd_pcm_format_width(parameters.format) / 8 * 2];
	buffer = new (std::nothrow) buffer_data_t[parameters.buffer_size * 
				sizeof(buffer_data_t) * parameters.channels];
	memset(buffer, 0, parameters.buffer_size * sizeof(buffer_data_t) *
		   	parameters.channels);
	if(buffer == NULL){
		slog(ALSA_TAG, "ENOMEM: there is no memory to reserve buffer");
		exit(1);
	}

	/* setting default number of channels */
	parameters.set_number_channels(ALSA_DEFAULT_NUMBER_CHANNELS);
	int array_size = ARRAY_SIZE(alsa_valid_rates);
	parameters.set_valid_rates_array(alsa_valid_rates, array_size); 
	slog(ALSA_TAG, "alsa_valid_rates has %d elements", parameters.size_valid_rates);
	parameters.set_rate(ALSA_DEFAULT_RATES);
	/*TODO set rate and depth */ 


	/*Here is where the system starts*/
	init_system();


	/*FIXME fix if recorder is created based on mode parameter */
	/*creating player and recording */
	recorder = new Recorder_Alsa(this);
	/* test for recording */
	recorder->getStream(NULL,0);
}

system_alsa::~system_alsa(){
	slog(ALSA_TAG, "Starting destructor of system_alsa");
	finish_system();
	if (buffer != NULL) {
		delete [] buffer;
		buffer = NULL;
		/*close have to be after delete of buffer it is a must */
		snd_pcm_close(parameters.capture_handle);
	}
}

int
system_alsa::init_system(){
	int dir;

	slog(ALSA_TAG, "Starting alsa sound system");

	/*FIXME it's not working on both sides, record and capture */
	if((err = snd_pcm_open(&(parameters.capture_handle), parameters.card_name, 
					SND_PCM_STREAM_CAPTURE, 0)) < 0){
		slog(ALSA_TAG, "Cannot open audio device %s (%s)", 
				parameters.card_name, snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_malloc(&(parameters.hw_params))) < 0){
		slog(ALSA_TAG, "Cannot allocate hardate parameter structure (%s)", 
				snd_strerror(err));
		exit(1);
	}
	if((err = snd_pcm_hw_params_any(parameters.capture_handle, 
					parameters.hw_params)) < 0) {
		slog(ALSA_TAG, "Cannot initialize hardware parameter structure (%s)", 
				snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_access(parameters.capture_handle, 
					parameters.hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		slog(ALSA_TAG, "Cannot set access type (%s)", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_format(parameters.capture_handle, 
					parameters.hw_params, parameters.format)) < 0) {
		slog(ALSA_TAG, "Cannot set sample format (%s)", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_rate_near(parameters.capture_handle, 
					parameters.hw_params, &(parameters.rate), &dir)) < 0) {
		slog(ALSA_TAG, "Cannot set sample rate (%s)", snd_strerror(err));
		exit(1);
	}
	slog(ALSA_TAG, "Rate setted as %d", parameters.rate);

	if((err = snd_pcm_hw_params_set_channels(parameters.capture_handle, 
					parameters.hw_params, parameters.channels)) < 0){
		slog(ALSA_TAG, "Cannot set channel count (%s)", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params(parameters.capture_handle, parameters.hw_params)) < 0){
		slog(ALSA_TAG, "Cannot set parameters (%s)", snd_strerror(err));
		exit(1);
	}

	snd_pcm_hw_params_free(parameters.hw_params);

	if((err = snd_pcm_prepare(parameters.capture_handle)) < 0){
		slog(ALSA_TAG, "Cannot prepare audio interface for use (%s)", snd_strerror(err));
		exit(1);
	}
	return 0;
}


result_t
system_alsa::play() {}


result_t
system_alsa::stop() {
	slog(ALSA_TAG, "stopping from system_alsa, current status = %d", status);
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
}


result_t
system_alsa::record() {
	recorder->start();
	status = recorder->getStatus();
}

void
system_alsa::finish_system(){
	/*We need to stop every transaction yet alive*/
	slog(ALSA_TAG, "finishing alsa sound system");
	stop();
}


/* alsa_system_parameters methods */

alsa_system_parameters::alsa_system_parameters() : system_parameters() {
	slog(ALSA_TAG, "Calling constructor from alsa_system_parameters");
	capture_handle = NULL;
	hw_params = NULL;
}


alsa_system_parameters::~alsa_system_parameters() {
	slog(ALSA_TAG, "Calling destructor from alsa_system_parameters");
}
