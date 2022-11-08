#include "scene.hpp"
#include "cuboid.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <memory>

scene::scene() {}

void scene::add_obj(scene::object_ptr o) { this->objs.push_back(std::move(o)); }

void scene::display() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(0, 0, 0);

  glViewport(0, 0, this->w, this->h);

  for (auto &obj : this->objs) {
    obj->draw();
  }

  glFlush();
}

void scene::handle_reshape(const reshape_event &e) {
  this->w = e.w;
  this->h = e.h;
  glViewport(0, 0, this->w, this->h);
}

solid_object::solid_object(mesh &&m) : m(std::move(m)) {}

void solid_object::draw() { m.draw_wireframe(); }