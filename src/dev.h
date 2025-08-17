#pragma once

#include "button.h"
#include "exit.h"
#include "menu.h"
#include "screen.h"

void dev_handle(Menu *menu) {
  quit = false;
  clear_btns();
  leftBtn.attachClick(exit_handle);
  while (!quit) {
    upBtn.tick();
    downBtn.tick();
    leftBtn.tick();
    rightBtn.tick();
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(10, 20);
    display.print("Dev...");
    display.display();
  }
  init_btns(menu);
}