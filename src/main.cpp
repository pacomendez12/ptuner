#include <sound_system/sound_system.h>
#include <util/array.h>


int main(int argc, char * argv[])
{
	/*int arr[] = {1,2,3,4,5,6,7,8,9};
	int * p = arr;

	printf("size of array %lu\n", ARRAY_SIZE(p));*/
	Sound_system::sound_system sound_sys;
	sound_sys.record();
	return 0;
}
