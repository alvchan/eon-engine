SDL_FLAGS = $(shell sdl2-config --cflags --libs)
LUA_FLAGS = $(shell pkg-config --cflags --libs lua)

eon-engine: eon.c eon.h
	gcc -o eon-engine eon.c $(SDL_FLAGS) $(LUA_FLAGS)

.PHONY: clean
clean:
	rm -rf *.o eon-engine
