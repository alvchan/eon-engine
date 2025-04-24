#include "SDL.h"

#include <stdbool.h>
#include <stdio.h>

/* wrapper macros over common SDL calls */
#define fillbg()  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0xDE, 0xAD, 0x06))
#define paintbg(r,g,b)  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, r, g, b))

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *surf = NULL;

static bool init(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("[error] Couldn't initialize SDL. SDL_Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  window = SDL_CreateWindow("SDL Tutorial",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("[error] Couldn't create a window. SDL_Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  surf = SDL_GetWindowSurface(window);
  fillbg();
  SDL_UpdateWindowSurface(window);

  return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
  /* can't recover from a startup panic, just quit */
  if (init() == EXIT_FAILURE)
    exit(EXIT_FAILURE);

  /* poll for quit event, hold window open until then */
  SDL_Event e;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  /* cleanup */
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
