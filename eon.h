#ifndef EON_H
#define EON_H

#include "renderer.h"

/* TODO: move to physics component */
extern const unsigned int ffps; /* fixed frame rate for physics */
extern const Uint64 fdt; /* ms/frame for 60 fps */

extern SDL_Renderer *renderer;

/*
struct game_state {
  struct sprite sprites[8];
};
*/

void cleanup(void);

#endif
