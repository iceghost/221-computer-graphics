#pragma once

struct Vector3 {
  float dx, dy, dz;
  Vector3(float dx, float dy, float dz);
  Vector3();
  Vector3 flip();
  Vector3 normalize();
  Vector3 cross(const Vector3 &b);
  float dot(const Vector3 &b);
};