#ifdef _WIN32
#include <windows.h>
#endif
#include "scene.hpp"
#include <GL/GL.h>
#include <GL/GLU.h>
#include <cmath>

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
const auto CHOT_1_HEIGHT = DZ + DZ + DZ / 2 + 2 * DZ + DZ / 2 + DZ + DZ / 4;

// FIXED
const auto CHOT_2_HEIGHT = DZ + DZ / 2 + DZ + DZ / 4;

// TWEAKABLE:
const auto RAY_DX = 0.4f;
const auto RAY_DEPTH = 0.3f;
// FIXED:
const auto RAY_DY = CHOT_DISTANCE * 2 + 2 * (CHOT_1_Y - CHAN_DE_DY);
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

// FIXED:
const auto BUT_VE_B_DY = LIEN_KET_DY;

// TWEAKABLE:
const auto GIA_DO_A_DX = TAM_TRUOT_WIDTH * 2 / 3;
// FIXED:
const auto GIA_DO_A_DZ = DZ;
const auto GIA_DO_A_DY = TAM_TRUOT_DY / 2 + CHOT_DISTANCE - CHOT_DIAMETER;

// FIXED:
const auto GIA_DO_B_HOLE_DX = 2 * CHOT_DISTANCE + CHOT_DIAMETER;
const auto GIA_DO_B_HOLE_DY = CHOT_DIAMETER;
const auto GIA_DO_B_DX = GIA_DO_B_HOLE_DX + CHOT_DIAMETER;
const auto GIA_DO_B_DY = 2 * CHOT_DIAMETER;
const auto GIA_DO_B_DZ = DZ;

Scene::Scene() : camera({45, 3, 2, {0, CHAN_DE_DY + RAY_DY / 2, 0}}) {
  auto &chan_de = this->add_obj(Cuboid(CHAN_DE_DX, CHAN_DE_DY, CHAN_DE_DZ));
  chan_de.translate([](double) { return Vector3(0, CHAN_DE_DY / 2, 0); });
  chan_de.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                      {1.0f, 0.0f, 0.0f, 1.0f},
                      {1.0f, 1.0f, 1.0f, 1.0f},
                      100.0f};

  auto &ray1 =
      chan_de.add_child(UBox(RAY_DZ, RAY_DX, RAY_DY, RAY_WIDTH, RAY_DEPTH));
  ray1.rotate_x([](double) { return 90.0; });
  ray1.rotate_z([](double) { return 90.0; });
  ray1.translate([](double) {
    return Vector3(RAY_DX / 2 + TAM_TRUOT_WIDTH / 2,
                   CHAN_DE_DY / 2 + RAY_DY / 2, 0);
  });
  ray1.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 1.0f, 0.0f, 1.0f},
                   {1.0f, 1.0f, 1.0f, 1.0f},
                   100.0f};

  auto &ray2 =
      chan_de.add_child(UBox(RAY_DZ, RAY_DX, RAY_DY, RAY_WIDTH, RAY_DEPTH));
  ray2.rotate_x([](double) { return 90.0; });
  ray2.rotate_z([](double) { return -90.0; });
  ray2.translate([](double) {
    return Vector3(-RAY_DX / 2 - TAM_TRUOT_WIDTH / 2,
                   CHAN_DE_DY / 2 + RAY_DY / 2, 0);
  });
  ray2.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 1.0f, 0.0f, 1.0f},
                   {1.0f, 1.0f, 1.0f, 1.0f},
                   100.0f};

  auto &tam_truot_a =
      chan_de.add_child(TBox(TAM_TRUOT_DX, TAM_TRUOT_DZ / 2, TAM_TRUOT_DY,
                             TAM_TRUOT_WIDTH, TAM_TRUOT_DEPTH));
  tam_truot_a.rotate_x([](double) { return 90.0; });
  tam_truot_a.translate([](double t) {
    return Vector3(0,
                   CHAN_DE_DY / 2 + TAM_TRUOT_DY / 2 +
                       float((std::cos(t * 2 * M_PI + M_PI) + 1) / 2) * 2 *
                           CHOT_DISTANCE,
                   TAM_TRUOT_DZ / 4);
  });
  tam_truot_a.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                          {0.0f, 0.0f, 1.0f, 1.0f},
                          {1.0f, 1.0f, 1.0f, 1.0f},
                          100.0f};

  auto &tam_truot_b =
      tam_truot_a.add_child(TBox(TAM_TRUOT_DX, TAM_TRUOT_DZ / 2, TAM_TRUOT_DY,
                                 TAM_TRUOT_WIDTH, TAM_TRUOT_DEPTH));
  tam_truot_b.rotate_z([](double) { return 180.0; });
  tam_truot_b.translate(
      [](double) { return Vector3(0, -TAM_TRUOT_DZ / 2, 0); });
  tam_truot_b.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                          {0.0f, 0.0f, 1.0f, 1.0f},
                          {1.0f, 1.0f, 1.0f, 1.0f},
                          100.0f};

  auto &chot_1 = tam_truot_a.add_child(
      Cylinder(N_SEGMENTS, CHOT_1_HEIGHT, CHOT_DIAMETER / 2));
  chot_1.rotate_y([](double time) { return time * 360; });
  chot_1.translate([](double) {
    return Vector3(0, -TAM_TRUOT_DZ / 4 - CHOT_1_HEIGHT / 2 + 7 * DZ / 2, 0);
  });
  chot_1.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                     {1.0f, 0.0f, 0.0f, 1.0f},
                     {1.0f, 1.0f, 1.0f, 1.0f},
                     100.0f};

  auto &lien_ket =
      chot_1.add_child(Cuboid(LIEN_KET_DX, LIEN_KET_DZ, LIEN_KET_DY));
  lien_ket.translate([](double) {
    return Vector3(0, LIEN_KET_DZ / 2 - 3 * DZ, -CHOT_DISTANCE / 2);
  });
  lien_ket.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                       {0.5f, 0.5f, 0.5f, 1.0f},
                       {1.0f, 1.0f, 1.0f, 1.0f},
                       100.0f};

  auto &chot_2 = lien_ket.add_child(
      Cylinder(N_SEGMENTS, CHOT_2_HEIGHT, CHOT_DIAMETER / 2));
  chot_2.translate([](double) {
    return Vector3(0, LIEN_KET_DZ / 2 + CHOT_2_HEIGHT / 2 - 5 * DZ / 2,
                   -CHOT_DISTANCE / 2);
  });
  chot_2.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                     {1.0f, 0.0f, 0.0f, 1.0f},
                     {1.0f, 1.0f, 1.0f, 1.0f},
                     100.0f};

  auto &but_ve_a = chot_1.add_child(
      HollowCylinder(N_SEGMENTS, DZ, 3 * CHOT_DIAMETER / 2, CHOT_DIAMETER / 2));
  but_ve_a.translate([](double) { return Vector3(0, 3 * DZ / 2, 0); });
  but_ve_a.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                       {0.5f, 0.5f, 0.5f, 1.0f},
                       {1.0f, 1.0f, 1.0f, 1.0f},
                       100.0f};

  auto &but_ve_b = but_ve_a.add_child(Cuboid(CHOT_DIAMETER, DZ, BUT_VE_B_DY));
  but_ve_b.translate(
      [](double) { return Vector3(0, 0, -BUT_VE_B_DY / 2 - CHOT_DIAMETER); });
  but_ve_b.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                       {0.5f, 0.5f, 0.5f, 1.0f},
                       {1.0f, 1.0f, 1.0f, 1.0f},
                       100.0f};

  auto &but_ve_c = but_ve_b.add_child(
      PointedCylinder(N_SEGMENTS, DZ, CHOT_DIAMETER / 4, DZ / 2));
  but_ve_c.translate(
      [](double) { return Vector3(0, DZ, -BUT_VE_B_DY / 2 + CHOT_DIAMETER); });
  but_ve_c.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                       {1.0f, 0.0f, 0.0f, 1.0f},
                       {1.0f, 1.0f, 1.0f, 1.0f},
                       100.0f};

  auto &gia_do_a =
      chan_de.add_child(Cuboid(GIA_DO_A_DX, GIA_DO_A_DY, GIA_DO_A_DZ));
  gia_do_a.translate([](double) {
    return Vector3(0, CHAN_DE_DY / 2 + GIA_DO_A_DY / 2, -3.5f * DZ);
  });
  gia_do_a.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                       {0.0f, 1.0f, 1.0f, 1.0f},
                       {1.0f, 1.0f, 1.0f, 1.0f},
                       100.0f};

  auto &gia_do_b = gia_do_a.add_child(
      HollowBox(N_SEGMENTS, GIA_DO_B_DY, GIA_DO_B_DZ, GIA_DO_B_DX,
                GIA_DO_B_HOLE_DY, GIA_DO_B_HOLE_DX));
  gia_do_b.rotate_x([](double) { return 90.0; });
  gia_do_b.rotate_y([](double) { return 90.0; });
  gia_do_b.translate(
      [](double) { return Vector3(0, GIA_DO_A_DY / 2 + GIA_DO_B_DY / 2, 0); });
  gia_do_b.material = {{0.0f, 0.0f, 0.0f, 1.0f},
                       {0.0f, 1.0f, 1.0f, 1.0f},
                       {1.0f, 1.0f, 1.0f, 1.0f},
                       100.0f};
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
    obj.draw(this->t);
  }

  glFlush();
}

boolean Scene::update(const double dt) {
  auto redisplay = false;

  if (this->camera.dimension == Scene::Camera::Dimension::THREE) {
    switch (this->vertical_state) {
    case Scene::MoveVerticalState::UP:
      this->camera.height += 10 * dt;
      redisplay = true;
      break;
    case Scene::MoveVerticalState::DOWN:
      this->camera.height -= 10 * dt;
      redisplay = true;
      break;
    case Scene::MoveVerticalState::IDLE:
      break;
    }
  }

  switch (this->horizontal_state) {
  case Scene::MoveHorizontalState::LEFT:
    this->camera.angle -= 90 * dt;
    redisplay = true;
    break;
  case Scene::MoveHorizontalState::RIGHT:
    this->camera.angle += 90 * dt;
    redisplay = true;
    break;
  case Scene::MoveHorizontalState::IDLE:
    break;
  }

  if (this->camera.dimension == Scene::Camera::Dimension::THREE) {
    switch (this->zoom_state) {
    case Scene::ZoomState::MAGNIFY:
      this->camera.distance -= 2 * dt;
      if (this->camera.distance < 0)
        this->camera.distance = 0;
      redisplay = true;
      break;
    case Scene::ZoomState::MINIFY:
      this->camera.distance += 2 * dt;
      redisplay = true;
      break;
    case Scene::ZoomState::IDLE:
      break;
    }
  }

  if (this->animate_state == Scene::AnimateState::ON) {
    this->t +=
        0.2 *
        dt; // 1 second progress 0.2, so duration of animation is 5 seconds
    // loop back
    if (this->t > 1)
      this->t = 0;
    redisplay = true;
  }

  return redisplay;
}

Scene::Object &Scene::add_obj(Mesh &&m) {
  this->objs.push_back(Scene::Object(std::move(m)));
  return this->objs.back();
}