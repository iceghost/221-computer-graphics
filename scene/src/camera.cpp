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
  if (this->dimension == Scene::Camera::Dimension::THREE) {
    auto eye = Point3(float(this->distance * std::sin(angle * DEG_TO_RAD)),
                      float(this->height),
                      float(this->distance * std::cos(angle * DEG_TO_RAD)));
    auto up = this->distance != 0
                  ? Vector3(0, 1, 0)
                  : Vector3(float(-std::sin(angle * DEG_TO_RAD)), 0,
                            float(-std::cos(angle * DEG_TO_RAD)));
    gluLookAt(eye.x, eye.y, eye.z, look_at.x, look_at.y, look_at.z, up.dx,
              up.dy, up.dz);
  } else {
    gluLookAt(0, 1000, 0, 0, 0, 0, 0, 0, 1);
  }
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (this->dimension == Scene::Camera::Dimension::THREE) {
    gluPerspective(60.0, this->aspect_ratio, 1.0, 1000.0);
  } else {
    auto factor = 1.0f;
    if (this->aspect_ratio <= 1.0)
      glOrtho(-factor, factor, -factor / this->aspect_ratio,
              factor / this->aspect_ratio, -1000, 1000);
    else
      glOrtho(-factor * this->aspect_ratio, factor * this->aspect_ratio,
              -factor, factor, -1000, 1000);
  }
}