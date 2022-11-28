#include "mesh.hpp"
#include "color3.hpp"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <cmath>

const Color3 Mesh::COLORS[] = {
    {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f},
    {0.3f, 0.3f, 0.3f}, {0.5f, 0.5f, 0.5f}, {0.9f, 0.9f, 0.9f},
    {1.0f, 0.5f, 0.5f}, {0.5f, 1.0f, 0.5f}, {0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};

Mesh::Quad::Quad(std::array<int, 4> vertIds, int colorId)
    : vertIds(vertIds), colorIds({colorId, colorId, colorId, colorId}) {}

Mesh::Quad Mesh::Quad::from_triangle(std::array<int, 3> vids, int colorId) {
  return Quad({vids[0], vids[0], vids[1], vids[2]}, colorId);
}

Mesh::Mesh(int nVerts, int nFaces) {
  this->verts.reserve(nVerts);
  this->quads.reserve(nFaces);
}

Mesh::Mesh(Mesh &&m) : verts(std::move(m.verts)), quads(std::move(m.quads)) {}

// void Mesh::draw() {
//   for (auto &face : this->quads) {
//     glBegin(GL_POLYGON);
//     for (auto vertId : face.vertIds) {
//       auto &vert = verts[vertId];
//       glVertex3f(vert.x, vert.y, vert.z);
//     }
//     glEnd();
//   }
// }

void Mesh::draw_wireframe() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  this->draw();
}

void Mesh::draw_solid() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  this->draw();
}

void Mesh::draw() {
  // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  for (auto &face : quads) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < face.vertIds.size(); i++) {
      auto &vert = verts[face.vertIds[i]];
      auto &color = Mesh::COLORS[face.colorIds[i] %
                                 (sizeof(Mesh::COLORS) / sizeof(Color3))];
      glColor3f(color.r, color.g, color.b);
      glVertex3f(vert.x, vert.y, vert.z);
    }
    glEnd();
  }
}