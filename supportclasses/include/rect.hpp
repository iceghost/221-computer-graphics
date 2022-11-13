#pragma once

template <typename T> class Rect {
private:
  T l, r, b, t;

public:
  Rect(T left, T right, T bottom, T top);
  void draw();
  T get_width();
  T get_height();
};

using IntRect = Rect<int>;
using FloatRect = Rect<float>;