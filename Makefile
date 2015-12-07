GCC=g++
LIBS=-lasound
FLAGS=-std=c++11 -fPIC -ggdb
FLAGS_BIN=-std=c++11 -ggdb
BINARY_NAME=netPtuner


SRC=$(wildcard src/sound_system/*.cpp) \
$(wildcard src/util/*.cpp) \
$(wildcard src/tuner/*.cpp) \
$(wildcard src/fft/*.cpp) \
$(wildcard src/network/*.cpp) \
$(wildcard src/gui/*.cpp) \

OBJ=array.o \
capture.o \
complex.o \
fft.o \
filter.o \
logger.o \
NeuronalNetwork.o \
player.o \
ProyectImplementation.o \
recorder_alsa.o \
recorder.o \
signal.o \
sound_system.o \
system_alsa.o \
system_jack.o \
system.o \
tuner.o \
vector.o \

$(BINARY_NAME): $(OBJ)
	$(GCC) -o $(BINARY_NAME) src/MainNeuronalNetwork.cpp $(OBJ) -Iinclude `pkg-config gtkmm-3.0 --cflags --libs` $(FLAGS_BIN) $(LIBS)

$(OBJ): $(SRC)
	$(GCC) -c $^ -Iinclude `pkg-config gtkmm-3.0 --cflags --libs` $(FLAGS) $(LIBS)

clean:
	rm -f *.o netPtuner

