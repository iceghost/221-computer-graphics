#include "mesh.hpp"
#include <cmath>

Cylinder::Cylinder(int n, float h, float r)
    : nSegments(n), height(h), radius(r), Mesh(2 * n + 2, n * 3) {
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

  for (int i = 0; i < n; i++) {
    this->norms.push_back({0, 1, 0});
  }
  for (int i = 0; i < n; i++) {
    this->norms.push_back({0, -1, 0});
  }
  for (int i = 0; i < n; i++) {
    this->norms.push_back({std::cos(a * i), 0, std::sin(a * i)});
  }

  int nid = 0;
  // top face
  for (int i = 0; i < n - 1; i++) {
    this->quads.push_back(Mesh::Quad::from_triangle({0, i + 2, i + 1}, nid++));
  }
  this->quads.push_back(Mesh::Quad::from_triangle({0, 1, n}, nid++));

  // bottom face
  for (int i = 0; i < n - 1; i++) {
    this->quads.push_back(
        Mesh::Quad::from_triangle({2 * n + 1, i + 1 + n, i + 2 + n}, nid++));
  }
  this->quads.push_back(
      Mesh::Quad::from_triangle({2 * n + 1, 2 * n, 1 + n}, nid++));

  // sides
  for (int i = 0; i < n - 1; i++) {
    this->quads.push_back(
        Mesh::Quad({i + 1, i + 2, i + 2 + n, i + 1 + n}, nid++));
  }
  this->quads.push_back(Mesh::Quad({n, 1, 1 + n, 2 * n}, nid++));
}