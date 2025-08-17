#pragma once
#include "button.h"
#include "video.h"
#include "dev.h"
#include "exit.h"
#include "label.h"
#include "menu.h"
#include "screen.h"
#include "selector.h"

void test_handle(Menu *menu) {
  Menu test_menu(&display, 3);

  init_btns(&test_menu);
  Label label("LABEL");
  Selector menu1("TOGGLE");
  MenuItem menu2("OPTION", [](Menu *m) {
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

      display.setTextSize(1);           
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.cp437(true);
      for (int16_t i = 0; i < 256; i++) {
        if (i == '\n')
          display.write(' ');
        else
          display.write(i);
      }
    }
    init_btns(m);
  });
	MenuItem menu3("VIDEO", video_handle);

  test_menu.add_item(&label);
  test_menu.add_item(&menu1);
  test_menu.add_item(&menu2);
  test_menu.add_item(&menu3);
  while (!quit) {
    leftBtn.tick();
    upBtn.tick();
    downBtn.tick();
    rightBtn.tick();
    test_menu.handle();
  }
  init_btns(menu);
}