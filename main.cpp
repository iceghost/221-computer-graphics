#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>

#include <cmath>
#include <iostream>
#include <memory>

#include "mesh.hpp"
#include "scene.hpp"

std::unique_ptr<Scene> scene = nullptr;

int main(int argc, const char **argv) {
  //	cout << "1. Tetrahedron" << endl;
  //	cout << "2. Cube" << endl;
  //	cout << "Input the choice: " << endl;
  //	cin  >> nChoice;

  glutInit(&argc, (char **)argv); // initialize the tool kit
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
                      GLUT_DEPTH);  // set the display mode
  glutInitWindowSize(600, 300);     // set window size
  glutInitWindowPosition(100, 100); // set window position on screen
  glutCreateWindow("Nguyen Duy Khang - 2011364"); // open the screen window

  glEnable(GL_DEPTH_TEST);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  scene = std::make_unique<Scene>();
  auto obj = Scene::Object(Cuboid(4, 1, 2));
  scene->objs.push_back(std::move(obj));

  glutDisplayFunc([]() {
    scene->display();
    glutSwapBuffers();
  });

  glutReshapeFunc([](int width, int height) {
    scene->camera.aspect_ratio = float(width) / height;
    scene->camera.screen_width = width;
    glutPostRedisplay();
  });

  // glutKeyboardFunc([](unsigned char key, int, int) {
  //   std::cout << "Got key: " << key << std::endl;
  //   if (key == GLUT_KEY_F4) {
  //     exit(0);
  //   }
  // });

  glutMainLoop();
  return 0;
}
