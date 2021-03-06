#include <sound_system/sound_system.h>

/*
 * this file defines how ptuner capture audio from microphone,
 * for the first instance, it only supports ALSA, but the aim
 * of this file is to be transparent over what sound system
 * is using, in fact I want it to support JACK too at least.
 */
using namespace Sound_system;
#define TAG "SOUND_SYSTEM"

sound_system::sound_system(): sound_system(DEFAULT_SOUND_SYSTEM, NULL){}

sound_system::sound_system(s_system_t type, void (*callback)(double * buffer,
			int buffer_size, void * arg)){
	this->type = NONE;
	system_ = NULL;
	this->callback = callback;
	select_sound_system(type);

	if (system_) {
		system_->setCallback(this->callback);
	}
}

sound_system::~sound_system() {
	slog(TAG, "Calling sound_system destructor");
	if (system_ != NULL) {
		delete system_;
	}
}

void
sound_system::
setCallback(void (*callback)(double * buffer, int buffer_size, void * arg)) {
	this->callback = callback;
	if (system_) {
		system_->setCallback(this->callback);
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



void 
sound_system::setSystemParameters(system_parameters &sp)
{

}

int 
sound_system::getSampleRate()
{
	if (system_ != NULL) {
		return system_->parametersPtr->rate;
	}
}

int 
sound_system::getSoundSystemBufferSize()
{
	if (system_ != NULL) {
		return system_->parametersPtr->buffer_size;
	}
}
