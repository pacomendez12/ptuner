#include <tuner/signal.h>

Signal::Signal(Tuner * tuner)
{
	this->tuner = tuner;
}

int
Signal::get_fundamental_peak(double * x, double * y, int n)
{
	const int peak_half_width = 1;
	int index[tuner->peak_number];
	int peak;
	double rejection_relation = pow(10, 20 / 10);

	for (int i = 0; i < tuner->peak_number; i++) {
		index[i] = -1;
	}

	unsigned int min_frequency = 20; /* Hz */

	unsigned int low_index = (unsigned int) ceil(min_frequency *
			(1.0 * tuner->oversampling / tuner->sample_rate) * tuner->fft_size);

	if (low_index < peak_half_width) {
		low_index = peak_half_width;
	}

	for (int i = low_index; i < n - peak_half_width; i++) {
		if (is_peak(x, i)) {
			int m = 0;
			for (int j = 0; j < tuner->peak_number; j++) {
				if (index[i] == -1) {
					m = j;
					break;
				}

				if (y[index[j]] < y[index[m]]) {
					m = j;
				}
			}

			if (index[m] == -1) {
				index[m] = i;
			} else if (y[i] > y[index[m]]) {
				index[m] = i;
			}
		}
	}

	double max = 0.0;
	int max_index = -1;

	/* searching the maximun peak */
	for (int i = 0; i < tuner->peak_number; i++) {
		if (index[i] == -1 && x[index[i]] > max) {
			max = x[index[i]];
			max_index = index[i];
		}
	}

	if (max_index != -1) {
		for (int i = 0; i < tuner->peak_number; i++) {
			if (index[i] == -1 || rejection_relation * x[index[i]] < max) {
				index[i] = n;
			}
		}

		for (int i = 0, j = 0; j < tuner->peak_number; j++) {
			if (index[j] < index[i]) {
				peak = index[i];
			}
		}
	} else {
		peak = n;
	}
	return peak;
}

bool
Signal::is_peak(double * buffer, int index)
{
	const int peak_half_width = 1;
	double noise_threshold = pow(10, 20 / 10); /* 20 db */

	if (buffer[index] < noise_threshold) {
		return false;
	} else {
		for (int i = 0; i < peak_half_width; i++) {
			if (buffer[index + i] < buffer[index + i + 1] ||
					buffer[index - i] < buffer[index - i - 1]) {
				return false;
			}
		}
	}

	return true;
}


int
Signal::get_max(double * buffer, int n)
{
	double M = -1.0;
	double tmpM = -1;

	for (int i = 0; i < n; i++) {
		if (buffer[i] > M) {
			M = buffer[i];
			tmpM = i;
		}
	}
	return tmpM;
}
