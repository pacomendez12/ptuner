/*
 * This class has a virtual method that needs to be implemented
 * in a subclass because it's dependent of the system used for 
 * capturing sound
 */

#include "recoder.h"
#include <alsa/asoundlib.h>

#ifndef RECORDER_ALSA_H
#define RECORDER_ALSA_H

class Recorder_Alsa : Recorder{
	public:
		Recorder_Alsa();
		Recorder_Alsa(int rate, int depth);
		/*Destructor is called when the tuner finish or when is 
		 * changed the sound system.
		 **/
		~Recorder_Alsa();
		int getStream(void * buff, int size);

		/*FIXME: I'm not sure now if the next methods will be part
		 * of this class
		 * */

		/*virtual int initSoundSystem() = 0;
		virtual int finishSoundSystem() = 0;*/
};

#endif
