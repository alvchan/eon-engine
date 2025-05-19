/*
 * Copyright (C) 2025 Alvin Chan
 * 
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "SDL.h"
#include "SDL_image.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "eon.h"
#include "renderer.h"

#ifdef DEBUG_MODE
#include "movement.h"
#endif

#include <stdio.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x)

const unsigned int ffps = 60;
const Uint64 fdt = 1000/ffps;

lua_State *L = NULL;

unsigned int num_sprites = 8;

/* TODO: free this on quit */
/* TODO: init this */
struct game_state G;

static void update(void) {
  Uint64 starttime = SDL_GetTicks();

  /* poll for quit event, hold window open until then */
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      cleanup();
    }

#ifdef DEBUG_MODE
    /* movement code for demo/testing; not to be used otherwise */
    else if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
        case SDLK_UP:
          move_up();
          break;

        case SDLK_DOWN:
          move_down();
          break;

        case SDLK_LEFT:
          move_left();
          break;

        case SDLK_RIGHT:
          move_right();
          break;

        default:
          puts("wutt");
          break;
      }
    }
#endif

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
  /* full argc, argv main signature required for SDL; this stops compiler warnings */
  UNUSED(argc);
  UNUSED(argv);

  /* initialize SDL and Lua state */
  sdl_init();
  L = luaL_newstate();
  luaL_openlibs(L);

  /* set lua bindings */
  /* ... */

  struct sprite sp = {
    .rect = { 96, 96, 256, 256 },
    .r = 0xDE,
    .g = 0xAD,
    .b = 0x06
  };

  G = (struct game_state){ malloc(sizeof(struct sprite) * num_sprites) };
  G.sprites[0] = sp;
  G.sprites[1] = (struct sprite){ {0,0,256,256}, 0xFF, 0x0, 0x0 };
  G.sprites[2] = (struct sprite){ {32,32,256,256}, 0x0, 0xFF, 0x0 };
  G.sprites[3] = (struct sprite){ {64,64,256,256}, 0x0, 0x0, 0xFF };

  while (1) {
    update();
  }

  cleanup();

  return EXIT_SUCCESS;
}

void cleanup(void) {
  if (L)
    lua_close(L);

  if (texture)
    SDL_DestroyTexture(texture);
  free(G.sprites);

  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Quit();

  exit(EXIT_SUCCESS);
}
