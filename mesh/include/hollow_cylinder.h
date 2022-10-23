#pragma once
#include "mesh.h"

class hollow_cylinder : public mesh {
public:
  hollow_cylinder(int nSegment, float height, float outradius, float inradius);
};