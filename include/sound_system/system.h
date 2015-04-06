/*Abstract class*/

#ifndef SYSTEM_H
#define SYSTEM_H
#include "recorder.h"
#include "player.h"
#include "definitions.h"
#include "sound_system.h"

class system
{
public:
	virtual ~system() = 0;

	/*The most abstract methods*/
	virtual result_t play() = 0;
	virtual result_t stop() = 0;
	virtual result_t record() = 0;

private:
	/* data */
	Recorder * recorder;
	Player * player;
	
	/*private methods*/
	virtual void init_system() = 0;
	virtual void finish_system() = 0;
};


#endif /* end of include guard: SYSTEM_H */
