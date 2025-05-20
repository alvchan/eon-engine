#ifndef COLLISION_H
#define COLLISION_H

#define epsilon 0.05

struct point {
  float x, y;
};

struct line {
  struct point p1, p2;
};

struct circle {
  struct point p;
  float radius;
};

struct rect {
  float x, y;
  float w, h;
};

#endif
