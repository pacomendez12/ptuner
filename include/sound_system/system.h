/*Abstract class*/

#ifndef SYSTEM_H
#define SYSTEM_H
#include "recorder.h"
#include "player.h"
#include "definitions.h"

#define SYSTEM_PLAYER 1
#define SYSTEM_RECORDER 2

typedef int system_mode_t;

typedef char buffer_data_t;

typedef int buffer_size_t;

class A_system {
public:
	virtual ~A_system() = 0;

	/*The most abstract methods*/
	virtual result_t play() = 0;
	virtual result_t stop() = 0;
	virtual result_t record() = 0;


	// void setParameters(int rate, int depth);


protected:
	/* data */
	Recorder * recorder;
	Player * player;
	
	status_t status;
	system_mode_t mode;

	int buffer_size;
	int rate;
	int depth;
	buffer_data_t * buffer;
	
	/*private methods*/
	virtual int init_system() = 0;
	virtual void finish_system() = 0;

};


#endif /* end of include guard: SYSTEM_H */
