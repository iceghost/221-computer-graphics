#include "mesh.hpp"

cuboid::cuboid(float dx, float dy, float dz)
    : dx(dx), dy(dy), dz(dz), mesh(8, 6) {
  float hdx = dx / 2.0f, hdy = dy / 2.0f, hdz = dz / 2.0f;
  this->verts = {{-hdx, hdy, hdz},  {hdx, hdy, hdz},   {hdx, hdy, -hdz},
                 {-hdx, hdy, -hdz}, {-hdx, -hdy, hdz}, {hdx, -hdy, hdz},
                 {hdx, -hdy, -hdz}, {-hdx, -hdy, -hdz}};

  this->quads = {
      // front face
      mesh::quad({1, 5, 6, 2}, 0),
      // right face
      mesh::quad({0, 3, 7, 4}, 1),
      // top face
      mesh::quad({0, 1, 2, 3}, 2),
      // bottom face
      mesh::quad({7, 6, 5, 4}, 3),
      // near face
      mesh::quad({4, 5, 1, 0}, 4),
      // far face
      mesh::quad({3, 2, 6, 7}, 5),
  };
}

cube::cube(float size) : size(size), mesh(cuboid(size, size, size)) {}