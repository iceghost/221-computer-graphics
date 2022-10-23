#include <GL/glut.h>

#include <cmath>
#include <iostream>
#include <memory>

#include "cuboid.h"
#include "cylinder.h"
#include "hollow_cylinder.h"
#include "slid.h"
#include "tetrahedron.h"

int screenWidth = 600;
int screenHeight = 300;

int nChoice = 6;

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
  mesh *ptr;
  if (nChoice == 1)
    ptr = new tetrahedron();
  else if (nChoice == 2)
    ptr = new cube(1);
  else if (nChoice == 3)
    ptr = new cuboid(1, 2, 3);
  else if (nChoice == 4)
    ptr = new cylinder(10, 2, 1);
  else if (nChoice == 5)
    ptr = new slid(2, 1, 5, 1, 0.5);
  else if (nChoice == 6)
    ptr = new hollow_cylinder(100, 5, 2, 1);
  else
    throw "unrecognized choice";

  std::unique_ptr<mesh> m(ptr);
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
  glutCreateWindow("Lab 2");        // open the screen window

  myInit();
  glutDisplayFunc(myDisplay);
  glutKeyboardFunc([](unsigned char key, int x, int y) {
    std::cout << "Got key: " << key << std::endl;
    if (key == GLUT_KEY_F4) {
      exit(0);
    }
  });
  glutMainLoop();
  return 0;
}
