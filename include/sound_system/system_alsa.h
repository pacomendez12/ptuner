#ifndef SYSTEM_ALSA_H
#define SYSTEM_ALSA_H
#include "system.h"

class system_alsa :public system
{
public:
	system_alsa();
	~system_alsa();

	/*The most abstract methods*/
	result_t play();
	result_t stop();
	result_t record();

private:
	void init_system();
	void finish_system();

};


#endif /* end of include guard: SYSTEM_H */
