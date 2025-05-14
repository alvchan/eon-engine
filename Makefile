SDL_FLAGS = $(shell pkg-config --cflags --libs SDL2_image) $(shell sdl2-config --cflags --libs)
LUA_FLAGS = $(shell pkg-config --cflags --libs lua)

eon-engine: eon.c eon.h renderer.o
	gcc -o eon-engine renderer.o eon.c -Wall -Wextra $(SDL_FLAGS) $(LUA_FLAGS)

renderer.o: renderer.c renderer.h eon.h
	gcc -c renderer.c $(SDL_FLAGS)

.PHONY: clean
clean:
	rm -rf *.o eon-engine
