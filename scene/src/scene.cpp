#include "scene.hpp"
#include "mesh.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <iostream>
#include <memory>

Scene::Scene() {}

void Scene::add_obj(Scene::ObjectPtr o) { this->objs.push_back(std::move(o)); }

void Scene::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(0, 0, 0);

  this->draw_axis();

  for (auto &obj : this->objs) {
    obj->draw();
  }

  glFlush();
}

void Scene::handle_reshape(const ReshapeEvent &e) {
  for (auto &obj : this->objs) {
    obj->handle_reshape(e);
  }
}
void Scene::handle_mouse_button(const MouseButtonEvent &e) {
  for (auto &obj : this->objs) {
    obj->handle_mouse_button(e);
  }
}
void Scene::handle_mouse_drag(const MouseDragEvent &e) {
  for (auto &obj : this->objs) {
    obj->handle_mouse_drag(e);
  }
}

void Scene::draw_axis() {
  glColor3f(0, 0, 1);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(4, 0, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 4, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 4);
  glEnd();
}

Scene::Object::Object() : pos(0, 0, 0) {}
Scene::Object::Object(Point3 pos) : pos(pos) {}

SolidObject::SolidObject(Mesh &&m) : m(std::move(m)) {}
void SolidObject::draw() { m.draw(); }

const float RADIUS = 4.0;
const float HSIDE = RADIUS / std::sqrt(2);

Camera::Camera() : Object(Point3(HSIDE, HSIDE, HSIDE)) {}
void Camera::draw() {
  // the camera will revolve a sphere centered at world (0, 0, 0) with RADIUS.
  // its viewing volume is the cube inscribed in the sphere
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(this->pos.x, this->pos.y, this->pos.z, 0, 0, 0, 0, 1, 0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (this->screenW <= this->screenH)
    glOrtho(-HSIDE, HSIDE, -HSIDE * this->screenH / this->screenW,
            HSIDE * this->screenH / this->screenW, -10.0, 10.0);
  else
    glOrtho(-HSIDE * this->screenW / this->screenH,
            HSIDE * this->screenW / this->screenH, -HSIDE, HSIDE, -10.0, 10.0);
}
void Camera::handle_reshape(const ReshapeEvent &e) {
  this->screenW = e.w;
  this->screenH = e.h;
  glViewport(0, 0, e.w, e.h);
}
void Camera::handle_mouse_button(const MouseButtonEvent &e) {
  if (e.down) {
    std::cout << "down" << std::endl;
    this->prevX = e.x;
    this->prevY = e.y;
  }
}
void Camera::handle_mouse_drag(const MouseDragEvent &e) {
  const auto size = std::min(this->screenW, this->screenH);
  auto dx = (e.x - this->prevX) * 2 * HSIDE / size / RADIUS;
  auto dy = (e.y - this->prevY) * 2 * HSIDE / size / RADIUS;

  // polar
  auto r = std::sqrt(this->pos.x * this->pos.x + this->pos.y * this->pos.y +
                     this->pos.z * this->pos.z);
  auto theta = std::acos(this->pos.y / r);
  auto phi = std::atan(this->pos.z / this->pos.x);
  theta += dy;
  phi += dx;
  this->pos.x = r * std::sin(theta) * std::cos(phi);
  this->pos.z = r * std::sin(theta) * std::sin(phi);
  this->pos.y = r * std::cos(theta);
  // std::cout << this->pos.x << " " << this->pos.y << " " << this->pos.z
  //           << std::endl;
  this->prevX = e.x;
  this->prevY = e.y;
}