#ifdef _WIN32
#include <windows.h>
#endif
#include "scene.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

const double RADIUS = 4.0;
const double HSIDE = RADIUS / std::sqrt(2);
const double DEG_TO_RAD = M_PI / 180;

void Scene::Camera::view() {
  glViewport(0, 0, this->screen_width,
             int(this->screen_width / this->aspect_ratio));
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  auto eyeX = distance * std::sin(angle * DEG_TO_RAD);
  auto eyeY = height;
  auto eyeZ = distance * std::cos(angle * DEG_TO_RAD);
  gluLookAt(eyeX, eyeY, eyeZ, look_at.x, look_at.y, look_at.z, 0, 1, 0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (this->aspect_ratio <= 1.0)
    glOrtho(-HSIDE, HSIDE, -HSIDE / this->aspect_ratio,
            HSIDE / this->aspect_ratio, -50.0, 50.0);
  else
    glOrtho(-HSIDE * this->aspect_ratio, HSIDE * this->aspect_ratio, -HSIDE,
            HSIDE, -50.0, 50.0);
}