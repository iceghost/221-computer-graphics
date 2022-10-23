#include "point2.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

Point2::Point2(float x, float y) : x(x), y(y) {}

void Point2::draw() {
  glBegin(GL_POINTS);
  glVertex2f(this->x, this->y);
  glEnd();
}