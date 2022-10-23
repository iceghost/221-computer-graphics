#pragma once
#include "mesh.hpp"

class pointed_cylinder : public mesh {
public:
  pointed_cylinder(int n_segments, float height, float radius,
                   float tip_height);
};