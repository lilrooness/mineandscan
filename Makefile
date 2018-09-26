all:
	gcc -c src/*.c
	gcc *.o `sdl2-config --libs` -lSDL2_image -o path
	rm *.o
