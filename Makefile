GCC=g++
LIBS=-lasound
FLAGS=-std=c++11 -fPIC -ggdb
FLAGS_BIN=-std=c++11 -ggdb

SRC=$(wildcard src/sound_system/*.cpp) $(wildcard src/util/*.cpp)
#SRC=$(wildcard src/sound_system/*.cpp) 
OBJ=$(wildcard ./*.o)

bin: system
	$(GCC) -o main src/main.cpp $(OBJ) -Iinclude $(FLAGS_BIN) $(LIBS)

system: $(SRC)
#$(GCC) -o $@ $^ -Iinclude/ $(FLAGS) $(LIBS)
	$(GCC) -c $^ -Iinclude/ $(FLAGS) $(LIBS)

gui:
	g++ src/gui/main_app.cpp -o gui `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm -f *.o main

