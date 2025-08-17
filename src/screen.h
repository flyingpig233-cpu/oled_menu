#pragma once

#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_MOSI 3 // D1
#define OLED_CLK 2  // D0
#define OLED_DC 6   // DC
#define OLED_CS 7   // None
#define OLED_RESET 10 // RES

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK,
                         OLED_DC, OLED_RESET, OLED_CS);
