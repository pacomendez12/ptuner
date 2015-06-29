#include <sound_system/system.h>

/* The first idea of how to implement a logger system */
void
A_system::slog(const char * tag, const char * fmt, ...)
{
	char final_tag[225];

	snprintf(final_tag, 225, "[ %s ]: ", tag);

	va_list args;
	va_start(args, fmt);
	fprintf(stdout, "%s", final_tag);
	vfprintf(stdout, fmt, args);
	fprintf(stdout, "\n");
	fflush(stdout);
	va_end(args);
}
