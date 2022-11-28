#include "mesh.hpp"
#include <cmath>

HollowCylinder::HollowCylinder(int n, float h, float R, float r)
    : Mesh(n * 4, n * 4) {
  float angle = 2 * float(M_PI) / n;
  for (int i = 0; i < n; i++) {
    this->verts.push_back(
        {r * std::cos(angle * i), h / 2, r * std::sin(angle * i)});
  }
  for (int i = 0; i < n; i++) {
    this->verts.push_back(
        {r * std::cos(angle * i), -h / 2, r * std::sin(angle * i)});
  }
  for (int i = 0; i < n; i++) {
    this->verts.push_back(
        {R * std::cos(angle * i), h / 2, R * std::sin(angle * i)});
  }
  for (int i = 0; i < n; i++) {
    this->verts.push_back(
        {R * std::cos(angle * i), -h / 2, R * std::sin(angle * i)});
  }

  for (int i = 0; i < n; i++) {
    this->norms.push_back({std::cos(angle * i), 0, std::sin(angle * i)});
  }
  for (int i = 0; i < n; i++) {
    this->norms.push_back({-std::cos(angle * i), 0, -std::sin(angle * i)});
  }
  for (int i = 0; i < n; i++) {
    this->norms.push_back({0, 1, 0});
  }
  for (int i = 0; i < n; i++) {
    this->norms.push_back({0, -1, 0});
  }

  // outside
  int nid = 0;
  for (int i = 0; i < n - 1; i++) {
    this->quads.push_back(Mesh::Quad({i, i + 1, i + 1 + n, i + n}, nid++));
  }
  this->quads.push_back(Mesh::Quad({n - 1, 0, n, 2 * n - 1}, nid++));

  // inside
  for (int i = 2 * n; i < 3 * n - 1; i++) {
    this->quads.push_back(Mesh::Quad({i, i + 1, i + 1 + n, i + n}, nid++));
  }
  this->quads.push_back(
      Mesh::Quad({3 * n - 1, 2 * n, 3 * n, 4 * n - 1}, nid++));

  // top
  for (int i = 0; i < n - 1; i++) {
    this->quads.push_back(
        Mesh::Quad({i, i + 1, i + 1 + 2 * n, i + 2 * n}, nid++));
  }
  this->quads.push_back(Mesh::Quad({n - 1, 0, 2 * n, 3 * n - 1}, nid++));

  // bottom
  for (int i = 0; i < n - 1; i++) {
    this->quads.push_back(
        Mesh::Quad({i + n, i + n + 1, i + 1 + 3 * n, i + 3 * n}, nid++));
  }
  this->quads.push_back(Mesh::Quad({2 * n - 1, n, 3 * n, 4 * n - 1}, nid++));
}