#ifndef FFT_H
#define FFT_H
#include <util/complex.h>
#include <tuner/tuner.h>

class Fft {
	public:
	Fft(Tuner * tuner);
	~Fft();
	void fft(double * in, complex * out, unsigned int n);
	void fft_rec(double * in, complex * out, unsigned int n, unsigned int offset,
			unsigned int d1, unsigned int step);

	void fft_spd(double * in, int n1, double wi, double dw, double * out, int n2);
	void fft_spd_diff(double * in, int n, double w, double & out_d1, double & out_d2);

	private:
	complex * wn;
};


#endif /* end of include guard: FFT_H */
