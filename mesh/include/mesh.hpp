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

class tetrahedron : public mesh {
public:
  tetrahedron();
};

class cuboid : public mesh {
  float dx, dy, dz;

public:
  cuboid(float dx, float dy, float dz);
};

class cube : public mesh {
  float size;

public:
  cube(float size);
};

class cylinder : public mesh {
  int nSegments;
  float height, radius;

public:
  cylinder(int nSegments, float height, float radius);
};

class hollow_cylinder : public mesh {
public:
  hollow_cylinder(int nSegment, float height, float outradius, float inradius);
};

class pointed_cylinder : public mesh {
public:
  pointed_cylinder(int n_segments, float height, float radius,
                   float tip_height);
};

class tbox : public mesh {
public:
  tbox(float dx, float dy, float dz, float width, float depth);
};

class ubox : public mesh {
public:
  ubox(float dx, float dy, float dz, float width, float depth);
};

class hollow_box : public mesh {
public:
  hollow_box(int n_segments, float dx, float dy, float dz, float hole_dx,
             float hole_dz);
};