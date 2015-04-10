/*
 * This class has a virtual method that needs to be implemented
 * in a subclass because it's dependent of the system used for 
 * capturing sound
 */

#ifndef RECORDER_H
#define RECORDER_H

class Recorder{
	public:
		Recorder();
		/*Destructor is called when the tuner finish or when is 
		 * changed the sound system.
		 **/
		~Recorder();
		int virtual getStream(void * buff, int size) = 0;
		void virtual stop() = 0;

};

#endif
