#include "mesh.hpp"

PointedCylinder::PointedCylinder(int n, float h, float r, float t)
    : Mesh(Cylinder(n, h, r)) {
  this->verts[0].y += t;
}