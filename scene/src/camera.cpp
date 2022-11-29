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
  if (this->dimension == Scene::Camera::Dimension::THREE &&
      this->distance != 0) {
    auto eyeX = this->distance * std::sin(angle * DEG_TO_RAD);
    auto eyeY = this->height;
    auto eyeZ = this->distance * std::cos(angle * DEG_TO_RAD);
    gluLookAt(eyeX, eyeY, eyeZ, look_at.x, look_at.y, look_at.z, 0, 1, 0);
  } else {
    gluLookAt(0, look_at.y + 1, 0, look_at.x, look_at.y, look_at.z,
              -std::sin(angle * DEG_TO_RAD), 0, -std::cos(angle * DEG_TO_RAD));
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  auto factor = max(this->distance, 1);

  if (this->aspect_ratio <= 1.0)
    glOrtho(-factor, factor, -factor / this->aspect_ratio,
            factor / this->aspect_ratio, -1000.0, 1000.0);
  else
    glOrtho(-factor * this->aspect_ratio, factor * this->aspect_ratio, -factor,
            factor, -1000.0, 1000.0);
}