#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <cstring>
#include <string>

#define NONE 0
#define ALSA 1
#define JACK 2

#define DEFAULT_SOUND_SYSTEM ALSA

enum result_t { ERROR_RESULT = 0, OK_RESULT};
/*std::string result_t_strings[2] =
{
	"ERROR_RESULT",
	"OK_RESULT"
};*/

/*status of the sound system, note that play and record are
 * mutually exlusive*/
enum status_t {PLAYING = 0, RECORDING, STOPPED};
/*std::string status_t_strings[2] =
{
	"PLAYING",
	"RECORDING",
	"STOPPED"
};*/

typedef int s_system_t;



#endif /* end of include guard: DEFINITIONS_H */
