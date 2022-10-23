#include "rect.h"
#include <cmath>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

template <typename T>
Rect<T>::Rect(T left, T right, T bottom, T top)
    : l(left), r(right), b(bottom), t(top) {}

template <typename T> T Rect<T>::getWidth() {
  return std::abs(this->r - this->l);
}

template <typename T> T Rect<T>::getHeight() {
  return std::abs(this->t - this->b);
}

template <> void IntRect::draw() {
  glRecti(this->l, this->b, this->r, this->t);
  glFlush();
}

template <> void FloatRect::draw() {
  glRectf(this->l, this->b, this->r, this->t);
  glFlush();
}