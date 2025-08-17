#pragma once

enum class Align {
  Left,
  Center,
  Right
};

struct Pos {
  int x;
  int y;
};

struct Size {
  int width;
  int height;
  Size() : width(0), height(0) {}
  Size(int w, int h) : width(w), height(h) {}
};

struct Rect {
  Pos pos;
  Size size;

  Rect(int x, int y, int w, int h) : pos(Pos {x, y}), size(w, h) {}

  // give a size, return a rect to put it in the center of this rect
  Pos center(const Size &s, Align align = Align::Center) const {
    int x = pos.x;
    int y = pos.y;
    switch (align) {
      case Align::Left:
        x += 0;
        break;
      case Align::Center:
        x += (this->size.width - s.width) / 2;
        break;
      case Align::Right:
        x += this->size.width - s.width;
        break;
    }
    y += (this->size.height - s.height) / 2;
    return Pos {x, y};
  }
};