#pragma once

#include "event.hpp"
#include "mesh.hpp"
#include <memory>
#include <vector>

class Scene final : public Event::Handler {
  class Object;
  std::vector<std::unique_ptr<Object>> objs;
  int w, h;

public:
  Scene();
  void handleReshape(const ReshapeEvent &e) override;
  void addObj(Object &&o);
  void display();
};

class Scene::Object : Event::Handler {
public:
  void draw();
};