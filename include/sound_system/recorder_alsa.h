/*
 * This class has a virtual method that needs to be implemented
 * in a subclass because it's dependent of the system used for 
 * capturing sound
 */
#ifndef RECORDER_ALSA_H
#define RECORDER_ALSA_H

#include "recorder.h"
#include <alsa/asoundlib.h>

/*opaque class*/
class system_alsa;

class Recorder_Alsa : public Recorder{
	public:
		Recorder_Alsa(system_alsa *);
		/*Destructor is called when the tuner finish or when is 
		 * changed the sound system.
		 **/
		~Recorder_Alsa();
		result_t getStream(void * buff, int size);
		void stop();
		void start();

		/*FIXME: I'm not sure now if the next methods will be part
		 * of this class
		 * */

		/*virtual int initSoundSystem() = 0;
		virtual int finishSoundSystem() = 0;*/

		private:
		system_alsa * saptr;

		/* private methods */
		void get_data_from_alsa();
};

#endif
