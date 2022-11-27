#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>

#include <cmath>
#include <iostream>
#include <memory>

#include "mesh.hpp"
#include "scene.hpp"

int screenWidth = 600;
int screenHeight = 300;

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
    default:
      throw "unreachable";
    }
    return std::unique_ptr<Mesh>(ptr);
  }
};

void drawAxis() {
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

void myDisplay() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, screenWidth / 2, screenHeight);

  drawAxis();

  glColor3f(0, 0, 0);
  auto m = choice(choice::value::CYLINDER).getMesh();
  m->draw_wireframe();
  glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);
  drawAxis();
  m->draw_color();

  glFlush();
  glutSwapBuffers();
}

void myInit() {
  float fHalfSize = 4;

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glFrontFace(GL_CCW);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int main(int argc, const char **argv) {
  //	cout << "1. Tetrahedron" << endl;
  //	cout << "2. Cube" << endl;
  //	cout << "Input the choice: " << endl;
  //	cin  >> nChoice;

  glutInit(&argc, (char **)argv); // initialize the tool kit
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
                      GLUT_DEPTH);               // set the display mode
  glutInitWindowSize(screenWidth, screenHeight); // set window size
  glutInitWindowPosition(100, 100); // set window position on screen
  glutCreateWindow("Nguyen Duy Khang - 2011364");        // open the screen window

  myInit();
  glutDisplayFunc(myDisplay);
  glutKeyboardFunc([](unsigned char key, int, int) {
    std::cout << "Got key: " << key << std::endl;
    if (key == GLUT_KEY_F4) {
      exit(0);
    }
  });
  glutMainLoop();
  return 0;
}
