#include "mesh.hpp"

UBox::UBox(float dx, float dy, float dz, float width, float depth)
    : Mesh(16, 14) {
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

  this->norms.push_back({0, 0, 1});
  this->norms.push_back({0, 0, 1});
  this->norms.push_back({0, 0, 1});
  this->norms.push_back({0, 0, -1});
  this->norms.push_back({0, 0, -1});
  this->norms.push_back({0, 0, -1});
  this->norms.push_back({0, 1, 0});
  this->norms.push_back({1, 0, 0});
  this->norms.push_back({0, 1, 0});
  this->norms.push_back({-1, 0, 0});
  this->norms.push_back({0, 1, 0});
  this->norms.push_back({1, 0, 0});
  this->norms.push_back({0, -1, 0});
  this->norms.push_back({-1, 0, 0});

  this->quads = {// +z face
                 Mesh::Quad({0, 8, 11, 3}, 0), Mesh::Quad({11, 10, 2, 3}, 1),
                 Mesh::Quad({9, 1, 2, 10}, 2),
                 // -z face
                 Mesh::Quad({4, 12, 15, 7}, 3), Mesh::Quad({15, 14, 6, 7}, 4),
                 Mesh::Quad({13, 5, 6, 14}, 5)};
  int cid = 6;
  auto outline = {0, 8, 11, 10, 9, 1, 2, 3, 0};
  for (auto o = outline.begin(); o < outline.end() - 1; o++) {
    this->quads.push_back(
        Mesh::Quad({*o, *(o + 1), *(o + 1) + 4, *o + 4}, cid++));
  }
}