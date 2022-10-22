#include "slid.h"

slid::slid(float dx, float dy, float dz, float width, float depth)
    : mesh(16, 14) {
  float hdx = dx / 2, hdy = dy / 2, hdz = dz / 2, hw = width / 2;
  this->verts = {// big box
                 {-hdx, hdy, hdz},
                 {hdx, hdy, hdz},
                 {hdx, -hdy, hdz},
                 {-hdx, -hdy, hdz},
                 {-hdx, hdy, -hdz},
                 {hdx, hdy, -hdz},
                 {hdx, -hdy, -hdz},
                 {-hdx, -hdy, -hdz},
                 //  small box
                 {-hw, hdy, hdz},
                 {hw, hdy, hdz},
                 {hw, hdy - depth, hdz},
                 {-hw, hdy - depth, hdz},
                 {-hw, hdy, -hdz},
                 {hw, hdy, -hdz},
                 {hw, hdy - depth, -hdz},
                 {-hw, hdy - depth, -hdz}};

  this->quads = {// +y face
                 mesh::quad({0, 8, 11, 3}, 0), mesh::quad({11, 10, 2, 3}, 1),
                 mesh::quad({9, 1, 2, 10}, 2),
                 // -y face
                 mesh::quad({4, 12, 15, 7}, 3), mesh::quad({15, 14, 6, 7}, 4),
                 mesh::quad({13, 5, 6, 14}, 5)};
  int cid = 6;
  auto outline = {0, 8, 11, 10, 9, 1, 2, 3, 0};
  for (auto o = outline.begin(); o < outline.end() - 1; o++) {
    this->quads.push_back(
        mesh::quad({*o, *(o + 1), *(o + 1) + 4, *o + 4}, cid++));
  }
}