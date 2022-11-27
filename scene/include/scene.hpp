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
  Scene();
  void handle_reshape(const ReshapeEvent &e) override;
  void handle_mouse_button(const MouseButtonEvent &e) override;
  void handle_mouse_drag(const MouseDragEvent &e) override;
  void add_obj(ObjectPtr o);
  void display();
  void draw_axis();
};

class Scene::Object : public Event::Handler {
protected:
  Point3 pos;

public:
  Object();
  Object(Point3 pos);
  virtual ~Object() = default;
  // Draw itself in local coordinate system
  virtual void draw() = 0;
};

class SolidObject : public Scene::Object {
  Mesh m;

public:
  SolidObject(Mesh &&m);
  void draw() override;
};

class Camera : public Scene::Object {
  int prevX, prevY;
  int screenW, screenH;

public:
  Camera();
  void draw() override;
  void handle_reshape(const ReshapeEvent &e) override;
  void handle_mouse_button(const MouseButtonEvent &e) override;
  void handle_mouse_drag(const MouseDragEvent &e) override;
};