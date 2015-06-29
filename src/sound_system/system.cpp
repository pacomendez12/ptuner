/* Here is implemented generic functions for systems
 * like number channels configuration, rate configuration, etc
 * */

#include <sound_system/system.h>
#include <util/array.h>

void
system_parameters::set_number_channels(int ch) 
{
	channels = (ch > 0)?ch: 1;
}

void
system_parameters::set_rate(int ra)
{
	if (value_in_array(ra, valid_rates,size_valid_rates))
		rate = ra;
	else
		rate = DEFAULT_RATE;
}


void
system_parameters::set_depth(int de)
{
	depth = de;
}

int 
system_parameters::get_number_channels(int)
{
	return channels;
}

int
system_parameters::get_rate(int)
{
	return rate;
}

int 
system_parameters::get_depth(int)
{
	return depth;
}
