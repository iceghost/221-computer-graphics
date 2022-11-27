#include "event.hpp"

void Event::Handler::handle(const Event &e) { return e.accept(*this); }

MouseButtonEvent::MouseButtonEvent(bool left, bool down, int x, int y)
    : left(left), down(down), x(x), y(y) {}

void MouseButtonEvent::accept(Event::Handler &h) const {
  return h.handle_mouse_button(*this);
}

MouseDragEvent::MouseDragEvent(int x, int y) : x(x), y(y) {}

void MouseDragEvent::accept(Event::Handler &h) const {
  return h.handle_mouse_drag(*this);
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