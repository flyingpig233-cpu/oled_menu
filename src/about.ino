#include "about.h"

void about_handle(Menu *menu) {
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
    rightBtn.tick();
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5, 20);
    display.print("TECHNOLOGY");
    display.display();
  }
  init_btns(menu);
}