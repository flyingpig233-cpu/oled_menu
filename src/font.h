#pragma once

#include "rect.h"
#include <Adafruit_SSD1306.h>

struct Font {
  uint8_t size;

  Font(uint8_t size) : size(size) {}
  inline int fontWidth() const { return 6 * size; }

  inline int fontHeight() const { return 7 * size; }

  inline Size calcSize(int len) const {
    return Size(len * (fontWidth() + 1) - size, fontHeight());
  }
};

const Font NORMAL_FONT(1), BIG_FONT(2);
Font default_font = BIG_FONT;