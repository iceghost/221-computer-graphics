#include "mesh.hpp"

TBox::TBox(float dx, float dy, float dz, float w, float depth) : Mesh(16, 12) {
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

  this->norms.push_back({0, 0, 1});
  this->norms.push_back({0, 0, 1});
  this->norms.push_back({0, 0, -1});
  this->norms.push_back({0, 0, -1});
  this->norms.push_back({0, 1, 0});
  this->norms.push_back({-1, 0, 0});
  this->norms.push_back({0, 1, 0});
  this->norms.push_back({1, 0, 0});
  this->norms.push_back({0, 1, 0});
  this->norms.push_back({1, 0, 0});
  this->norms.push_back({0, -1, 0});
  this->norms.push_back({-1, 0, 0});

  this->quads = {// +z face
                 Mesh::Quad({0, 1, 2, 3}, 0), Mesh::Quad({8, 9, 10, 11}, 1),
                 // -z face
                 Mesh::Quad({4, 5, 6, 7}, 2), Mesh::Quad({12, 13, 14, 15}, 3)};
  int nid = 4;
  auto outline = {0, 11, 8, 9, 10, 1, 2, 3, 0};
  for (auto o = outline.begin(); o < outline.end() - 1; o++) {
    this->quads.push_back(
        Mesh::Quad({*o, *(o + 1), *(o + 1) + 4, *o + 4}, nid++));
  }
}