/*
 * This class has a virtual method that needs to be implemented
 * in a subclass because it's dependent of the system used for 
 * capturing sound
 */
#ifndef RECORDER_ALSA_H
#define RECORDER_ALSA_H

#include "recorder.h"
#include <alsa/asoundlib.h>

class Recorder_Alsa : Recorder{
	public:
		Recorder_Alsa();
		Recorder_Alsa(int rate, int depth);
		/*Destructor is called when the tuner finish or when is 
		 * changed the sound system.
		 **/
		~Recorder_Alsa();
		int getStream(void * buff, int size);
		void stop();

		/*FIXME: I'm not sure now if the next methods will be part
		 * of this class
		 * */

		/*virtual int initSoundSystem() = 0;
		virtual int finishSoundSystem() = 0;*/
};

#endif
