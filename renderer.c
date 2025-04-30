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

  SDL_SetRenderDrawColor(renderer, 0xDE, 0xAD, 0x06, 0xFF);

  /* draw all sprite components */
  const SDL_Rect rect = { 10, 10, 320, 240 };
  SDL_RenderFillRect(renderer, &rect);

  SDL_RenderPresent(renderer);
}
