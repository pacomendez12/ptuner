#ifndef COMPLEX_H

#define COMPLEX_H
#include <string>

class complex {
	public:
	double real;
	double imag;

	complex() {
		real = 0;
		imag = 0;
	}

	complex(double r, double i) {
		real = r;
		imag = i;
	}

	std::string toString() {
		return "[" + std::to_string(real) + ", " + std::to_string(imag) + "]\n";
	}

	void setValues(double r, double i) {
		real = r;
		imag = i;
	}

	void setReal(double r) {
		real = r;
	}

	void setImaginary(double i) {
		imag = i;
	}

	double getReal() {
		return real;
	}

	double getImaginary() {
		return imag;
	}

	complex operator +(complex & c2);
	complex operator -(complex & c2);
	complex operator *(complex & c2);
	complex operator /(complex & c2);
	complex operator *(double r);

};


#endif /* end of include guard: COMPLEX_H */
