#include "event.hpp"

void Event::Handler::handle(const Event &e) { return e.accept(*this); }

void MouseEvent::accept(Event::Handler &h) const {
  return h.handle_mouse(*this);
}

KeyboardEvent::KeyboardEvent(unsigned char key, int x, int y)
    : key(key), x(x), y(y) {}

void KeyboardEvent::accept(Event::Handler &h) const {
  return h.handle_keyboard(*this);
}

ReshapeEvent::ReshapeEvent(int w, int h) : w(w), h(h) {}

void ReshapeEvent::accept(Event::Handler &h) const {
  return h.handle_reshape(*this);
}