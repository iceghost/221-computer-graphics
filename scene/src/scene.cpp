#ifdef _WIN32
#include <windows.h>
#endif
#include "scene.hpp"
#include <GL/GL.h>
#include <GL/GLU.h>

// TWEAKABLE:
const auto N_SEGMENTS = 20;
const auto DZ = 0.2f;

// TWEAKABLE:
const auto CHAN_DE_DY = 0.2f;
const auto CHAN_DE_DX = 4.0f;
// FIXED:
const auto CHAN_DE_DZ = 10 * DZ;

// TWEAKABLE:
const auto CHOT_DISTANCE = 1.0f;
const auto CHOT_DIAMETER = 0.2f;

// TWEAKABLE:
const auto CHOT_1_Y = 0.5f;
// FIXED:
const auto CHOT_1_HEIGHT = DZ + DZ / 2 + 2 * DZ + DZ / 2 + DZ;

// FIXED
const auto CHOT_2_HEIGHT = DZ + DZ / 2 + DZ;

// TWEAKABLE:
const auto RAY_DX = 0.4f;
const auto RAY_DEPTH = 0.3f;
// FIXED:
const auto RAY_DY = CHOT_DISTANCE * 2;
const auto RAY_DZ = 2 * DZ;
const auto RAY_WIDTH = DZ;

// FIXED:
const auto TAM_TRUOT_DY = (CHOT_1_Y - CHAN_DE_DY) * 2;
const auto TAM_TRUOT_DX = TAM_TRUOT_DY + 2 * RAY_DEPTH;
const auto TAM_TRUOT_DZ = RAY_DZ;
const auto TAM_TRUOT_WIDTH = TAM_TRUOT_DY;
const auto TAM_TRUOT_DEPTH = DZ / 2;

// FIXED:
const auto LIEN_KET_DX = 2 * CHOT_DIAMETER;
const auto LIEN_KET_DY = CHOT_DISTANCE + 2 * CHOT_DIAMETER;
const auto LIEN_KET_DZ = DZ;

Scene::Scene() : camera({45, 3, 5, {0, CHAN_DE_DY + RAY_DY / 2, 0}}) {
  auto &chan_de = this->add_obj(Cuboid(CHAN_DE_DX, CHAN_DE_DY, CHAN_DE_DZ));
  chan_de.translate({0, CHAN_DE_DY / 2, 0});
  chan_de.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                      {1.0f, 0.0f, 0.0f, 1.0f},
                      {1.0f, 1.0f, 1.0f, 1.0f},
                      100.0f};

  auto &ray1 =
      chan_de.add_child(UBox(RAY_DZ, RAY_DX, RAY_DY, RAY_WIDTH, RAY_DEPTH));
  ray1.rotate_x(90);
  ray1.rotate_z(90);
  ray1.translate(
      {RAY_DX / 2 + TAM_TRUOT_WIDTH / 2, CHAN_DE_DY / 2 + RAY_DY / 2, 0});
  ray1.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 1.0f, 0.0f, 1.0f},
                   {1.0f, 1.0f, 1.0f, 1.0f},
                   100.0f};

  auto &ray2 =
      chan_de.add_child(UBox(RAY_DZ, RAY_DX, RAY_DY, RAY_WIDTH, RAY_DEPTH));
  ray2.rotate_x(90);
  ray2.rotate_z(-90);
  ray2.translate(
      {-RAY_DX / 2 - TAM_TRUOT_WIDTH / 2, CHAN_DE_DY / 2 + RAY_DY / 2, 0});
  ray2.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 1.0f, 0.0f, 1.0f},
                   {1.0f, 1.0f, 1.0f, 1.0f},
                   100.0f};

  // auto &tam_truot_a =
  //     chan_de.add_child(TBox(TAM_TRUOT_DX, TAM_TRUOT_DZ / 2, TAM_TRUOT_DY,
  //                            TAM_TRUOT_WIDTH, TAM_TRUOT_DEPTH));
  // tam_truot_a.rotate_x(90);
  // tam_truot_a.translate({0, CHAN_DE_DY / 2 + TAM_TRUOT_DY / 2, 0});
}

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

boolean Scene::update(const double dt) {
  auto redisplay = false;
  switch (this->move_state) {
  case Scene::MoveState::UP:
    this->camera.height += 3 * dt;
    redisplay = true;
    break;
  case Scene::MoveState::DOWN:
    this->camera.height -= 3 * dt;
    redisplay = true;
    break;
  case Scene::MoveState::IDLE:
    break;
  }
  return redisplay;
}

Scene::Object &Scene::add_obj(Mesh &&m) {
  this->objs.push_back(Scene::Object(std::move(m)));
  return this->objs.back();
}