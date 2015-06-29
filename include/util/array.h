#ifndef ARRAY_H

#define ARRAY_H

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x) [0]))

template <typename T>
inline bool value_in_array(T value, T * array, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		if (array[i] == value)
			return true;
	}
	return false;
}



#endif /* end of include guard: ARRAY_H */
