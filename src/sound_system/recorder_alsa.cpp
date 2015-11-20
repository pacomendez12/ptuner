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
	
	return OK_RESULT;
}

void
Recorder_Alsa::start() 
{
	capture_thread_mutex.lock();
	//checking if there is a callback function
	if (saptr->callback) {
		saptr->slog(TAG, "° Starting capture from ALSA");
		status = RECORDING;
		thread_capture = new std::thread(&Recorder_Alsa::get_data_from_alsa,this);
	} else {
		saptr->slog(TAG, "Can't start capturing data, it doesn't exist a callback function");
	}
	capture_thread_mutex.unlock();
}

void
Recorder_Alsa::stop() 
{
	capture_thread_mutex.lock();
	saptr->slog(TAG, "| | Stoping capture from ALSA");
	status = STOPPED;
	thread_capture->join();
	delete thread_capture;
	thread_capture = NULL;
	capture_thread_mutex.unlock();
}


void
Recorder_Alsa::get_data_from_alsa() 
{
	while (status == RECORDING) {
		if((saptr->err = snd_pcm_readi(saptr->parameters.capture_handle, saptr->buffer, 
						saptr->parameters.buffer_size)) != saptr->parameters.buffer_size) {
			saptr->slog(TAG, "read from audio interface failed (%s) err = %d", 
					snd_strerror(saptr->err), saptr->err);
			saptr->slog(TAG, "FATAL ERROR: stopping audio from ALSA");
			status = STOPPED;
			//return ERROR_RESULT;
		} 
		//saptr->slog(TAG, "size = %d bytes", saptr->parameters.buffer_size);

		//copying data to double array
		
		for (int i = 0; i < saptr->parameters.buffer_size; i++) {
			saptr->float_buffer[i] = (double) saptr->buffer[i];
		}

		//call callback over sound_system
		saptr->callback(saptr->float_buffer, saptr->parameters.buffer_size, NULL);
	}
	saptr->slog(TAG, "status has changed from RECORDING to STOPPED");
}
