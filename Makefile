SDL_FLAGS = $(shell pkg-config --cflags --libs SDL2_image) $(shell sdl2-config --cflags --libs)
LUA_FLAGS = $(shell pkg-config --cflags --libs lua)

.PHONY: all
all: eon.c eon.h renderer.o
	gcc -o eon-engine renderer.o eon.c -O2 -Wall -Wextra -DNDEBUG $(SDL_FLAGS) $(LUA_FLAGS)

renderer.o: renderer.c renderer.h eon.h
	gcc -c renderer.c $(SDL_FLAGS)

movement.o: eon.h
	gcc -c movement.c $(SDL_FLAGS)

.PHONY: clean debug
clean:
	rm -f *.o eon-engine

debug: eon.c eon.h renderer.o movement.o
	gcc -o eon-engine renderer.o movement.o eon.c -g -Wall -Wextra -D_DEBUG $(SDL_FLAGS) $(LUA_FLAGS)
