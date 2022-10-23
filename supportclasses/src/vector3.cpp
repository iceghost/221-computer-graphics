#include "vector3.hpp"
#include <cmath>

Vector3::Vector3(float dx, float dy, float dz) : dx(dx), dy(dy), dz(dz) {}

Vector3 Vector3::flip() { return Vector3(-dx, -dy, -dz); }

Vector3 Vector3::normalize() {
  float len = std::sqrt(dx * dx + dy * dy + dz * dz);
  return Vector3(dx / len, dy / len, dz / len);
};

Vector3 Vector3::cross(const Vector3 &b) {
  Vector3 c(dy * b.dz - dz * b.dy, dz * b.dx - dx * b.dz,
            dx * b.dy - dy * b.dx);
  return c;
};

float Vector3::dot(const Vector3 &b) {
  return dx * b.dx + dy * b.dy + dz * b.dz;
};