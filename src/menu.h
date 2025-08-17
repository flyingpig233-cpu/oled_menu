#pragma once

#include "font.h"
#include "rect.h"
#include "screen.h"
#include <OneButton.h>
#include <cmath>

double easeOutExpo(double x) { return x == 1 ? 1 : 1 - pow(2, -10 * x); }
double easeOutElastic(double x) {
const double c4 = (2 * PI) / 3;

return x == 0
  ? 0
  : x == 1
  ? 1
  : pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
}

double easeOutBounce(double x) {
const double n1 = 7.5625;
const double d1 = 2.75;

if (x < 1 / d1) {
    return n1 * x * x;
} else if (x < 2 / d1) {
    return n1 * (x -= 1.5 / d1) * x + 0.75;
} else if (x < 2.5 / d1) {
    return n1 * (x -= 2.25 / d1) * x + 0.9375;
} else {
    return n1 * (x -= 2.625 / d1) * x + 0.984375;
}
}
class Menu;

struct MenuItem {
  char *name;
  Size name_size;
  bool active;
  void (*callback)(Menu*);
  MenuItem *next;
  MenuItem *prev;

  MenuItem() {
    this->name = NULL;
    this->callback = NULL;
    this->next = NULL;
    this->prev = NULL;
    this->active = false;
  }

  MenuItem(char *name, void (*callback)(Menu*)) {
    setName(name);
    this->callback = callback;
    this->next = NULL;
    this->prev = NULL;
    this->active = false;
  }

  void setName(char *name) {
    this->name = name;
    this->name_size = default_font.calcSize(strlen(name));
  }

  void entry(Menu *menu) {
    callback(menu);
  }

  void draw(Adafruit_SSD1306 *display, const Rect &rect) {
    const Pos center = rect.center(name_size, Align::Center);
    display->setCursor(center.x, center.y);
    display->print(name);
  }
};

const double ANIMATION_SPEED = 0.035;

class Menu {
public:
  Menu(Adafruit_SSD1306 *display, int show_num) : show_num(show_num) {
    this->display = display;
    this->head = MenuItem();
    size = 0;
    line_height = SCREEN_HEIGHT / show_num;
    process = 1;
    current_y = expect_y = idle_y = 0;
    level = 0;

  }

  void select() {
    if (current != NULL && current->callback != NULL) {
      current->entry(this);
      handle();
    }
  }

  void add_item(MenuItem *item) {
    MenuItem *p = &head;
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = item;
    if (size == 0) {
      current = item;
      item->active = true;
      current_y = expect_y = idle_y = 0;
    } else {
      item->prev = p;
    }
    size++;
  }

  void next_item() {
    if (current->next != NULL) {
      current->active = false;
      current = current->next;
      current->active = true;
      process = 0;
      if (level < show_num - 1) {
        level++;
        idle_y = current_y;
        expect_y += line_height;
      }
    }
  }

  void prev_item() {
    if (current->prev != NULL) {
      current->active = false;
      current = current->prev;
      current->active = true;
      process = 0;
      if (level > 0) {
        level--;
        idle_y = current_y;
        expect_y -= line_height;
      }
    }
  }
  void handle() {
    draw();
    if (current_y != expect_y) {
      if (process == 1) {
        process = 0;
      }
      if (process + ANIMATION_SPEED >= 1) {
        process = 1;
        current_y = expect_y;
        return;
      } else
        process += ANIMATION_SPEED;
      current_y = idle_y + int((expect_y - idle_y) * easeOutBounce(process));
    }
  }

  void draw() {
    display->clearDisplay();
    display->setTextColor(WHITE);
    display->setTextSize(default_font.size);

    MenuItem *p = current;
    for (int i = 0; i < level; i++) {
      p = p->prev;
    }
    int cnt = 0;
    Rect item_rect(0, 0, SCREEN_WIDTH, line_height);
    while (p != NULL && cnt < show_num) {
      p->draw(display, item_rect);
      item_rect.pos.y += line_height;
      p = p->next;
      cnt++;
    }
    display->drawRect(0, current_y, SCREEN_WIDTH, line_height, WHITE);
    display->display();
  }

private:
  MenuItem head;
  MenuItem *current;
  int show_num;
  int line_height;
  int size;
  int current_y;
  int idle_y;
  int expect_y;
  int level;
  double process;
  Adafruit_SSD1306 *display;
};
