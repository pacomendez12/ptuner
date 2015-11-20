#include <sound_system/sound_system.h>
#include <util/array.h>
#include <util/complex.h>


int main(int argc, char * argv[])
{
	/*int arr[] = {1,2,3,4,5,6,7,8,9};
	int * p = arr;

	printf("size of array %lu\n", ARRAY_SIZE(p));*/
	Sound_system::sound_system sound_sys;
	sound_sys.record();
	/* sleep main thread to read 2 seconds */
	sleep(2);
	sound_sys.stop();
	complex x(5, 6);
	complex y(10, 3);
	complex z;

	z = x + y;
	std::cout << z.toString();
	return 0;
}
