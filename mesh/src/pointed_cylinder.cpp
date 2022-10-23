#include "pointed_cylinder.h"
#include "cylinder.h"

pointed_cylinder::pointed_cylinder(int n, float h, float r, float t)
    : mesh(cylinder(n, h, r)) {
  this->verts[0].y += t;
}