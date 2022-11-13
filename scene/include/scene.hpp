#pragma once

#include "event.hpp"
#include "mesh.hpp"
#include "vector3.hpp"
#include <memory>
#include <vector>

class Scene final : public Event::Handler {
public:
  class Object;

private:
  using ObjectPtr = std::unique_ptr<Object>;
  std::vector<ObjectPtr> objs;

public:
  int w, h;
  Scene();
  void handle_reshape(const ReshapeEvent &e) override;
  void add_obj(ObjectPtr o);
  void display();
  void draw_axis();
};

class Scene::Object : public Event::Handler {
protected:
  Vector3 pos;

public:
  Object();
  Object(Vector3 pos);
  virtual ~Object() = default;
  // Draw itself in local coordinate system
  virtual void draw(const Scene &) = 0;
};

class SolidObject : public Scene::Object {
  Mesh m;

public:
  SolidObject(Mesh &&m);
  void draw(const Scene &) override;
};

class Camera : public Scene::Object {
public:
  Camera();
  void draw(const Scene &) override;
};