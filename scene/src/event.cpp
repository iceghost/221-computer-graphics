#include "event.hpp"

void event::handler::handle(const event &e) { return e.accept(*this); }

void mouse_event::accept(event::handler &h) const {
  return h.handle_mouse(*this);
}

keyboard_event::keyboard_event(unsigned char key, int x, int y) {}

void keyboard_event::accept(event::handler &h) const {
  return h.handle_keyboard(*this);
}

reshape_event::reshape_event(int w, int h) {}

void reshape_event::accept(event::handler &h) const {
  return h.handle_reshape(*this);
}