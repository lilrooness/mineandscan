CC := gcc 

all:
	gcc -c src/*.c
	$(CC) *.o `sdl2-config --libs` -lSDL2_image 
	rm *.o

osx: 
	gcc -c src/*.c
	$(CC) *.o -framework SDL2 -framework SDL2_image 
	rm *.o

