#pragma once
#include "mesh.h"

class cylinder : public mesh {
  int nSegments;
  float height, radius;

public:
  cylinder(int nSegments, float height, float radius);
};