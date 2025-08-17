#pragma once

#include "font.h"
#include "rect.h"
#include "screen.h"
#include <OneButton.h>
#include <cmath>

double easeOutExpo(double x) { return x == 1 ? 1 : 1 - pow(2, -10 * x); }
double easeOutElastic(double x) {
  const double c4 = (2 * PI) / 3;

  return x == 0   ? 0
         : x == 1 ? 1
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

class Item {
public:
  Item() {
    this->content = nullptr;
    this->next = nullptr;
    this->prev = nullptr;
    this->active = false;
  }

  Item(char *name) {
    set_content(name);
    this->next = nullptr;
    this->prev = nullptr;
    this->active = false;
  }

  void set_content(char *name) {
    this->content = name;
    this->content_size = default_font.calcSize(strlen(name));
  }

  virtual void entry(Menu *menu) = 0;

  virtual void draw(Adafruit_SSD1306 *display, const Rect &rect) = 0;
  Size content_size;
  bool active;
  Item *next;
  Item *prev;
  char *content;
};

class MenuItem : public Item {
public:
  MenuItem() : Item(), callback(nullptr) {}
  MenuItem(char *name, void (*callback)(Menu *))
      : Item(name), callback(callback) {}

  void draw(Adafruit_SSD1306 *display, const Rect &rect) override {
    const Pos center = rect.center(content_size, Align::Center);
    display->setCursor(center.x, center.y);
    display->print(content);
  }

  void entry(Menu *menu) override { callback(menu); }
  void (*callback)(Menu *);
};

const double ANIMATION_SPEED = 0.030;

class Menu {
public:
  Menu(Adafruit_SSD1306 *display, int show_num) : show_num(show_num) {
    this->display = display;
    this->head = nullptr;
    size = 0;
    line_height = SCREEN_HEIGHT / show_num;
    process = 1;
    current_y = expect_y = idle_y = 0;
    level = 0;
  }

  void select() {
    if (current != nullptr) {
      current->entry(this);
      handle();
    }
  }

  void add_item(Item *item) {
    if (head == nullptr) {
      head = item;
      size++;
      current = item;
      item->active = true;
      current_y = expect_y = idle_y = 0;
      return;
    }
    Item *p = head;
    while (p->next != nullptr) {
      p = p->next;
    }
    p->next = item;
    item->prev = p;
    size++;
  }

  void next_item() {
    if (current->next != nullptr) {
      current->active = false;
      current = current->next;
      current->active = true;
      if (level < show_num - 1) {
        process = 0;
        level++;
        idle_y = current_y;
        expect_y += line_height;
      }
    }
  }

  void prev_item() {
    if (current->prev != nullptr) {
      current->active = false;
      current = current->prev;
      current->active = true;
      if (level > 0) {
        process = 0;
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

    Item *p = current;
    for (int i = 0; i < level; i++) {
      p = p->prev;
    }
    int cnt = 0;
    Rect item_rect(0, 0, SCREEN_WIDTH, line_height);
    while (p != nullptr && cnt < show_num) {
      p->draw(display, item_rect);
      item_rect.pos.y += line_height;
      p = p->next;
      cnt++;
    }
    display->drawRoundRect(0, current_y, SCREEN_WIDTH, line_height, 5, WHITE);
    display->display();
  }

private:
  Item *head;
  Item *current;
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
