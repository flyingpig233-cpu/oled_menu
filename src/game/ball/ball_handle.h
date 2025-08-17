#pragma once
#include "../../button.h"
#include "../../exit.h"
#include "../../menu.h"
#include "Environment.h"

void ball_handle(Menu *menu) {
  clear_btns();
  Environment env;
  leftBtn.attachDoubleClick(exit_handle);
  downBtn.attachClick([](void *env) { ((Environment *)env)->setLeft(true); },
                      &env);
  upBtn.attachClick([](void *env) { ((Environment *)env)->setRight(true); },
                    &env);
  unsigned int oldTime = 0;
  while (!quit) {
    upBtn.tick();
    downBtn.tick();
    leftBtn.tick();
    unsigned int t = millis();
    float dt = (t - oldTime) * 0.001;
    oldTime = t;
    display.clearDisplay();
    display.setCursor(0, 0);
    // oled.print(fps);
    // oled.println("fps");
    env.move(dt);
    env.draw();
    display.display();
  }
  init_btns(menu);
}