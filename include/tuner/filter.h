#ifndef FILTER_H

#define FILTER_H



class Filter {
	public:
	/* data = buffer of data getted from sound_system
	 * data_size = size of data array
	 * buffer = complete buffer of data
	 * buffer_size = size of buffer array
	 * */
	static void Butterworth(double * data, int data_size, 
			double * buffer, int buffer_size);

};


#endif /* end of include guard: FILTER_H */
