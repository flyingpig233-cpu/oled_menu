#pragma once
#include "menu.h"
#include "button.h"
#include "dev.h"
#include "exit.h"
#include "screen.h"

void help_handle(Menu *menu) {
  Menu help_menu(&display, 3);

  MenuItem item1("HACK HELP", [](Menu *m) {
    quit = false;
    clear_btns();
    upBtn.attachClick(exit_handle);
    downBtn.attachClick(exit_handle);
    leftBtn.attachClick(exit_handle);
    rightBtn.attachClick(exit_handle);
    while (!quit) {
      upBtn.tick();
      downBtn.tick();
      leftBtn.tick();
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("Controller");
      display.setTextSize(1);
      display.setCursor(0, 20);
      display.print("Do u want to control the PPT?");
      display.setCursor(0, 40);
      display.print("Up: Right Down: Left");
      display.setCursor(0, 50);
      display.print("Select: Esc");
      display.display();
    }
    init_btns(m);
  });

  MenuItem item2("CHAT HELP", dev_handle);
  help_menu.add_item(&item1);
  help_menu.add_item(&item2);
  init_btns(&help_menu);
  leftBtn.attachClick(exit_handle);
  while (!quit) {
    leftBtn.tick();
    upBtn.tick();
    downBtn.tick();
    rightBtn.tick();
    help_menu.handle();
  }
  init_btns(menu);
}