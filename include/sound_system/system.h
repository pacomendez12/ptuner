/*Abstract class*/

#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <util/array.h>
#include "recorder.h"
#include "player.h"
#include "definitions.h"

#define SYSTEM_PLAYER 1
#define SYSTEM_RECORDER 2

/* Default buffer size in case a specific sound system wants to use it */
#define SYSTEM_DEFAULT_BUFFER_SIZE 128

#define DEFAULT_NUMBER_CHANNELS 1

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
	
	void set_number_channels(unsigned int);
	void set_rate(unsigned int);
	void set_depth(unsigned int);

	unsigned int get_number_channels();
	unsigned int get_rate();
	unsigned int get_depth();


	void set_valid_rates_array(const unsigned int *, int size);
};


class system_parameters {

	public:
		int buffer_size;
		buffer_data_t * buffer;
		unsigned int rate;
		unsigned int channels;
		unsigned int * valid_rates;
		int size_valid_rates;
		unsigned int depth;

		system_parameters();
		~system_parameters();


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
