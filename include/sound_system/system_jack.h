#ifndef SYSTEM_JACK_H
#define SYSTEM_JACK_H
#include "system.h"

class system_jack :public system
{
public:
	system_jack();
	~system_jack();

	/*The most abstract methods*/
	result_t play();
	result_t stop();
	result_t record();

private:
	void init_system();
	void finish_system();

};


#endif /* end of include guard: SYSTEM_H */
