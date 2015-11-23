/* Here is implemented generic functions for systems
 * like number channels configuration, rate configuration, etc
 * */

#include <sound_system/system.h>

A_system::A_system() {
	recorder = NULL;
	player = NULL;
	buffer = NULL;
	parametersPtr = NULL;
}

A_system::~A_system() {
	slog(SYSTEM_TAG, "Calling A_system class destructor, recorder and player");
	if (recorder != NULL) {
		delete recorder;
		recorder = NULL;
	}

	if (player != NULL) {
		delete player;
		player = NULL;
	}
}


void
A_system::
setCallback(void (*callback)(double * buffer, int buffer_size, void * arg)) {
	this->callback = callback;
}

system_parameters::~system_parameters() 
{
	if (valid_rates != NULL) {
		slog(SYSTEM_TAG, "Calling destructor from system_parameters");
		delete [] valid_rates;
		valid_rates = NULL;
		size_valid_rates = 0;
	}
}

system_parameters::system_parameters()
{
	valid_rates = NULL;
	size_valid_rates = 0;
	channels = DEFAULT_NUMBER_CHANNELS; /*default */
	depth = 24; /* 24 bits */
	rate = DEFAULT_RATE;
	slog(SYSTEM_TAG, "Calling constructor from system_parameters");
}

void
system_parameters::set_number_channels(unsigned int ch) 
{
	channels = (ch > 0)?ch: 1;
}

void
system_parameters::set_rate(unsigned int ra)
{
	if (value_in_array(ra, valid_rates,size_valid_rates))
		rate = ra;
	else {
		slog(SYSTEM_TAG, "%d rate is not a valid rate, using default value (%d)", 
				ra, DEFAULT_RATE);
		rate = DEFAULT_RATE;
	}
}


void
system_parameters::set_depth(unsigned int de)
{
	depth = de;
}

unsigned int 
system_parameters::get_number_channels()
{
	return channels;
}

unsigned int
system_parameters::get_rate()
{
	return rate;
}

unsigned int 
system_parameters::get_depth()
{
	return depth;
}


void
system_parameters::set_valid_rates_array(const unsigned int * arr, int size)
{
	if (valid_rates != NULL) {
		delete [] valid_rates;
	}

	valid_rates = new unsigned int[size];
	memcpy(valid_rates, arr, sizeof(unsigned int) * size);
	size_valid_rates = size;
}
