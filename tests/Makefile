GCC=gcc
LIBS=-lasound

play: play.o
	$(GCC) play.o -o play $(LIBS)
	rm -rf *.o

play.o: play.c
	$(GCC) -c play.c

clean:
	rm -rf *.o play
