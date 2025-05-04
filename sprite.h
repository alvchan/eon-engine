#ifndef SPRITE_H
#define SPRITE_H

extern unsigned int num_sprites;

struct sprite {
  SDL_Rect rect;
  Uint8 r;
  Uint8 g;
  Uint8 b;
};

#endif
