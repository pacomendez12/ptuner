/*Abstract class*/

#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "recorder.h"
#include "player.h"
#include "definitions.h"

#define SYSTEM_PLAYER 1
#define SYSTEM_RECORDER 2

/* Default buffer size in case a specific sound system wants to use it */
#define SYSTEM_DEFAULT_BUFFER_SIZE 128


#define DEFAULT_RATE 44100


typedef int system_mode_t;

typedef short buffer_data_t;

typedef int buffer_size_t;

class A_system {
public:
	virtual ~A_system(){}

	/*The most abstract methods*/
	virtual result_t play() = 0;
	virtual result_t stop() = 0;
	virtual result_t record() = 0;

	// void setParameters(int rate, int depth);


	/* method for logging the system */
	void slog(const char * tag, const char *fmt, ...);


protected:
	/* data */
	Recorder * recorder;
	Player * player;

	
	status_t status;
	

	/*private methods*/
	virtual int init_system() = 0;
	virtual void finish_system() = 0;

};


class system_parameters {
public:
	system_mode_t mode;

	int buffer_size;
	unsigned int rate;
	int depth;
	short channels;
	buffer_data_t * buffer;

	/* An array with valid values to be setted for the system */
	int * valid_rates;
	int size_valid_rates;
	
	/* Configuration methods */
	void set_number_channels(int);
	void set_rate(int);
	void set_depth(int);

	int get_number_channels(int);
	int get_rate(int);
	int get_depth(int);
};

#endif /* end of include guard: SYSTEM_H */
