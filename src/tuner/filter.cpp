#include <tuner/filter.h>


//copyright ctuner https://code.google.com/p/ctuner/

void
Filter::Butterworth(double * data, int data_size, double * buffer, int buffer_size)
{
	int offset = buffer_size - data_size;
	for (int i = 0; i < data_size; i++) {
		double G = 3.023332184e+01;
		double K = 0.9338478249;

		double xv[2];
		double yv[2];

		xv[0] = xv[1];
		xv[1] = data[i] / G;

		yv[0] = yv[1];
		yv[1] = (xv[0] + xv[1]) + (K * yv[0]);

		/* copying data to buffer */
		buffer[offset + i] = yv[1];
	}

}
