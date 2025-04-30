#include "SDL.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "eon.h"
#include "renderer.h"

#include <stdio.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x)

const unsigned int ffps = 60;
const Uint64 fdt = 1000/ffps;

lua_State *L = NULL;

/* TODO: free this on quit */
/* struct game_state *G = NULL; */

static void update(void) {
  Uint64 starttime = SDL_GetTicks();

  /* poll for quit event, hold window open until then */
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      cleanup();
    }
  }

  render_system();

  Uint64 endtime = SDL_GetTicks();
  Uint64 elapsed = endtime - starttime;

  /* delay frame to keep framerate ~constant */
  Uint64 delay;
  if (elapsed <= fdt)
    delay = fdt - elapsed;
  else
    delay = 0;

  SDL_Delay(delay);
}

int main(int argc, char **argv) {
  /* full argc, argv main signature required for SDL */
  UNUSED(argc);
  UNUSED(argv);

  /* initialize SDL and Lua state */
  sdl_init();
  L = luaL_newstate();
  luaL_openlibs(L);

  /* set lua bindings */
  /* ... */

  while (1) {
    update();
  }

  return EXIT_SUCCESS;
}

void cleanup(void) {
  if (L)
    lua_close(L);

  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Quit();

  exit(EXIT_SUCCESS);
}
