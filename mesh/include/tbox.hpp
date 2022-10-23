#pragma once
#include "mesh.hpp"

class tbox : public mesh {
public:
  tbox(float dx, float dy, float dz, float width, float depth);
};