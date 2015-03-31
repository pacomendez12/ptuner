#include <sound_system/recorder_alsa.h>

/*CD quality for rate frame 
 * 24 bits of depth*/
Recorder_Alsa::Recorder_Alsa():Recorder_Alsa(44100, 24){}

Recorder_Alsa::Recorder_Alsa(int rate, int depth){
	setParameters(rate, depth);
}

