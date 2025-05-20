#include <math.h>
#include <stdbool.h>

float distance(struct point *p1, struct point *p2) {
  float x = p2->x - p1->x;
  float y = p2->y - p1->y;

  return sqrt(x*x + y*y);
}

bool point_point_collision(struct point *p1, struct point *p2) {
  return p1->x == p2->x && p1->y == p2->y;
}

bool point_line_collision(struct point *p, struct line *l) {
  float dist1 = distance(p, l->p1);
  float dist2 = distance(p, l->p2);
  float len = distance(&l->p1, &l->p2);

  return dist1+dist2 >= len-epsilon && dist1+dist2 <= len+epsilon;
}

bool point_circle_collision(struct point *p, struct circle *c) {
  return distance(p, &c->p) <= c->radius;
}

bool point_rect_collision(struct point *p, struct rect *r) {
  return p->x >= r->x && p->x <= r->x + r->w
      && p->y >= r->y && p->y <= r->y + r->h;
}

bool line_line_collision(struct line l1, struct line l2) {
  return;
}

bool line_circle_collision(struct line l, struct circle c) {
  return;
}

bool line_rect_collision(struct line l, struct rect r) {
  return;
}

bool circle_circle_collision(struct circle c1, struct circle c2) {
  return distance(&c1->p, &c2->p) <= c1.radius + c2.radius;
}

bool circle_rect_collision(struct circle c, struct rect r) {
  return;
}

bool rect_rect_collision(struct rect r1, struct rect r2) {
  return;
}
