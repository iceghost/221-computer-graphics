#include "scene.hpp"
#include "mesh.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <memory>

Scene::Scene() {}

void Scene::add_obj(Scene::ObjectPtr o) { this->objs.push_back(std::move(o)); }

void Scene::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(0, 0, 0);

  this->draw_axis();

  for (auto &obj : this->objs) {
    obj->draw(*this);
  }

  glFlush();
}

void Scene::handle_reshape(const ReshapeEvent &e) {
  this->w = e.w;
  this->h = e.h;
  glViewport(0, 0, this->w, this->h);
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
Scene::Object::Object(Vector3 pos) : pos(pos) {}

SolidObject::SolidObject(Mesh &&m) : m(std::move(m)) {}
void SolidObject::draw(const Scene &) { m.draw(); }

Camera::Camera() {}
void Camera::draw(const Scene &scene) {
  // the camera will revolve a sphere centered at world (0, 0, 0) with RADIUS.
  // its viewing volume is the cube inscribed in the sphere
  const float RADIUS = 4.0;
  const float HSIDE = RADIUS / std::sqrt(2);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(HSIDE, HSIDE, HSIDE, 0, 0, 0, 0, 1, 0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (scene.w <= scene.h)
    glOrtho(-HSIDE, HSIDE, -HSIDE * scene.h / scene.w,
            HSIDE * scene.h / scene.w, -10.0, 10.0);
  else
    glOrtho(-HSIDE * scene.w / scene.h, HSIDE * scene.w / scene.h, -HSIDE,
            HSIDE, -10.0, 10.0);
}