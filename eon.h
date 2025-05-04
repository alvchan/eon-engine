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

#ifndef EON_H
#define EON_H

#include "renderer.h"
#include "sprite.h"

/* TODO: move to physics component */
extern const unsigned int ffps; /* fixed frame rate for physics */
extern const Uint64 fdt; /* ms/frame for 60 fps */

extern SDL_Renderer *renderer;

struct game_state {
  struct sprite *sprites;
};

extern struct game_state G;

void cleanup(void);

#endif
