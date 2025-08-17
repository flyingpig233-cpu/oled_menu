#pragma once

#include "button.h"
#include "exit.h"
#include "game/ball/ball_handle.h"
#include "game/snake/fruit.h"
#include "game/snake/renderer.h"
#include "game/snake/snake.h"
#include "menu.h"
#include "screen.h"

void game_handle(Menu *menu) {
  Menu game_menu(&display, 3);

  MenuItem item1("SNAKE", [](Menu *m) {
    quit = false;
    Snake snake;
    Fruit fruit(&snake);
    clear_btns();
    leftBtn.attachLongPressStart(exit_handle);
    downBtn.attachClick(
        [](void *snake) { ((Snake*)snake)->turn(Direction::DOWN); }, &snake);
    upBtn.attachClick(
        [](void *snake) { ((Snake*)snake)->turn(Direction::UP); }, &snake);
    leftBtn.attachClick(
        [](void *snake) { ((Snake*)snake)->turn(Direction::LEFT); }, &snake);
    rightBtn.attachClick(
        [](void *snake) { ((Snake*)snake)->turn(Direction::RIGHT); }, &snake);
    auto startTime = millis();
    while (!quit) {
      upBtn.tick();
      downBtn.tick();
      leftBtn.tick();
      rightBtn.tick();
      if (millis() - startTime >= 350) {
        startTime = millis();
        bool resetFruit = false;
        if (snake.nextHeadPosition() == fruit.getPosition()) {
          snake.grow();
          resetFruit = true;
        }
        snake.advance();
        if (resetFruit)
          fruit.randomize(&snake);

        Renderer::startFrame();
        Renderer::renderBorder();
        Renderer::renderSnake(&snake);
        Renderer::renderFruit(&fruit);
        if (!snake.isAlive())
          Renderer::renderGameOver(&snake);
        Renderer::endFrame();
      }
    }
    init_btns(m);
  });
  MenuItem item2("PONG", ball_handle);
  game_menu.add_item(&item1);
  game_menu.add_item(&item2);
  init_btns(&game_menu);
  leftBtn.attachClick(exit_handle);
  while (!quit) {
    leftBtn.tick();
    upBtn.tick();
    downBtn.tick();
    rightBtn.tick();
    game_menu.handle();
  }
  init_btns(menu);
}