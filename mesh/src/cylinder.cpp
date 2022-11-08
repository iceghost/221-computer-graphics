#include "mesh.hpp"
#include <cmath>

cylinder::cylinder(int n, float h, float r)
    : nSegments(n), height(h), radius(r), mesh(2 * n + 2, n * 3) {
  float a = 2 * float(M_PI) / n;

  // top, topcirc, topcirc, topcirc, ..., bottomcirc, bottomcirc, bottom

  // top
  this->verts.push_back({0, h / 2, 0});
  for (int i = 0; i < n; i++) {
    this->verts.push_back({r * std::cos(a * i), h / 2, r * std::sin(a * i)});
  }
  // bottom
  for (int i = 0; i < n; i++) {
    this->verts.push_back({r * std::cos(a * i), -h / 2, r * std::sin(a * i)});
  }
  this->verts.push_back({0, -h / 2, 0});

  int cid = 0;
  // top face
  for (int i = 0; i < n - 1; i++) {
    this->quads.push_back(mesh::quad::from_triangle({0, i + 2, i + 1}, cid++));
  }
  this->quads.push_back(mesh::quad::from_triangle({0, 1, n}, cid++));

  // bottom face
  for (int i = 0; i < n - 1; i++) {
    this->quads.push_back(
        mesh::quad::from_triangle({2 * n + 1, i + 1 + n, i + 2 + n}, cid++));
  }
  this->quads.push_back(
      mesh::quad::from_triangle({2 * n + 1, 2 * n, 1 + n}, cid++));

  // sides
  for (int i = 0; i < n - 1; i++) {
    this->quads.push_back(
        mesh::quad({i + 1, i + 2, i + 2 + n, i + 1 + n}, cid++));
  }
  this->quads.push_back(mesh::quad({n, 1, 1 + n, 2 * n}, cid++));
}