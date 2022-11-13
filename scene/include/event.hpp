#pragma once

class Event {
public:
  class Handler;

protected:
  virtual void accept(Handler &h) const = 0;
};

class MouseEvent : Event {
  void accept(Handler &h) const override;
};

struct KeyboardEvent : Event {
  unsigned char key;
  int x, y;
  KeyboardEvent(unsigned char key, int x, int y);

private:
  void accept(Handler &h) const override;
};

struct ReshapeEvent : Event {
  int w, h;
  ReshapeEvent(int w, int h);

private:
  void accept(Handler &h) const override;
};

// use of visitor pattern
struct Event::Handler {
  void handle(const Event &e);
  virtual void handle_mouse(const MouseEvent &e) {}
  virtual void handle_keyboard(const KeyboardEvent &e) {}
  virtual void handle_reshape(const ReshapeEvent &e) {}
};
