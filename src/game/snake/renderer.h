#pragma once

#include "Arduino.h"
#include "snake.h"
#include "position.h"
#include "fruit.h"

namespace Renderer {
  void initialize();
  void renderBorder();
  void renderSnake(Snake *snake);
  void renderFruit(Fruit *fruit);
  void renderGameOver(Snake *snake);
  void startFrame();
  void endFrame();
}


#include "../../screen.h"

#define CELL_SIZE 8

namespace Renderer {

  unsigned long time_total = 0;
  unsigned long time_last = 0;
  float framerate() {
    time_last = time_total;
    time_total = micros();
    return 1.0 / ((time_total - time_last) / 1000000.0);
  }

  void renderBorder() {
    display.drawRect(0, 0, 128, 64, WHITE);
  }
  
  void renderSnake(Snake *snake) {
    const uint8_t **body = snake->getBody();
    for(int i = 0; i < Snake::BODY_WIDTH; i++) {
      for(int j = 0; j < Snake::BODY_HEIGHT; j++) {
        if(body[i][j] > 0) {
          display.fillRect(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
        }
      }
    }
  }

  void renderFruit(Fruit * fruit) {
    Position position = fruit->getPosition();
    display.fillRect(position.x * CELL_SIZE + 1, position.y * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2, WHITE);
  }

  void renderGameOver(Snake *snake) {
    display.clearDisplay();
    display.setTextColor(1);
    display.setCursor(5, 15);
    display.setTextSize(2);
    display.print("Game Over!");
    display.setCursor(34, 47);
    display.setTextSize(1);
    display.print("Points: ");
    display.print(snake->getPoints());
  }

  void startFrame() {
    display.clearDisplay();
  }

  void endFrame() {
    display.display();
  }

}