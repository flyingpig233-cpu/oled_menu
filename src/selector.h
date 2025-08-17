#pragma once
#include "menu.h"

class Selector : public Item {
public:
  Selector(char *name, bool state = false)
      : Item(name), state(state) {}
  void draw(Adafruit_SSD1306 *display, const Rect &rect) override {
    const Pos center = rect.center(content_size, Align::Center);
    display->setCursor(center.x, center.y);
		if (state) {
			display->setTextColor(BLACK);
			display->fillRoundRect(rect.pos.x, rect.pos.y, rect.size.width, rect.size.height, 5, WHITE);
		}
    display->print(content);
		if (state)
			display->setTextColor(WHITE);
	}
	void entry(Menu *menu) override {
		state = !state;
	}

private:
  bool state;
};