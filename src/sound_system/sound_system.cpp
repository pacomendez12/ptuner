#include <sound_system/sound_system.h>

/*
 * this file defines how ptuner capture audio from microphone,
 * for the first instance, it only supports ALSA, but the aim
 * of this file is to be transparent over what sound system
 * is using, in fact I want it to support JACK too at least.
 */
using namespace Sound_system;

sound_system::sound_system(): sound_system(DEFAULT_SOUND_SYSTEM){}

sound_system::sound_system(s_system_t type){
	this->type = NONE;
	system_ = NULL;
	select_sound_system(type);
}

sound_system::~sound_system() {
	if (system_ != NULL) {
		system_->stop();
		delete system_;
	}
}

void
sound_system::select_sound_system(s_system_t type){
	s_system_t tmp_type;
	if(type >= ALSA && type <= JACK){
		tmp_type = type;
	} else {
		tmp_type = DEFAULT_SOUND_SYSTEM;
	}

	/*we are going to check if the system is created before*/
	if(system_ != NULL){
		delete system_;
	}

	switch(tmp_type){
		case ALSA:
			system_ = new system_alsa();
			break;
		case JACK:
			system_ = new system_jack();
			break;
		default:
			system_ = NULL;
			tmp_type = NONE;
			break;
	}

	/*Refreshing attribute type*/
	this->type = tmp_type;
} 


result_t
sound_system::play(){
	assert(system_ != NULL);
	return system_->play();
}

result_t
sound_system::stop(){
	assert(system_ != NULL);
	return system_->stop();
}

result_t
sound_system::record(){
	assert(system_ != NULL);
	return system_->record();
}
