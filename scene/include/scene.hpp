#pragma once

#include "event.hpp"
#include "mesh.hpp"
#include <memory>
#include <vector>

class Scene final : public Event::Handler {
public:
  class Object;

private:
  using ObjectPtr = std::unique_ptr<Object>;
  std::vector<ObjectPtr> objs;
  int w, h;

public:
  Scene();
  void handleReshape(const ReshapeEvent &e) override;
  void addObj(ObjectPtr o);
  void display();
};

class Scene::Object : public Event::Handler {
public:
  virtual void draw() = 0;
};

class SolidObject : public Scene::Object {
  mesh m;

public:
  SolidObject(mesh &&m);
  void draw() override;
};