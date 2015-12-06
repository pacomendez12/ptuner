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
Fft::fft_rec(double * in, complex * out, unsigned int n,
			unsigned int offset, unsigned int d1, unsigned int step)
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

		for (c = 0, q = 0; q < n / 2; q++, c += step) {
			a = q + d1;
			b = a + np2;

			x1 = out[a];
			x2 = out[b] * wn[c];
			out[a] = x1 + x2;
			out[b] = x1 - x2;
		}
	}
}

void
Fft::fft(double * in, complex * out, unsigned int n)
{
    fft_rec(in, out, n, 0, 0, 1);
}


void
Fft::fft_spd(double * in, int n1, double wi, double dw,
												double * out, int n2)
{
	double real, imag;
	double wn;
	double n1_2 = n1 * n1;

	for (int i = 0; i < n2; i++) {
		real = imag = 0.0;
		for (int n = 0; n < n1; n++) {
			wn = (wi + dw * i) * n;
			real = real + cos(wn) * in[n];
			imag = imag - sin(wn) * in[n];
		}
		out[i] = (real * real + imag * imag) / n1_2;
	}
}


void
Fft::fft_spd_diff(double * in, int N, double w, double & out_d1,
													double & out_d2)
{
	double cos_wn, sin_wn;

	double sum_cos_wn = 0.0;
	double sum_sin_wn = 0.0;
	double n_sum_cos_wn = 0.0;
	double n_sum_sin_wn = 0.0;
	double n2_sum_cos_wn = 0.0;
	double n2_sum_sin_wn = 0.0;

	for (int i = 0; i < N; i++) {
		cos_wn = in[i] * cos(w * i);
		sin_wn = in[i] * sin(w * i);
	
		sum_sin_wn += sin_wn;
		sum_cos_wn += cos_wn;

		n_sum_sin_wn += sin_wn * i;
		n_sum_cos_wn += cos_wn * i;

		n2_sum_sin_wn += sin_wn * i * i;
		n2_sum_cos_wn += cos_wn * i * i;
	}

	double n2 = N * N;
	out_d1 = 2.0 * 
		(sum_sin_wn * n_sum_cos_wn - sum_cos_wn * n_sum_sin_wn) / n2;

	out_d2 = 2.0 * (n_sum_cos_wn * n_sum_cos_wn -
		sum_sin_wn * n2_sum_sin_wn + n_sum_sin_wn * n_sum_sin_wn -
		sum_cos_wn * n2_sum_cos_wn) / n2;
}
