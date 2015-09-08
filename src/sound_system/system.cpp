/* Here is implemented generic functions for systems
 * like number channels configuration, rate configuration, etc
 * */

#include <sound_system/system.h>


system_parameters::~system_parameters() 
{
	if (valid_rates != NULL) {
		delete [] valid_rates;
		size_valid_rates = 0;
	}
}

system_parameters::system_parameters()
{
	valid_rates = NULL;
	size_valid_rates = 0;
	buffer = NULL;
	channels = DEFAULT_NUMBER_CHANNELS; /*default */
	depth = 24; /* 24 bits */
	rate = DEFAULT_RATE;
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
	else
		rate = DEFAULT_RATE;
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
	if (arr != NULL) {
		delete [] valid_rates;
	}

	valid_rates = new unsigned int[size];
	memcpy(valid_rates, arr, size);
	size_valid_rates = size;
}
