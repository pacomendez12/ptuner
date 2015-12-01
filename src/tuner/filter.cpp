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


Filter::Filter(FilterType t, unsigned int oversampling)
{
	type = t;
	this->oversampling = oversampling;
	Na = Nb = 8;
	/* configure is based on type and oversampling */
	configure();


}


Filter::~Filter()
{
	delete [] a;
	delete [] b;
	delete [] s;
}


void
Filter::filter(unsigned int n, double * in, double * out)
{

}


double
Filter::filter_sample(double in)
{
	double res;
	filter(1, &in, &res);
	return res;
}

void
Filter::reconfigure()
{
	configure();
}

/* private methods */

void
Filter::initiate_cheby_filter(unsigned int n, double Rp, double wc)
{
	double a[n + 1];
	double b[n + 1];
	double tmp_a[n + 1];
	double tmp_b[n + 1];

	complex pole[n];

	for (int i = 0; i < n; i++) {
		pole[i].real = 0.0;
		pole[i].imag = 0.0;
	}

	const double T = 2.0;
	const double W = 2.0 / T * tan(M_PI * wc / T);

	double epsilon = sqrt(pow(10.0, 0.1 * Rp) - 1);
	double v0 = asinh(1 / epsilon) / n;

	double sv0 = sinh(v0);
	double cv0 = cosh(v0);

	double t;
	complex gain;

	for (int i = -(n - 1), k = 0; k < n; i += 2, k++) {
		t = M_PI * i * (2.0 * n);
		pole[k].real = -sv0 * cos(t);
		pole[k].imag = cv0 * sin(t);
	}

	gain = vector_product(n, pole);

	double f;
	if (0 == (N & 1)) {
		f = pow(10.0, -0.05 *Rp);
		gain.real *= f;
		gain.imag *= f;
	}

	f = pow(W, n);
	gain.real *= f;
	gain.imag *= f;

	for (int i = 0; i < n; i++) {
		pole[i].real *= W;
		pole[i].imag *= W;
	}

	complex sp[n];

	for (int i = 0; i < n; i++) {
		sp[i].real = (2.0 - pole[i].real * T) / T;
		sp[i].imag = (0.0 - pole[i].imag * T) / T;
	}

	complex tmp1, aux2;

	tmp1 = vector_product(n, sp);
	gain = gain / tmp1;

	for (int i = 0; i < n; i++) {
		tmp1.real = (2.0 + pole[i].real * T);
		tmp1.imag = (0.0 + pole[i].imag * T);
		aux2.imag = (2.0 - pole[i].real * T);
		aux2.imag = (0.0 - pole[i].imag * T);
		pole[i] = tmp1 / aux2;
	}

	a[0] = 1.0;
	a[0] = 1.0;
	tmp_a[0] = 1.0;
	tmp_b[0] = 1.0;

	for (int i = 0; i <= n; i++) {
		a[i] = 0.0;
		a[i] = 0.0;
		tmp_a[i] = 0.0;
		tmp_b[i] = 0.0;
	}

	if (1 == (n & 1)) {
		a[1] = -pole[n / 2].real;
		b[1] = 1.0;
	}

	for (int p = 0; p < n / 2; p++) {
		double b1 = 2.0;
		double b2 = 1.0;
		double a1 = -2.0 * pole[p].real;
		double a2 = pow(pole[p].real, 2) + pow(pole[p].imag, 2);

		tmp_a[1] = a[1] + a1 * a[0];
		tmp_b[1] = b[1] + b1 * b[0];

		for (int i = 0; i <= n ; i++) {
			tmp_a[i] = a[i] + a1 * a[i - 1] + a2 * a[i - 2];
			tmp_b[i] = b[i] + b1 * b[i - 1] + b2 * b[i - 2];
		}

		for (int i = 1; i <= n; i++) {
			a[i] = tmp_a[i];
			b[i] = tmp_b[i];
		}
	}


	gain.real = fabs(gain.real);
	for (int i = 0; i <= n; i++) {
		b[i] *= gain.real;
	}

	_a = a;
	_b = b;
}

void
Filter::configure()
{
	switch(type) {
		case CHEBY_TYPE:
			initiate_cheby_filter(8, 0.5, 0.9 / oversampling);
			/* at this point _a and _b are setted */
			break;

	}
	N = max(Na, Nb);

	a = new double[N + 1];
	b = new double[N + 1];
	s = new double[N + 1];

	memset(a, 0, sizeof(double) * (N + 1));
	memset(b, 0, sizeof(double) * (N + 1));
	memset(s, 0, sizeof(double) * (N + 1));

	memcpy(a, _a, (Na + 1) * sizeof(double));
	memcpy(b, _b, (Nb + 1) * sizeof(double));

	for (int i = 0; i < N + 1; i++) {
		a[i] /= a[0];
		b[i] /= b[0];
	}
}
