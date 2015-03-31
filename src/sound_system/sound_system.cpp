#include <sound_system.h>

/*
 * this file defines how ptuner capture audio from microphone,
 * for the first instance, it only supports ALSA, but the aim
 * of this file is to be transparent over what sound system
 * is using, in fact I want it to support JACK too at least.
 */

sound_system::sound_system(): sound_system(ALSA){}

sound_system::sound_system(s_system_t type){
	select_sound_system(type);
}

sound_system::select_sound_system(s_system_t type){
	if(type >= ALSA && type <= JACK){
		this->type = type;
	} else {
		this->type = DEFAULT_SOUND_SYSTEM;
	}
} 
