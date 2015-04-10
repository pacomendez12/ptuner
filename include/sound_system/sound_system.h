#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <assert.h>
#include "system.h"
#include "definitions.h"
#include "system_alsa.h"
#include "system_jack.h"

namespace Sound_system{
	class sound_system {
		private:
			s_system_t type;
			A_system * system_;

			/*private methods*/
			void select_sound_system(s_system_t);

		public:
			sound_system();
			sound_system(s_system_t);
			~sound_system();

			result_t play();
			result_t stop();
			result_t record();

	};

}


#endif
