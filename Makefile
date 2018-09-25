all:
	gcc src/main.c `sdl2-config --libs` -lSDL2_image -o path
