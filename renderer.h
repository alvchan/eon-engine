#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;

void sdl_init(void);
void render_system(void);

#endif
