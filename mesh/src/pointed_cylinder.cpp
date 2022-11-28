#include "mesh.hpp"
#include <cmath>

PointedCylinder::PointedCylinder(int n, float h, float r, float t)
    : Mesh(Cylinder(n, h, r)) {
  this->verts[0].y += t;
  const float angle = 2 * float(M_PI) / n;
  const float R_DIV_RT = r * r / (r * r + t * t);
  const float T_DIV_RT = t * t / (r * r + t * t);
  const auto vector_t = Vector3(0, t, 0);
  for (int i = 2 * n; i < 3 * n; i++) {
    auto vector_r =
        Vector3(r * std::cos(i * angle), 0, r * std::sin(i * angle));
    this->norms[i].dx = T_DIV_RT * vector_r.dx + R_DIV_RT * vector_r.dx;
    this->norms[i].dy = T_DIV_RT * vector_r.dy + R_DIV_RT * vector_r.dy;
    this->norms[i].dz = T_DIV_RT * vector_r.dz + R_DIV_RT * vector_r.dz;
    this->norms[i] = this->norms[i].normalize();
  }
}