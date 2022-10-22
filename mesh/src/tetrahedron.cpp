#include "tetrahedron.h"

tetrahedron::tetrahedron() : mesh(4, 4) {
  this->verts = {{0, 0, 0}, {1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
  this->quads = {mesh::quad::from_triangle({1, 2, 3}, 0),
                 mesh::quad::from_triangle({0, 2, 1}, 1),
                 mesh::quad::from_triangle({0, 3, 2}, 2),
                 mesh::quad::from_triangle({1, 3, 0}, 3)};
}