#include <fft/fft.h>
#include <cmath>


Fft::Fft(Tuner * tuner)
{
	double alpha;

	wn = new complex[tuner->fft_size];

	for (int i = 0; i < tuner->fft_size / 2; i++) {
		alpha = -2.0 * i * M_PI / tuner->fft_size;
		wn[i].real = cos(alpha);
		wn[i].imag = sin(alpha);
	}
}

Fft::~Fft()
{
	delete [] wn;
}


void
Fft::fft_rec(double * in, complex * out, unsigned int n, unsigned int offset,
		unsigned int d1, unsigned int step)
{
	complex x1, x2;
	unsigned long np2 = n / 2;

	if (n == 2) {
		x1.real = in[offset];
		x1.imag = 0;
		x2.real = in[offset + step];
		x2.imag = 0;

		out[d1] = x1 + x2;
		out[d1 + np2] = x1 - x2;
	} else {
		unsigned long a, b, c, q;

		/* recursive call */
		fft_rec(in, out, np2, offset, d1, step * 2);
		fft_rec(in, out, np2, offset + step, d1 + np2, step * 2);
	}
}

void
Fft::fft(double * in, complex * out, unsigned int n)
{
    fft_rec(in, out, n, 0, 0, 1);
}


