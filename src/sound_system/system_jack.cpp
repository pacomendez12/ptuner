/* Here is where the jack system starts, and where the paremeters
 * are setted, it's important to remember that this is a subclass 
 * of the class "system" and therefore this class inherits a
 * recorder and a player
 * */

#include <sound_system/system_jack.h>

system_jack::system_jack(): 
	system_jack(SYSTEM_PLAYER | SYSTEM_RECORDER)
{

}

system_jack::system_jack(system_mode_t mode){
	status = STOPPED;
}

system_jack::~system_jack(){
}

void
system_jack::finish_system(){
	/*We need to stop every transaction yet alive*/
	switch(status){
		case PLAYING:
			player->stop();
			status = STOPPED;
		break;
		case RECORDING:
			recorder->stop();
			status = STOPPED;
			break;

		default:
			status = STOPPED;
	}

	/*we can delete objects*/
	if( recorder != NULL)
		delete recorder;

	if( player != NULL)
		delete player;
	
}
