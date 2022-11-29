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

void update(int) {
  auto redisplay = scene->update(DELTA_T);
  if (redisplay) {
    glutPostRedisplay();
  }
  glutTimerFunc(int(1000 * DELTA_T), update, 0);
}

int main(int argc, const char **argv) {
  glutInit(&argc, (char **)argv); // initialize the tool kit
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
                      GLUT_DEPTH);  // set the display mode
  glutInitWindowSize(600, 300);     // set window size
  glutInitWindowPosition(100, 100); // set window position on screen
  glutCreateWindow("Nguyen Duy Khang - 2011364"); // open the screen window

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  float myLightPosition[] = {1.0f, 2.0f, 5.0f, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);

  float amb0[] = {0.2f, 0.4f, 0.6f, 1.0f};
  float diff0[] = {0.8f, 0.9f, 0.8f, 1.0f};
  float spec0[] = {1.0f, 0.8f, 1.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

  scene = std::make_unique<Scene>();

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
    case '=':
    case '+':
      scene->zoom_state = Scene::ZoomState::MAGNIFY;
      break;
    case '_':
    case '-':
      scene->zoom_state = Scene::ZoomState::MINIFY;
      break;
    case 'v':
      scene->camera.dimension = Scene::Camera::Dimension::TWO;
      glutPostRedisplay();
      break;
    case 'V':
      scene->camera.dimension = Scene::Camera::Dimension::THREE;
      glutPostRedisplay();
      break;
    case 'a':
      scene->animate_state = Scene::AnimateState::ON;
      break;
    case 'A':
      scene->animate_state = Scene::AnimateState::OFF;
      break;
    }
  });

  glutSpecialFunc([](int key, int, int) {
    switch (key) {
    case GLUT_KEY_UP:
      scene->vertical_state = Scene::MoveVerticalState::UP;
      break;
    case GLUT_KEY_DOWN:
      scene->vertical_state = Scene::MoveVerticalState::DOWN;
      break;
    case GLUT_KEY_LEFT:
      scene->horizontal_state = Scene::MoveHorizontalState::LEFT;
      break;
    case GLUT_KEY_RIGHT:
      scene->horizontal_state = Scene::MoveHorizontalState::RIGHT;
      break;
    }
  });

  glutKeyboardUpFunc([](unsigned char key, int, int) {
    switch (key) {
    case '=':
    case '+':
    case '_':
    case '-':
      scene->zoom_state = Scene::ZoomState::IDLE;
      break;
    }
  });

  glutSpecialUpFunc([](int key, int, int) {
    switch (key) {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
      scene->vertical_state = Scene::MoveVerticalState::IDLE;
      break;
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
      scene->horizontal_state = Scene::MoveHorizontalState::IDLE;
      break;
    }
  });

  update(0);

  glutMainLoop();
  return 0;
}
