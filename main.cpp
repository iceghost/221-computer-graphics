#ifdef _WIN32
#include <windows.h>
#endif
#include "event.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <memory>

struct choice {
  enum value {
    TETRAHEDRON = 1,
    CUBE = 2,
    CUBOID = 3,
    CYLINDER = 4,
    HOLLOW_CYLINDER = 5,
    UBOX = 6,
    TBOX = 7,
    POINTED_CYLINDER = 8,
    HOLLOW_BOX = 9,
  };
  value v;
  choice() : v(value::HOLLOW_BOX) {}
  choice(int ivalue) : v(value(ivalue)) {}
  std::unique_ptr<Mesh> getMesh() {
    Mesh *ptr;
    switch (this->v) {
    case TETRAHEDRON:
      ptr = new Tetrahedron();
      break;
    case CUBE:
      ptr = new Cube(1);
      break;
    case CUBOID:
      ptr = new Cuboid(1, 2, 3);
      break;
    case CYLINDER:
      ptr = new Cylinder(3, 2, 1);
      break;
    case HOLLOW_CYLINDER:
      ptr = new HollowCylinder(100, 5, 2, 1);
      break;
    case UBOX:
      ptr = new UBox(2, 1, 5, 1, 0.5);
      break;
    case TBOX:
      ptr = new TBox(2, 1, 5, 1, 0.5);
      break;
    case POINTED_CYLINDER:
      ptr = new PointedCylinder(10, 2, 1, 1);
      break;
    case HOLLOW_BOX:
      ptr = new HollowBox(20, 2, 1, 5, 1, 4);
      break;
    }
    return std::unique_ptr<Mesh>(ptr);
  }
};

Scene scene;

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 300);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Lab 2");

  float fHalfSize = 4;

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glFrontFace(GL_CCW);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);

  glutReshapeFunc([](int w, int h) {
    std::cout << "Resize " << w << " " << h << std::endl;
    // handle window resize
    scene.handle_reshape(ReshapeEvent(w, h));
  });
  glutKeyboardFunc([](unsigned char key, int x, int y) {
    //
    scene.handle_keyboard(KeyboardEvent(key, x, y));
  });
  glutDisplayFunc([]() {
    std::cout << "Display" << std::endl;
    // handle draw callback
    scene.display();
    // information about double buffer is in the function so we swap buffer
    // here. no need to import glut inside the lib, too
    glutSwapBuffers();
  });
  scene.add_obj(std::make_unique<Camera>());
  scene.add_obj(std::make_unique<SolidObject>(Cube(1)));
  glutMainLoop();
  return 0;
}
