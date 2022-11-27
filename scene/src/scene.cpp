#include "scene.hpp"
#include "GL/glut.h"
#include <cmath>

void Scene::Object::translate(Vector3 vec) {
  this->t = vec;
}

void Scene::Object::rotateX(double angle) {
  this->rX = angle;
  this->pushOrder(0);
}

void Scene::Object::rotateY(double angle) {
  this->rY = angle;
  this->pushOrder(1);
}

void Scene::Object::rotateZ(double angle) {
  this->rZ = angle;
  this->pushOrder(2);
}

void Scene::Object::pushOrder(int order) {
  auto pos = std::find(this->rOrds.begin(), this->rOrds.end(), order);
  if (pos != this->rOrds.end()) {
    this->rOrds.erase(pos);
  }
  this->rOrds.push_back(order);
}

void Scene::Object::draw_wireframe() {
  glPushMatrix();
  glTranslatef(this->t.dx, this->t.dy, this->t.dz);
  for (auto ord : this->rOrds) {
    switch (ord) {
    case 0:
      glRotated(this->rX, 1, 0, 0);
      break;
    case 1:
      glRotated(this->rY, 0, 1, 0);
      break;
    case 2:
      glRotated(this->rZ, 0, 0, 1);
      break;
    }
  }
  this->m.draw_wireframe();
  glPopMatrix();
}