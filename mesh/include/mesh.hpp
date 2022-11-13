#pragma once

#include "color3.hpp"
#include "point3.hpp"
#include <array>

class Mesh {
protected:
  struct Quad {
    std::array<int, 4> vertIds;
    std::array<int, 4> colorIds;
    Quad(std::array<int, 4> vertIds, int colorId);
    static Quad from_triangle(std::array<int, 3> vertIds, int colorId);
  };

protected:
  std::vector<Point3> verts;
  std::vector<Quad> quads;

public:
  static const Color3 COLORS[];

public:
  Mesh(int nVerts, int nQuads);
  Mesh(Mesh &&);

  void draw_wireframe();
  void draw_color();
  void draw();

  static Color3 color(int i);
};

class Tetrahedron : public Mesh {
public:
  Tetrahedron();
};

class Cuboid : public Mesh {
  float dx, dy, dz;

public:
  Cuboid(float dx, float dy, float dz);
};

class Cube : public Mesh {
  float size;

public:
  Cube(float size);
};

class Cylinder : public Mesh {
  int nSegments;
  float height, radius;

public:
  Cylinder(int nSegments, float height, float radius);
};

class HollowCylinder : public Mesh {
public:
  HollowCylinder(int nSegment, float height, float outradius, float inradius);
};

class PointedCylinder : public Mesh {
public:
  PointedCylinder(int n_segments, float height, float radius, float tip_height);
};

class TBox : public Mesh {
public:
  TBox(float dx, float dy, float dz, float width, float depth);
};

class UBox : public Mesh {
public:
  UBox(float dx, float dy, float dz, float width, float depth);
};

class HollowBox : public Mesh {
public:
  HollowBox(int n_segments, float dx, float dy, float dz, float hole_dx,
            float hole_dz);
};