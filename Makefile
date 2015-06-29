GCC=g++
LIBS=-lasound
FLAGS=-std=c++11 -fPIC
FLAGS_BIN=-std=c++11

SRC=$(wildcard src/sound_system/*.cpp) $(wildcard src/util/*.cpp)
#SRC=$(wildcard src/sound_system/*.cpp) 
OBJ=$(wildcard ./*.o)

bin: system
	$(GCC) -o main src/main.cpp $(OBJ) -Iinclude $(FLAGS_BIN) $(LIBS)

system: $(SRC)
#$(GCC) -o $@ $^ -Iinclude/ $(FLAGS) $(LIBS)
	$(GCC) -c $^ -Iinclude/ $(FLAGS) $(LIBS)


clean:
	rm -f *.o main

