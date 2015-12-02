#include <util/complex.h>
#include <cmath>


complex
complex::operator+(complex & c2) {
	complex tmp;
	tmp.real = real + c2.real;
	tmp.imag = imag + c2.imag;
	return tmp;
}



complex
complex::operator-(complex & c2) {
	complex tmp;
	tmp.real = real - c2.real;
	tmp.imag = imag - c2.imag;
	return tmp;
}


complex
complex::operator*(complex & c2) {
	complex tmp;
	tmp.real = real * c2.real - imag * c2.imag;
	tmp.imag = imag * c2.real + real * c2.imag;
	return tmp;
}

complex
complex::operator/(complex & c2) {
	complex tmp;
	double div = pow(c2.real, 2) + pow(c2.imag, 2);
	tmp.real = (real * c2.real + imag * c2.imag) / div;
	tmp.imag = (imag * c2.real - real * c2.imag) / div;
	return tmp;
}

/*
complex
complex::operator*(double r) {
	complex tmp;
	tmp.real = real * r;
	tmp.imag = imag * r;
	return tmp;
}*/
