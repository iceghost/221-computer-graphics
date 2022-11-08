#include "scene.hpp"
#include "cuboid.hpp"
#include <GL/glu.h>
#include <memory>

Scene::Scene() {}

void Scene::addObj(Scene::ObjectPtr o) { this->objs.push_back(std::move(o)); }

void Scene::display() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(0, 0, 0);

  for (auto &obj : this->objs) {
    obj->draw();
  }

  glFlush();
}

void Scene::handleReshape(const ReshapeEvent &e) {
  this->w = e.w;
  this->h = e.h;
  glViewport(0, 0, this->w, this->h);
}

SolidObject::SolidObject(mesh &&m) : m(std::move(m)) {}

void SolidObject::draw() { m.draw_wireframe(); }