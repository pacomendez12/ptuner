#include <sound_system/recorder.h>

/*CD quality for rate frame 
 * 24 bits of depth*/
Recorder::Recorder():Recorder(44100, 24){}

Recorder::Recorder(int rate, int depth){
	setParameters(rate, depth);
}

Recorder::setParameters(int rate, int depth){
	this->rate = rate;
	this->depth = depth;
}

