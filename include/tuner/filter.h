#ifndef FILTER_H

#define FILTER_H

#include <cstring>
#include <cmath>
#include <util/vector.h>
#include <util/complex.h>


enum FilterType {CHEBY_TYPE}; 


#define max(a,b) (((a)<(b))?(b):(a))

class Filter {
	public:
	/* data = buffer of data getted from sound_system
	 * data_size = size of data array
	 * buffer = complete buffer of data
	 * buffer_size = size of buffer array
	 * */
	static void Butterworth(double * data, int data_size, 
			double * buffer, int buffer_size);


	void filter(unsigned int n, double * in, double * out);
	double filter_sample(double in);


	void set_oversampling(unsigned int o) { oversampling = o;}
	void set_filter_type(FilterType t) { type = t;}

	void reconfigure();

	Filter(FilterType, unsigned int o);
	~Filter();


	private:
	double * a;
	double * b; /* coefs  */
	double * s; /* status */

	double * _a;
	double * _b;

	unsigned int N;

	unsigned int Na, Nb;

	unsigned int oversampling;


	/* type of filter */
	FilterType type;


	void initiate_cheby_filter(unsigned int n, double Rp, double wc);
	void configure();
};


#endif /* end of include guard: FILTER_H */
