SDL_FLAGS = $(shell sdl2-config --cflags --libs)
LUA_FLAGS = $(shell pkg-config --cflags --libs lua)

eon: eon.c
	gcc -o eon-engine eon.c $(SDL_FLAGS) $(LUA_FLAGS)
