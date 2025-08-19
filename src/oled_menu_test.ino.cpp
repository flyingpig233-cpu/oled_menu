# 1 "C:\\Users\\Lenovo\\AppData\\Local\\Temp\\tmp3_a0551o"
#include <Arduino.h>
# 1 "E:/Documents/PlatformIO/Projects/250803-125604-airm2m_core_esp32c3/src/oled_menu_test.ino"
#include "about.h"
#include "button.h"
#include "dev.h"
#include "game.h"
#include "hack.h"
#include "help.h"
#include "video.h"
#include "selector.h"
#include "test.h"
#include "menu.h"

Menu menu(&display, 3);

MenuItem item2((char*)"PPT", hack_handle);
MenuItem item8((char*)"TEST", test_handle);
MenuItem item3((char*)"GAME", game_handle);
MenuItem item5((char*)"SETTINGS", dev_handle);
MenuItem item6((char*)"ABOUT", about_handle);
MenuItem item7((char*)"HELP", help_handle);
void setup();
void loop();
static void selectButtonPressed(void *menu);
static void upButtonPressed(void *menu);
static void downButtonPressed(void *menu);
void clear_btns();
void init_btns(Menu *menu);
#line 21 "E:/Documents/PlatformIO/Projects/250803-125604-airm2m_core_esp32c3/src/oled_menu_test.ino"
void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    for (;;)
      ;
  }
  bleKeyboard.begin();
  menu.add_item(&item2);
  menu.add_item(&item8);
  menu.add_item(&item3);
  menu.add_item(&item5);
  menu.add_item(&item6);
  menu.add_item(&item7);
  init_btns(&menu);
  display.setFont(nullptr);
}

void loop() {
  upBtn.tick();
  downBtn.tick();
  leftBtn.tick();
  rightBtn.tick();
  menu.handle();
}
# 1 "E:/Documents/PlatformIO/Projects/250803-125604-airm2m_core_esp32c3/src/Ball.ino"
#include "game/ball/Ball.h"
#include "game/ball/Environment.h"
#include "game/ball/Sprite.h"

const unsigned char SPRITE_BALL_NORMAL[] = {
    3, 3, 0, 255, 0, 255, 0, 255, 0, 255, 0, 1, 1,
};

Sprite spriteBallNormal(SPRITE_BALL_NORMAL);

Ball::Ball(Environment &e) : environment(e) { reset(); }

Ball::Ball(Environment &e, float startX, float startY, float startVx,
           float startVy)
    : environment(e) {
  x = startX;
  y = startY;
  vx = startVx;
  vy = startVy;
  speed = 14;
  normalize();
}

void Ball::reset() {
  x = environment.XRES * 0.5f;
  y = environment.YRES - 3;
  vx = 25;
  vy = -33;
  speed = 50;
  normalize();
  status = STATUS_ACTIVE;
}

void Ball::normalize() {
  float l = vx * vx + vy * vy;
  if (l == 0)
    return;
  l = 1.f / sqrt(l) * speed;
  vx *= l;
  vy *= l;
}

void Ball::draw() {
  if (status != STATUS_ACTIVE)
    return;
  spriteBallNormal.draw(int(x + 0.5f), int(y + 0.5f));
}

void Ball::move(float dt) {
  if (status != STATUS_ACTIVE)
    return;
  float nx = x + vx * dt;
  float ny = y + vy * dt;
  if (nx < 0) {
    nx = 0;
    vx = -vx;
    return;
  }
  if (nx > environment.XRES - 1) {
    nx = environment.XRES - 1;
    vx = -vx;
    return;
  }
  if (ny < 0) {
    ny = 0;
    vy = -vy;
    return;
  }
  if (ny > environment.YRES - 1) {


    status = STATUS_INACTIVE;
    return;
  }

  if (vy > 0 && environment.player.hit(x, y)) {
    environment.player.reflect(*this);
    return;
  }

  x = nx;
  y = ny;
}
# 1 "E:/Documents/PlatformIO/Projects/250803-125604-airm2m_core_esp32c3/src/button.ino"
#include "button.h"
#include "exit.h"

static void selectButtonPressed(void *menu)
{
  ((Menu *)menu)->select();
}

static void upButtonPressed(void *menu)
{
  ((Menu *)menu)->prev_item();
}

static void downButtonPressed(void *menu)
{
  ((Menu *)menu)->next_item();
}

void clear_btns()
{
  upBtn.reset();
  downBtn.reset();
  leftBtn.reset();
  rightBtn.reset();
  upBtn.attachClick(nullptr, nullptr);
  downBtn.attachClick(nullptr, nullptr);
  leftBtn.attachClick(nullptr, nullptr);
  rightBtn.attachClick(nullptr, nullptr);
  upBtn.attachDoubleClick(nullptr, nullptr);
  downBtn.attachDoubleClick(nullptr, nullptr);
  leftBtn.attachDoubleClick(nullptr, nullptr);
  rightBtn.attachDoubleClick(nullptr, nullptr);
  upBtn.attachLongPressStart(nullptr, nullptr);
  downBtn.attachLongPressStart(nullptr, nullptr);
  leftBtn.attachLongPressStart(nullptr, nullptr);
  rightBtn.attachLongPressStart(nullptr, nullptr);
  upBtn.attachDuringLongPress(nullptr, nullptr);
  downBtn.attachDuringLongPress(nullptr, nullptr);
  leftBtn.attachDuringLongPress(nullptr, nullptr);
  rightBtn.attachDuringLongPress(nullptr, nullptr);
  upBtn.attachLongPressStop(nullptr, nullptr);
  downBtn.attachLongPressStop(nullptr, nullptr);
  leftBtn.attachLongPressStop(nullptr, nullptr);
  rightBtn.attachLongPressStop(nullptr, nullptr);
  upBtn.attachClick(nullptr);
  downBtn.attachClick(nullptr);
  leftBtn.attachClick(nullptr);
  rightBtn.attachClick(nullptr);
  upBtn.attachDoubleClick(nullptr);
  downBtn.attachDoubleClick(nullptr);
  leftBtn.attachDoubleClick(nullptr);
  rightBtn.attachDoubleClick(nullptr);
  upBtn.attachLongPressStart(nullptr);
  downBtn.attachLongPressStart(nullptr);
  leftBtn.attachLongPressStart(nullptr);
  rightBtn.attachLongPressStart(nullptr);
  upBtn.attachDuringLongPress(nullptr);
  downBtn.attachDuringLongPress(nullptr);
  leftBtn.attachDuringLongPress(nullptr);
  rightBtn.attachDuringLongPress(nullptr);
  upBtn.attachLongPressStop(nullptr);
  downBtn.attachLongPressStop(nullptr);
  leftBtn.attachLongPressStop(nullptr);
  rightBtn.attachLongPressStop(nullptr);
}

void init_btns(Menu *menu)
{
  clear_btns();
  upBtn.attachClick(upButtonPressed, (void *)menu);
  downBtn.attachClick(downButtonPressed, (void *)menu);
  rightBtn.attachClick(selectButtonPressed, (void *)menu);
  leftBtn.attachClick(exit_handle);
  quit = false;
}
# 1 "E:/Documents/PlatformIO/Projects/250803-125604-airm2m_core_esp32c3/src/paddle.ino"
#include "game/ball/Paddle.h"
#include "game/ball/Environment.h"
#include "game/ball/Sprite.h"

const unsigned char SPRITE_PADDLE_NORMAL[] = {
  11, 2,
  0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  6, 1,
};

Sprite spritePaddleNormal(SPRITE_PADDLE_NORMAL);

Paddle::Paddle(Environment &e)
:environment(e)
{
  x = e.XRES * 0.5f;
  y = e.YRES - 1;
  speed = 70.f;

  width = spritePaddleNormal.sx;
}

void Paddle::draw()
{
  spritePaddleNormal.draw(int(x + 0.5f), int(y + 0.5f));
}

void Paddle::left(float dt)
{
  x -= dt * speed;
  float minx = width * 0.5f;
  if(x < minx) x = minx;
}

void Paddle::right(float dt)
{
  x += dt * speed;
  float maxx = environment.XRES - 1 - width * 0.5f;
  if(x > maxx) x = maxx;
}

bool Paddle::hit(float bx, float by)
{
  return spritePaddleNormal.hit(int(bx - x + 0.5f), int(by - y + 0.5f));
}

float Paddle::corner(float bx)
{
  float cl = bx - (x - width * 0.5f);
  float cr = (x + width * 0.5f) - bx;
  if(cl >= 0 && cl <= 3)
    return cl - 3;
  if(cr >= 0 && cr <= 3)
    return 3 - cr;
  return 0;
}

void Paddle::reflect(Ball& b)
{
  if(b.vy < 0) return;
  b.vx += (b.x - x) / width * 70;
  b.vy = -b.vy;
  b.normalize();

}