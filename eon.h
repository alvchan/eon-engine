#ifndef EON_H
#define EON_H

/* TODO: move to physics component */
const unsigned int ffps = 60; /* fixed frame rate for physics */
const Uint64 fdt = 1000/ffps; /* ms/frame for 60 fps */

extern SDL_Renderer *renderer;

struct game_state {
  struct sprite sprites[8];
};

#endif
