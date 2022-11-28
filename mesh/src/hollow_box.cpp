#include "mesh.hpp"
#include <cmath>
#include <initializer_list>

HollowBox::HollowBox(int n, float dx, float dy, float dz, float in_dx,
                     float in_dz)
    : Mesh(16 + (n - 1) * 8, 16 + (n - 1) * 6) {
  float hdx = dx / 2.0f, hdy = dy / 2.0f, hdz = dz / 2.0f, in_hdz = in_dz / 2,
        r = in_dx / 2, angle = float(M_PI) / n;

  for (int i = 0; i <= n; i++) {
    this->verts.push_back({-hdx + i * dx / n, hdy, hdz});
  }
  for (int i = 0; i <= n; i++) {
    this->verts.push_back(
        {-r * std::cos(angle * i), hdy, in_hdz - r + r * std::sin(angle * i)});
  }

  for (int i = 0; i <= n; i++) {
    this->verts.push_back({-hdx + i * dx / n, -hdy, hdz});
  }
  for (int i = 0; i <= n; i++) {
    this->verts.push_back(
        {-r * std::cos(angle * i), -hdy, in_hdz - r + r * std::sin(angle * i)});
  }

  for (int i = 0; i <= n; i++) {
    this->verts.push_back({-hdx + i * dx / n, hdy, -hdz});
  }
  for (int i = 0; i <= n; i++) {
    this->verts.push_back(
        {-r * std::cos(angle * i), hdy, -in_hdz + r - r * std::sin(angle * i)});
  }

  for (int i = 0; i <= n; i++) {
    this->verts.push_back({-hdx + i * dx / n, -hdy, -hdz});
  }
  for (int i = 0; i <= n; i++) {
    this->verts.push_back({-r * std::cos(angle * i), -hdy,
                           -in_hdz + r - r * std::sin(angle * i)});
  }

  auto quad_strip = {
      0,         4 * n + 4, 5 * n + 5, n + 1, 3 * n + 3,
      7 * n + 7, 6 * n + 6, 2 * n + 2, 0,     4 * n + 4,
  };

  this->norms.push_back({0, 1, 0});
  this->norms.push_back({0, 1, 0});
  this->norms.push_back({1, 0, 0});
  this->norms.push_back({-1, 0, 0});
  this->norms.push_back({0, -1, 0});
  this->norms.push_back({0, -1, 0});
  this->norms.push_back({-1, 0, 0});
  this->norms.push_back({1, 0, 0});
  this->norms.push_back({0, 0, 1});
  this->norms.push_back({0, 0, -1});

  for (int i = 0; i < n; i++) {
    this->norms.push_back({0, 1, 0});
  }
  for (int i = 0; i < n; i++) {
    this->norms.push_back({0, 1, 0});
  }
  for (int i = 0; i < n; i++) {
    this->norms.push_back({std::cos(angle * i), 0, -std::sin(angle * i)});
  }
  for (int i = 0; i < n; i++) {
    this->norms.push_back({std::cos(angle * i), 0, std::sin(angle * i)});
  }
  for (int i = 0; i < n; i++) {
    this->norms.push_back({0, -1, 0});
  }
  for (int i = 0; i < n; i++) {
    this->norms.push_back({0, -1, 0});
  }

  int nid = 0;
  for (auto p = quad_strip.begin(); p < quad_strip.end() - 3; p += 2) {
    this->quads.push_back(Mesh::Quad({p[0], p[1], p[2], p[3]}, nid++));
    this->quads.push_back(
        Mesh::Quad({p[0] + n, p[1] + n, p[2] + n, p[3] + n}, nid++));
  }
  this->quads.push_back(Mesh::Quad({0, n, 3 * n + 2, 2 * n + 2}, nid++));
  this->quads.push_back(
      Mesh::Quad({4 * n + 4, 5 * n + 4, 7 * n + 6, 6 * n + 6}, nid++));

  auto small_strip = {0,         1,         n + 2,     n + 1,
                      3 * n + 3, 3 * n + 4, 2 * n + 3, 2 * n + 2};
  for (auto p = small_strip.begin(); p < small_strip.end() - 3; p += 2) {
    for (int i = 0; i < n; i++) {
      this->quads.push_back(
          Mesh::Quad({p[0] + i, p[1] + i, p[2] + i, p[3] + i}, nid++));
    }
    for (int i = 0; i < n; i++) {
      this->quads.push_back(
          Mesh::Quad({p[0] + i + 4 * n + 4, p[1] + i + 4 * n + 4,
                      p[2] + i + 4 * n + 4, p[3] + i + 4 * n + 4},
                     nid++));
    }
  }
}