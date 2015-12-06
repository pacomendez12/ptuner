GCC=g++
LIBS=-lasound
FLAGS=-std=c++11 -fPIC -ggdb
FLAGS_BIN=-std=c++11 -ggdb


SRC=$(wildcard src/sound_system/*.cpp) $(wildcard src/util/*.cpp) $(wildcard src/tuner/*.cpp) $(wildcard src/fft/*.cpp)
GUI_SRC=$(wildcard src/gui/*.cpp)
NET_SRC=$(wildcard src/network/*.cpp) $(wildcard src/gui/*.cpp)
#SRC=$(wildcard src/sound_system/*.cpp) 
OBJ=$(wildcard ./*.o)

bin: system
	$(GCC) -o main src/main.cpp $(OBJ) -Iinclude $(FLAGS_BIN) $(LIBS)

system: $(SRC)
	$(GCC) -c $^ -Iinclude `pkg-config gtkmm-3.0 --cflags --libs` $(FLAGS) $(LIBS)

gui: $(GUI_SRC)
	$(GCC) src/gui/main_app.cpp -o gui -Iinclude/gui `pkg-config gtkmm-3.0 --cflags --libs` $(FLAGS)

net: net_make system
	$(GCC) -o net src/MainNeuronalNetwork.cpp $(OBJ) -Iinclude `pkg-config gtkmm-3.0 --cflags --libs` $(FLAGS_BIN) $(LIBS)

net_make: $(NET_SRC)
	$(GCC) -c $^ -Iinclude `pkg-config gtkmm-3.0 --cflags --libs` $(FLAGS) $(LIBS)

clean:
	rm -f *.o main

