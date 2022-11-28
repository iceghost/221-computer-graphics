#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>

#include <cmath>
#include <iostream>
#include <memory>

#include "mesh.hpp"
#include "scene.hpp"

const double DELTA_T = 1 / 60.0;

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
  auto obj = Scene::Object(Cuboid(5, 0.2f, 4));
  obj.translate({0, 0.1f, 0});

  auto tbox1 = Scene::Object(TBox(3, 0.2f, 2, 2, 0.1f));
  tbox1.rotate_x(90);
  tbox1.translate({0, 1 + 0.1f, 0});
  obj.children.push_back(std::move(tbox1));
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

  glutKeyboardFunc([](unsigned char key, int, int) {
    switch (key) {
    case '1':
      scene->move_state = Scene::MoveState::UP;
      return;
    case '2':
      scene->move_state = Scene::MoveState::DOWN;
      return;
    }
  });

  glutKeyboardUpFunc([](unsigned char key, int, int) {
    switch (key) {
    case '1':
    case '2':
      scene->move_state = Scene::MoveState::IDLE;
    }
  });

  glutIdleFunc([]() {
    auto redisplay = false;
    switch (scene->move_state) {
    case Scene::MoveState::UP:
      scene->camera.height += 2 * DELTA_T;
      redisplay = true;
      break;
    case Scene::MoveState::DOWN:
      scene->camera.height -= 2 * DELTA_T;
      redisplay = true;
      break;
    }
    if (redisplay) {
      glutPostRedisplay();
    }
  });

  glutMainLoop();
  return 0;
}
