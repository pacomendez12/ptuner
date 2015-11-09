/*Abstract class*/

#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <util/array.h>
#include <thread>
#include <unistd.h>
#include "recorder.h"
#include "player.h"
#include "definitions.h"
#include "logger.h"

#define SYSTEM_PLAYER 1
#define SYSTEM_RECORDER 2

/* Default buffer size in case a specific sound system wants to use it */
#define SYSTEM_DEFAULT_BUFFER_SIZE 128

#define DEFAULT_NUMBER_CHANNELS 1

#define DEFAULT_RATE 44100

#define SYSTEM_TAG "SYSTEM"

typedef int system_mode_t;

//typedef char buffer_data_t;
typedef int16_t buffer_data_t;

typedef int buffer_size_t;

class A_system : public Logger{
public:
	A_system();
	virtual ~A_system();

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
	buffer_data_t * buffer;
};


class system_parameters : public Logger{

	public:
		int buffer_size;
		unsigned int rate;
		unsigned int channels;
		unsigned int * valid_rates;
		int size_valid_rates;
		unsigned int depth;

		system_parameters();
		virtual ~system_parameters();


		void set_number_channels(unsigned int n_channels);
		void set_valid_rates_array(const unsigned int * array_rates
				, int array_size);
		void set_rate(unsigned int rate);
		void set_depth(unsigned int depth);


		unsigned get_number_channels();
		unsigned get_rate();
		unsigned get_depth();
};



#endif /* end of include guard: SYSTEM_H */
