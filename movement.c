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

#include "eon.h"
#include "movement.h"

#include <stdio.h>

const int SPEED = 5;

void move_left(void) {
  G.sprites[0].rect.x -= SPEED * fdt;
}

void move_right(void) {
  G.sprites[0].rect.x += SPEED * fdt;
}

void move_up(void) {
  G.sprites[0].rect.y -= SPEED * fdt;
}

void move_down(void) {
  G.sprites[0].rect.y += SPEED * fdt;
}
