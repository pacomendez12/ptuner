#include <sound_system/recorder_alsa.h>

/*CD quality for rate frame 
 * 24 bits of depth*/
Recorder_Alsa::Recorder_Alsa() : Recorder_Alsa(41000, 24){
}

Recorder_Alsa::Recorder_Alsa(int rate, int depth) {

}

Recorder_Alsa::~Recorder_Alsa() {
}


int
Recorder_Alsa::getStream(void * buff, int size) {

	return 0;
}

void
Recorder_Alsa::stop() {

}
