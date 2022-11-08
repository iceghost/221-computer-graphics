#include "scene.hpp"
#include "cuboid.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <memory>

scene::scene() {}

void scene::add_obj(scene::object_ptr o) { this->objs.push_back(std::move(o)); }

void scene::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(0, 0, 0);

  this->draw_axis();

  for (auto &obj : this->objs) {
    obj->draw(*this);
  }

  glFlush();
}

void scene::handle_reshape(const reshape_event &e) {
  this->w = e.w;
  this->h = e.h;
  glViewport(0, 0, this->w, this->h);
}

void scene::draw_axis() {
  glColor3f(0, 0, 1);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(4, 0, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 4, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 4);
  glEnd();
}

scene::object::object() : pos(0, 0, 0) {}
scene::object::object(Vector3 pos) : pos(pos) {}

solid_object::solid_object(mesh &&m) : m(std::move(m)) {}
void solid_object::draw(const scene &) {
  m.draw();
}

camera::camera() {}
void camera::draw(const scene &scene) {
  // the camera will revolve a sphere centered at world (0, 0, 0) with RADIUS.
  // its viewing volume is the cube inscribed in the sphere
  const float RADIUS = 4.0;
  const float HSIDE = RADIUS / std::sqrt(2);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(HSIDE, HSIDE, HSIDE, 0, 0, 0, 0, 1, 0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (scene.w <= scene.h)
    glOrtho(-HSIDE, HSIDE, -HSIDE * scene.h / scene.w,
            HSIDE * scene.h / scene.w, -10.0, 10.0);
  else
    glOrtho(-HSIDE * scene.w / scene.h, HSIDE * scene.w / scene.h, -HSIDE,
            HSIDE, -10.0, 10.0);
}