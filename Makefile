CC := gcc -Wno-discarded-qualifiers

all:
	$(CC) -c src/*.c
	$(CC) *.o `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
	rm *.o

osx: 
	gcc -c src/*.c
	$(CC) *.o -framework SDL2 -framework SDL2_image -framework SDL2_ttf
	rm *.o

