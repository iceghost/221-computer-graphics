#pragma once
#include "mesh.hpp"

class hollow_box : public mesh {
public:
  hollow_box(int n_segments, float dx, float dy, float dz, float hole_dx,
             float hole_dz);
};