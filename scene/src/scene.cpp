#ifdef _WIN32
#include <windows.h>
#endif
#include "scene.hpp"
#include <GL/GL.h>
#include <GL/GLU.h>

Scene::Scene() : camera({45, 3, 5}) {}

void Scene::display() {
  this->camera.view();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(0, 0, 1);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(4, 0, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 4, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 4);
  glEnd();

  glColor3f(0, 0, 0);

  for (auto &obj : this->objs) {
    obj.draw();
  }

  glFlush();
}