#include <sound_system/recorder.h>

/*CD quality for rate frame 
 * 24 bits of depth*/
Recorder::Recorder(){
	thread_capture = NULL;
}

Recorder::~Recorder() {
	if (thread_capture != NULL) {
		delete thread_capture;
	}
}


