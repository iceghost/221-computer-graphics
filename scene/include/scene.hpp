#pragma once

#include "mesh.hpp"
#include "point3.hpp"
#include "vector3.hpp"
#include <algorithm>
#include <vector>

struct Scene {
  struct Object {
    Vector3 t;
    double rX;
    double rY;
    double rZ;
    std::vector<int> rOrds; // 0 for x, 1 for y, 2 for z
    std::vector<Object> children;

    Mesh m;

    void translate(Vector3 vec);
    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);

    void pushOrder(int order);

    void draw_wireframe();
  };

  struct Camera {
    // angle around Oy
    double angle;
    // height from Oxz
    double height;
    // distance from Oy
    double distance;

    Point3 lookAt;

    void view();

    void onKey(int key);
  };
};

enum class Key {
  UP,
  DOWN,
  ANIMATE_ON,
  ANIMATE_OFF,
  WIREFRAME_ON,
  WIREFRAME_OFF,
  TWO_DIMENSION,
  THREE_DIMENSION,
  CLOSER,
  FARTHER,
  LOWER,
  HIGHER,
  ROTATE_LEFT,
  ROTATE_RIGHT,
};