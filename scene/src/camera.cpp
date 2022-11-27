#include "GL/glut.h"
#include "scene.hpp"
#include <cmath>

void Scene::Camera::view() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  auto eyeX = distance * std::sin(angle);
  auto eyeY = height;
  auto eyeZ = distance * std::cos(angle);
  gluLookAt(eyeX, eyeY, eyeZ, lookAt.x, lookAt.y, lookAt.z, 0, 1, 0);
}