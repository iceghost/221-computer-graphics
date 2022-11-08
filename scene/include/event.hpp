#pragma once

class event {
public:
  class handler;

protected:
  virtual void accept(handler &h) const = 0;
};

class mouse_event : event {
  void accept(handler &h) const override;
};

struct keyboard_event : event {
  unsigned char key;
  int x, y;
  keyboard_event(unsigned char key, int x, int y);

private:
  void accept(handler &h) const override;
};

struct reshape_event : event {
  int w, h;
  reshape_event(int w, int h);

private:
  void accept(handler &h) const override;
};

// use of visitor pattern
struct event::handler {
  void handle(const event &e);
  virtual void handle_mouse(const mouse_event &e) {}
  virtual void handle_keyboard(const keyboard_event &e) {}
  virtual void handle_reshape(const reshape_event &e) {}
};
