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

template <typename T>
void print_array(T array, int size)
{
	for (int i = 0; i < size; i++) {
		printf("%d\n", array[i]);
	}
}



#endif /* end of include guard: ARRAY_H */
