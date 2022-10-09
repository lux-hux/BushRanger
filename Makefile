#_*_MakeFile_*_

CC=clang
CFLAGS= -g `pkg-config --libs --cflags sdl2` `pkg-config --libs --cflags sdl2_image` `pkg-config --libs --cflags sdl2_ttf`

all: windy

windy: main.o sdl_functions.o functions.o
	$(CC) main.o sdl_functions.o functions.o  $(CFLAGS) -o windy


main.o: main.c
	$(CC) $(CFLAGS) -c main.c

sdl_functions.o: sdl_functions.c
	$(CC) $(CFLAGS) -c sdl_functions.c


functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c


clean:
	rm *.o windy
