#pragma once

#include "color3.hpp"
#include "point3.hpp"
#include <array>

class mesh {
protected:
  struct quad {
    std::array<int, 4> vertIds;
    std::array<int, 4> colorIds;
    quad(std::array<int, 4> vertIds, int colorId);
    static quad from_triangle(std::array<int, 3> vertIds, int colorId);
  };

protected:
  std::vector<point3> verts;
  std::vector<quad> quads;

public:
  static const Color3 COLORS[];

public:
  mesh(int nVerts, int nQuads);

  void draw_wireframe();
  void draw_color();

  static Color3 color(int i);
};