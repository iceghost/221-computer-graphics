#include "event.hpp"

void Event::Handler::handle(const Event &e) { return e.accept(*this); }

void MouseEvent::accept(Event::Handler &h) const {
  return h.handleMouse(*this);
}

KeyboardEvent::KeyboardEvent(unsigned char key, int x, int y) {}

void KeyboardEvent::accept(Event::Handler &h) const {
  return h.handleKeyboard(*this);
}

ReshapeEvent::ReshapeEvent(int w, int h) {}

void ReshapeEvent::accept(Event::Handler &h) const {
  return h.handleReshape(*this);
}