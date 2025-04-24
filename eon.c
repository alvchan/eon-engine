#include "SDL.h"

#include <stdio.h>

/* wrapper macros over common SDL calls */
#define fillbg()  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0xDE, 0xAD, 0x06))
#define paintbg(r,g,b)  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, r, g, b))

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const unsigned int ffps = 60; /* fixed frame rate for physics */
const Uint64 fft = 1000/ffps; /* ms/frame for 60 fps */

SDL_Window *window = NULL;
SDL_Surface *surf = NULL;
SDL_Event event;

static void init(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("[error] Couldn't initialize SDL. SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  window = SDL_CreateWindow("SDL Tutorial",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("[error] Couldn't create a window. SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  surf = SDL_GetWindowSurface(window);
  fillbg();
  SDL_UpdateWindowSurface(window);
}

static void update(int i) {
  Uint64 starttime = SDL_GetTicks();

  /* poll for quit event, hold window open until then */
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      SDL_DestroyWindow(window);
      SDL_Quit();
      exit(EXIT_SUCCESS);
    }
  }

  /* Game Loop */
  printf("%d\n", i);

  Uint64 endtime = SDL_GetTicks();
  Uint64 elapsed = endtime - starttime;

  /* delay frame to keep framerate ~constant */
  Uint64 delay;
  if (elapsed <= fft)
    delay = fft - elapsed;
  else
    delay = 0;

  SDL_Delay(delay);
}

int main(int argc, char **argv) {
  init();

  int i = 0;
  while (1) {
    update(i++);
  }

  return EXIT_SUCCESS;
}
