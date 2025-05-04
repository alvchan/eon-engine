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

#include "eon.h"
#include "renderer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;

void sdl_init(void) {
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

  if (renderer == NULL) {
    printf("[error] Couldn't create a renderer. SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void render_system(void) {
  SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
  SDL_RenderClear(renderer);

  /* draw all sprite components */
  for (int i = 0; i < num_sprites; i++) {
    SDL_SetRenderDrawColor(renderer, G.sprites[i].r, G.sprites[i].g, G.sprites[i].b, 0xFF);
    SDL_RenderFillRect(renderer, &(G.sprites[i].rect));
  }

  SDL_RenderPresent(renderer);
}
