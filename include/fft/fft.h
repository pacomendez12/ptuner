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


	private:
	complex * wn;
};


#endif /* end of include guard: FFT_H */
