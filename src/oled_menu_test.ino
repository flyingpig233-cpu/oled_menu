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

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    for (;;)
      ;  // Don't proceed, loop forever
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