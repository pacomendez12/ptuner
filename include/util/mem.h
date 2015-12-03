#ifndef MEM_H

#define MEM_H



template<typename T>
void inline safe_delete_array(T * ptr)
{
	if (ptr) {
		delete [] ptr;
		ptr = NULL;
	}
}

template<typename T>
void inline safe_delete(T * ptr)
{
	if (ptr) {
		delete ptr;
		ptr = NULL;
	}
}


#endif /* end of include guard: MEM_H */
