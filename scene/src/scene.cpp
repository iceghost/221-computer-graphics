#include "scene.hpp"
#include "cuboid.hpp"
#include <GL/glu.h>
#include <memory>

Scene::Scene() {
  float fHalfSize = 4;

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glFrontFace(GL_CCW);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

void Scene::addObj(Object &&o) {
  this->objs.push_back(std::make_unique<Object>(o));
}

void Scene::display() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, this->w / 2, this->h);

  glColor3f(0, 0, 0);
  auto m = cube(1);
  m.draw_wireframe();
  glViewport(this->w / 2, 0, this->w / 2, this->h);
  m.draw_color();

  glFlush();
}

void Scene::handleReshape(const ReshapeEvent &e) {
  this->w = e.w;
  this->h = e.h;
}