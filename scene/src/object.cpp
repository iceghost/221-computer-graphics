#ifdef _WIN32
#include <windows.h>
#endif
#include "scene.hpp"
#include <GL/gl.h>
#include <cmath>

Scene::Object::Object(Mesh &&m) : m(std::move(m)) {}

void Scene::Object::translate(Vector3 vec) { this->t = vec; }

void Scene::Object::rotate_x(double angle) {
  this->r_x = angle;
  this->push_order(0);
}

void Scene::Object::rotate_y(double angle) {
  this->r_y = angle;
  this->push_order(1);
}

void Scene::Object::rotate_z(double angle) {
  this->r_z = angle;
  this->push_order(2);
}

void Scene::Object::push_order(int order) {
  auto pos = std::find(this->r_ords.begin(), this->r_ords.end(), order);
  if (pos != this->r_ords.end()) {
    this->r_ords.erase(pos);
  }
  this->r_ords.push_back(order);
}

void Scene::Object::draw() {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(this->t.dx, this->t.dy, this->t.dz);
  for (auto ord : this->r_ords) {
    switch (ord) {
    case 0:
      glRotated(this->r_x, 1, 0, 0);
      continue;
    case 1:
      glRotated(this->r_y, 0, 1, 0);
      continue;
    case 2:
      glRotated(this->r_z, 0, 0, 1);
      continue;
    default:
      throw "unreachable";
    }
  }
  this->m.draw_solid();
  for (auto &child : this->children) {
    child.draw();
  }
  glPopMatrix();
}