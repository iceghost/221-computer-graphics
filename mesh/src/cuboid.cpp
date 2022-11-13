#include "mesh.hpp"

Cuboid::Cuboid(float dx, float dy, float dz)
    : dx(dx), dy(dy), dz(dz), Mesh(8, 6) {
  float hdx = dx / 2.0f, hdy = dy / 2.0f, hdz = dz / 2.0f;
  this->verts = {{-hdx, hdy, hdz},  {hdx, hdy, hdz},   {hdx, hdy, -hdz},
                 {-hdx, hdy, -hdz}, {-hdx, -hdy, hdz}, {hdx, -hdy, hdz},
                 {hdx, -hdy, -hdz}, {-hdx, -hdy, -hdz}};

  this->quads = {
      // front face
      Mesh::Quad({1, 5, 6, 2}, 0),
      // right face
      Mesh::Quad({0, 3, 7, 4}, 1),
      // top face
      Mesh::Quad({0, 1, 2, 3}, 2),
      // bottom face
      Mesh::Quad({7, 6, 5, 4}, 3),
      // near face
      Mesh::Quad({4, 5, 1, 0}, 4),
      // far face
      Mesh::Quad({3, 2, 6, 7}, 5),
  };
}

Cube::Cube(float size) : size(size), Mesh(Cuboid(size, size, size)) {}