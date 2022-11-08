#pragma once

#include "event.hpp"
#include "mesh.hpp"
#include <memory>
#include <vector>

class scene final : public event::handler {
public:
  class object;

private:
  using object_ptr = std::unique_ptr<object>;
  std::vector<object_ptr> objs;
  int w, h;

public:
  scene();
  void handle_reshape(const reshape_event &e) override;
  void add_obj(object_ptr o);
  void display();
};

class scene::object : public event::handler {
public:
  virtual ~object() = default;
  virtual void draw() = 0;
};

class solid_object : public scene::object {
  mesh m;

public:
  solid_object(mesh &&m);
  void draw() override;
};