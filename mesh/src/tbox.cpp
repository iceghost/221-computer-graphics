#include "tbox.hpp"

tbox::tbox(float dx, float dy, float dz, float w, float depth) : mesh(16, 12) {
  float hdx = dx / 2, hdy = dy / 2, hdz = dz / 2, hw = w / 2;
  this->verts = {// big box
                 {-hdx, hdy - depth, hdz},
                 {hdx, hdy - depth, hdz},
                 {hdx, -hdy, hdz},
                 {-hdx, -hdy, hdz},
                 {-hdx, hdy - depth, -hdz},
                 {hdx, hdy - depth, -hdz},
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
                 mesh::quad({0, 1, 2, 3}, 0), mesh::quad({8, 9, 10, 11}, 1),
                 // -y face
                 mesh::quad({4, 5, 6, 7}, 2), mesh::quad({12, 13, 14, 15}, 3)};
  int cid = 4;
  auto outline = {0, 11, 8, 9, 10, 1, 2, 3, 0};
  for (auto o = outline.begin(); o < outline.end() - 1; o++) {
    this->quads.push_back(
        mesh::quad({*o, *(o + 1), *(o + 1) + 4, *o + 4}, cid++));
  }
}