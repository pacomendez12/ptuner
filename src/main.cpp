#include <sound_system/sound_system.h>
#include <util/array.h>
#include <util/complex.h>



void cback(double * buffer, int buffer_size, void * arg) {
	std::cout << "Receiving " << buffer_size << " bytes from sound system" << std::endl;
	for (int i = 0; i < buffer_size; i++) {
		std::cout << buffer[i] <<" ";
	}
	std::cout << std::endl;
}

int main(int argc, char * argv[])
{
	/*int arr[] = {1,2,3,4,5,6,7,8,9};
	int * p = arr;

	printf("size of array %lu\n", ARRAY_SIZE(p));*/
	Sound_system::sound_system sound_sys;
	sound_sys.setCallback(cback);
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
