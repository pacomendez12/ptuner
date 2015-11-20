#include <util/complex.h>


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
complex::operator*(double r) {
	complex tmp;
	tmp.real = real * r;
	tmp.imag = imag * r;
	return tmp;
}
