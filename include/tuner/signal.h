#ifndef SIGNAL_H

#define SIGNAL_H

#include <tuner/tuner.h>

class Signal {
	public:
	Signal(Tuner * tuner);
	int get_fundamental_peak(double * x, double * y, int n);
	bool is_peak(double * buffer, int index);

	int get_max(double * buffer, int n);


	private:
	Tuner * tuner;
};

#endif /* end of include guard: SIGNAL_H */
