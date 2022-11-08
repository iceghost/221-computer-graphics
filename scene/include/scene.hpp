#pragma once

#include "event.hpp"
#include "mesh.hpp"
#include "vector3.hpp"
#include <memory>
#include <vector>

class scene final : public event::handler {
public:
  class object;

private:
  using object_ptr = std::unique_ptr<object>;
  std::vector<object_ptr> objs;

public:
  int w, h;
  scene();
  void handle_reshape(const reshape_event &e) override;
  void add_obj(object_ptr o);
  void display();
  void draw_axis();
};

class scene::object : public event::handler {
protected:
  Vector3 pos;

public:
  object();
  object(Vector3 pos);
  virtual ~object() = default;
  // Draw itself in local coordinate system
  virtual void draw(const scene &) = 0;
};

class solid_object : public scene::object {
  mesh m;

public:
  solid_object(mesh &&m);
  void draw(const scene &) override;
};

class camera : public scene::object {
public:
  camera();
  void draw(const scene &) override;
};