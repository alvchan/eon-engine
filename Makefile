SDL_FLAGS = $(shell sdl2-config --cflags --libs)

eon: eon.c
	gcc -o eon-engine eon.c $(SDL_FLAGS)
