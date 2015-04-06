
GCC=g++
LIBS=-lasound
FLAGS=-std=c++11 -fPIC

SRC=$(wildcard src/sound_system/*.cpp)

system: $(SRC)
#$(GCC) -o $@ $^ -Iinclude/ $(FLAGS) $(LIBS)
	$(GCC) -c $^ -Iinclude/ $(FLAGS) $(LIBS)

