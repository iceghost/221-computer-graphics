#pragma once
#include "mesh.h"

class tbox : public mesh {
public:
  tbox(float dx, float dy, float dz, float width, float depth);
};