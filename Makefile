#_*_MakeFile_*_

CC=clang
CFLAGS= `pkg-config --libs --cflags sdl2` `pkg-config --libs --cflags sdl2_image` `pkg-config --libs --cflags sdl2_ttf`

all: bushy

bushy: sdl_functions.o main.o functions.o
	$(CC) sdl_functions.o main.o functions.o  $(CFLAGS) -o bushy

sdl_functions.o: sdl_functions.c
	$(CC) $(CFLAGS) -c sdl_functions.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c


clean:
	rm *.o bushy
