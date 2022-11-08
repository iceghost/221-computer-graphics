#include "mesh.hpp"
#include <cmath>
#include <initializer_list>

hollow_box::hollow_box(int n, float dx, float dy, float dz, float in_dx,
                       float in_dz)
    : mesh(16 + (n - 1) * 8, 16 + (n - 1) * 6) {
  float hdx = dx / 2.0, hdy = dy / 2.0, hdz = dz / 2.0, in_hdz = in_dz / 2,
        r = in_dx / 2, angle = M_PI / n;

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
  int cid = 0;
  for (auto p = quad_strip.begin(); p < quad_strip.end() - 3; p += 2) {
    this->quads.push_back(mesh::quad({p[0], p[1], p[2], p[3]}, cid++));
    this->quads.push_back(
        mesh::quad({p[0] + n, p[1] + n, p[2] + n, p[3] + n}, cid++));
  }
  this->quads.push_back(mesh::quad({0, n, 3 * n + 2, 2 * n + 2}, cid++));
  this->quads.push_back(
      mesh::quad({4 * n + 4, 5 * n + 4, 7 * n + 6, 6 * n + 6}, cid++));

  auto small_strip = {0,         1,         n + 2,     n + 1,
                      3 * n + 3, 3 * n + 4, 2 * n + 3, 2 * n + 2};
  for (auto p = small_strip.begin(); p < small_strip.end() - 3; p += 2) {
    for (int i = 0; i < n; i++) {
      this->quads.push_back(
          mesh::quad({p[0] + i, p[1] + i, p[2] + i, p[3] + i}, cid++));
    }
    for (int i = 0; i < n; i++) {
      this->quads.push_back(
          mesh::quad({p[0] + i + 4 * n + 4, p[1] + i + 4 * n + 4,
                      p[2] + i + 4 * n + 4, p[3] + i + 4 * n + 4},
                     cid++));
    }
  }
}