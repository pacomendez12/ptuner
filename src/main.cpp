#include <sound_system/sound_system.h>
#include <util/array.h>
#include <util/complex.h>
#include <tuner/tuner.h>
#include <fft/fft.h>


int main(int argc, char * argv[])
{
	/*int arr[] = {1,2,3,4,5,6,7,8,9};
	int * p = arr;

	printf("size of array %lu\n", ARRAY_SIZE(p));*/
	//Sound_system::sound_system sound_sys;
	//sound_sys.setCallback(cback);
	//sound_sys.record();
	/* sleep main thread to read 2 seconds */
	//sleep(2);
	//sound_sys.stop();
	//complex x(5, 6);
	//complex y(10, 3);
	//complex z;

	//z = x + y;
	//std::cout << z.toString();
	//
	//
	/*
	double buffer[512];
	complex comp[512];
	Tuner t;
	Fft * fft = new Fft(&t);

	for (int i = 0; i < 512; i++) {
		buffer[i] = i + 1;
	}

	fft->fft(buffer, comp, 512);

	for (int i = 0; i < 512; i++) {
		printf("[%lf, %lf]\n", comp[i].real, comp[i].imag);
	}

	
	return 0;*/
	Tuner tuner;
	tuner.startTuning();
	double * arr = tuner.getProcessedArray();
	/* copy arr to other array because it will change */
	sleep(10);
	return 0;
}
