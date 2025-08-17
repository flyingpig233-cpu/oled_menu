#include "hack.h"

#include "button.h"
#include "exit.h"
#include "screen.h"
#include <Adafruit_SSD1306.h>

void hack_handle(Menu *menu) {
  quit = false;
  current_key = "";
  clear_btns();
  leftBtn.attachClick([]() {
    if (bleKeyboard.isConnected()) {
      current_key = "Left";
      bleKeyboard.press(KEY_LEFT_ARROW);
      bleKeyboard.release(KEY_LEFT_ARROW);
    }
  });
  leftBtn.attachDoubleClick([]() {
    if (bleKeyboard.isConnected()) {
      current_key = "Home";
      bleKeyboard.press(KEY_HOME);
      bleKeyboard.release(KEY_HOME);
    }
  });
  leftBtn.attachLongPressStart(exit_handle);
  

  rightBtn.attachClick([]() {
    if (bleKeyboard.isConnected()) {
      current_key = "Right";
      bleKeyboard.press(KEY_RIGHT_ARROW);
      bleKeyboard.release(KEY_RIGHT_ARROW);
    }
  });
  rightBtn.attachDoubleClick([]() {
    if (bleKeyboard.isConnected()) {
      current_key = "END";
      bleKeyboard.press(KEY_END);
      bleKeyboard.release(KEY_END);
    }
  });
  rightBtn.attachLongPressStart([]() {
    if (bleKeyboard.isConnected()) {
      current_key = "ESC";
      bleKeyboard.press(KEY_ESC);
      bleKeyboard.release(KEY_ESC);
    }
  });
  upBtn.attachClick([]() {
    if (bleKeyboard.isConnected()) {
      current_key = "Erase";
      bleKeyboard.print("E");
    }
  });
  upBtn.attachLongPressStart([]() {
    if (bleKeyboard.isConnected()) {
      current_key = "Video";
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.press(KEY_F5);
      bleKeyboard.release(KEY_LEFT_CTRL);
      bleKeyboard.release(KEY_LEFT_ALT);
      bleKeyboard.release(KEY_F5);
    }
  });
  downBtn.attachClick([]() {
    if (bleKeyboard.isConnected()) {
      current_key = "Explorer";
      bleKeyboard.press(KEY_MEDIA_LOCAL_MACHINE_BROWSER);
      bleKeyboard.release(KEY_MEDIA_LOCAL_MACHINE_BROWSER);
    }
  });

  while (!quit) {
    upBtn.tick();
    downBtn.tick();
    leftBtn.tick();
    rightBtn.tick();
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    if (bleKeyboard.isConnected()) {
      display.print("Connected");
    } else {
      display.print("Pairing");
    }
    display.setCursor(0, 40);
    display.print(current_key);
    display.display();
  }
  init_btns(menu);
}