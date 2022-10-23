#pragma once

#include "mesh.h"

class cuboid : public mesh {
  float dx, dy, dz;

public:
  cuboid(float dx, float dy, float dz);
};

class cube : public mesh {
  float size;

public:
  cube(float size);
};