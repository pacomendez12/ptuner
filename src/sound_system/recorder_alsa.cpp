#include <sound_system/recorder_alsa.h>
#include <sound_system/system_alsa.h>
#include <sound_system/logger.h>

#define TAG "RECORDER_ALSA"

/*CD quality for rate frame 
 * 24 bits of depth*/
Recorder_Alsa::Recorder_Alsa(system_alsa * saptr) 
{
	this->saptr = saptr;
}


Recorder_Alsa::~Recorder_Alsa() 
{
}


result_t
Recorder_Alsa::getStream(void * buff, int size) 
{
	if((saptr->err = snd_pcm_readi(saptr->parameters.capture_handle, saptr->buffer, 
			saptr->parameters.buffer_size)) != saptr->parameters.buffer_size){
		saptr->slog(TAG, "read from audio interface failed (%s) err = %d", 
				snd_strerror(saptr->err), saptr->err);
		return ERROR_RESULT;
	} else {
		//slog(ALSA_TAG, "Read well %d bytes", err);
	}
	saptr->slog(ALSA_TAG, "size = %d bytes", saptr->parameters.buffer_size);
	return OK_RESULT;
}

	void
Recorder_Alsa::start() 
{
	saptr->slog(TAG, "° Starting capture from ALSA");
	status = RECORDING;

}

	void
Recorder_Alsa::stop() 
{
	saptr->slog(TAG, "| | Stoping capture from ALSA");
	status = STOPPED;

}
