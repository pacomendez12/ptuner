#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <assert.h>
#include "system.h"
#include "definitions.h"
#include "system_alsa.h"
#include "system_jack.h"
#include "logger.h"


namespace Sound_system{
	class sound_system : public Logger{
		private:
			s_system_t type;
			A_system * system_;

			/*private methods*/

			//callback
			void (* callback)(double * buffer, int buffer_size, void * arg);
		public:
			sound_system();
			sound_system(s_system_t, void (*callback)(double * buffer,
						int buffer_size, void * arg));
			~sound_system();

			result_t play();
			result_t stop();
			result_t record();

			void setCallback(void (*callback)(double * buffer, int buffer_size, 
						void *arg));
			void select_sound_system(s_system_t);
	};

}


#endif
