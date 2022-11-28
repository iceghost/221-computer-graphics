#pragma once

#include "mesh.hpp"
#include "point3.hpp"
#include "vector3.hpp"
#include <vector>

struct Scene {
  struct Object {
    Vector3 t;
    double r_x;
    double r_y;
    double r_z;
    std::vector<int> r_ords; // 0 for x, 1 for y, 2 for z
    std::vector<Object> children;

    Object(Mesh &&m);

    Mesh m;

    void translate(Vector3 vec);
    void rotate_x(double angle);
    void rotate_y(double angle);
    void rotate_z(double angle);

    void push_order(int order);
    void add_child(Object &&child);

    void draw();
  };

  struct Camera {
    // angle around Oy
    double angle;
    // height from Oxz
    double height;
    // distance from Oy
    double distance;
    Point3 look_at;

    float aspect_ratio;
    int screen_width;

    void view();
    void on_key(int key);
  } camera;

  enum class MoveState {
    IDLE,
    UP,
    DOWN,
  } move_state;

  enum class AnimateState {
    OFF,
    ON,
  } animate_state;

  std::vector<Object> objs;

  Scene();
  void display();
};
