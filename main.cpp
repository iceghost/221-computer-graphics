#include <GL/freeglut_std.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "event.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include <GL/glut.h>
#include <iostream>
#include <memory>

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
    // handle window resize
    scene.handle_reshape(ReshapeEvent(w, h));
  });
  glutKeyboardFunc([](unsigned char key, int x, int y) {
    //
    scene.handle_keyboard(KeyboardEvent(key, x, y));
  });
  glutMouseFunc([](int button, int state, int x, int y) {
    // on mouse click
    scene.handle_mouse_button(
        MouseButtonEvent(button == GLUT_LEFT_BUTTON, state == GLUT_DOWN, x, y));
  });
  glutMotionFunc([](int x, int y) {
    // on mouse click and move
    scene.handle_mouse_drag(MouseDragEvent(x, y));
    glutPostRedisplay();
  });
  glutDisplayFunc([]() {
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
