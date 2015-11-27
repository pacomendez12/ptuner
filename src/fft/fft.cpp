#include <fft/fft.h>
#include <cmath>

void 
Fft::fft(complex * data, int n)
{
    double norm = sqrt(1.0 / n);

    for (int i = 0, j = 0; i < n; i++)
    {
	if (j >= i)
	{
	    double tr = data[j].real * norm;

	    data[j].real = data[i].real * norm;
	    data[j].imag = 0.0;

	    data[i].real = tr;
	    data[i].imag = 0.0;
	}

	int m = n / 2;
	while (m >= 1 && j >= m)
	{
	    j -= m;
	    m /= 2;
	}
	j += m;
    }
    
    for (int mmax = 1, istep = 2 * mmax; mmax < n;
	 mmax = istep, istep = 2 * mmax)
    {
	double delta = (M_PI / mmax);
	for (int m = 0; m < mmax; m++)
	{
	    double w = m * delta;
	    double wr = cos(w);
	    double wi = sin(w);

	    for (int i = m; i < n; i += istep)
	    {
		int j = i + mmax;
		double tr = wr * data[j].real - wi * data[j].imag;
		double ti = wr * data[j].imag + wi * data[j].real;
		data[j].real = data[i].real - tr;
		data[j].imag = data[i].imag - ti;
		data[i].real += tr;
		data[i].imag += ti;
	    }
	}
    }
}


