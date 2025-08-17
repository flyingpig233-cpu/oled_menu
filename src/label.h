#pragma once

#include "menu.h"

class Label : public Item {
public:
	Label(char *text) : Item(text) {}

	void draw(Adafruit_SSD1306 *display, const Rect &rect) override {
    const Pos center = rect.center(content_size, Align::Center);
    display->setCursor(center.x, center.y);
		display->print(content);
	}

	void entry(Menu *menu) override {}
};