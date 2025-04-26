#include "SDL.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include <stdio.h>

/* wrapper macros over common SDL calls */
#define fillbg()  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0xDE, 0xAD, 0x06))
#define paintbg(r,g,b)  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, r, g, b))

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const unsigned int ffps = 60; /* fixed frame rate for physics */
const Uint64 fdt = 1000/ffps; /* ms/frame for 60 fps */

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;

lua_State *L = NULL;

static void sdl_init(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("[error] Couldn't initialize SDL. SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  window = SDL_CreateWindow("Eon Engine",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("[error] Couldn't create a window. SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
}

static void update(void) {
  Uint64 starttime = SDL_GetTicks();

  /* poll for quit event, hold window open until then */
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      lua_close(L);

      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();

      exit(EXIT_SUCCESS);
    }
  }


  /* Game Loop */
  luaL_dostring(L, "print(fdeltatime)");

  /* -- end of game loop section -- */


  /* Rendering */
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 0xDE, 0xAD, 0x06, 0xFF);
  const SDL_Rect rect = { 10, 10, 320, 240 };
  SDL_RenderFillRect(renderer, &rect);

  SDL_RenderPresent(renderer);

  /* -- end of rendering section -- */


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
  /* initialize SDL and Lua state */
  sdl_init();
  L = luaL_newstate();
  luaL_openlibs(L);

  lua_pushnumber(L, ffps);
  lua_setglobal(L, "fframerate");
  lua_pushnumber(L, fdt);
  lua_setglobal(L, "fdeltatime");

  while (1) {
    update();
  }

  return EXIT_SUCCESS;
}
