#include <util/vector.h>

complex
vector_product(int n, complex * v)
{
	complex res(1.0, 0.0);
	complex aux;

	for (int i = 0; i < n; i++) {
		aux.real = -v[i].real;
		aux.imag = -v[i].imag;
		res = res * aux;
	}
	return res;
}
