#pragma once
#include "Ball.h"
#include "../../screen.h"
#include "../../font.h"
#include "Paddle.h"
#include "../../button.h"

class Environment
{
  public:
  int XRES;
  int YRES;
  Ball ball;
  Paddle player;
  int status;
  const int STATUS_START = 0;
  const int STATUS_RUNNING = 1;
  const int STATUS_GAME_OVER = 2;
  const int STATUS_INTRO = 3;
  const int STATUS_READY = 4;
  const int STATUS_FINISH = 5;
  bool lbtn, rbtn;
  int score;
  int level;
  int lives;
  float timer;
  void setLeft(bool state) { lbtn = state; }
  void setRight(bool state) { rbtn = state; }
  Environment();
  void startGame();
  void initLevel();
  void nextLevel();
  void ready();
  bool isBlockVisible(int c, int r);
  void move(float dt);
  void draw();
};

#include "Block.h"
#include "Levels.h"

const int BLOCK_COLUMNS = 8;
const int BLOCK_ROWS = 10;
const int BLOCK_COUNT = BLOCK_COLUMNS * BLOCK_ROWS;
Block blocks[BLOCK_COUNT];

Environment::Environment()
  :XRES(SCREEN_WIDTH),
  YRES(SCREEN_HEIGHT),
  ball(*this),
  player(*this)
{
  startGame();
}

void Environment::startGame()
{
  score = 0;
  level = 0;
  lives = 3;
  initLevel();
  ball.reset();
  ready();
}

void Environment::ready()
{
    status = STATUS_READY;
    timer = 3;
}

bool Environment::isBlockVisible(int c, int r)
{
  if(r < 0 || r >= BLOCK_ROWS) return false;
  if(c < 0 || c >= BLOCK_COLUMNS) return false;
  return blocks[r * BLOCK_COLUMNS + c].isVisible();
}

void Environment::initLevel()
{
  for(int y = 0; y < BLOCK_ROWS; y++)
    for(int x = 0; x < BLOCK_COLUMNS; x++)
      blocks[y * BLOCK_COLUMNS + x].init(*this, levels[level][y * BLOCK_COLUMNS + x], x, y);
}

void Environment::nextLevel()
{
  if(level == 9)
  {
    status = STATUS_FINISH;
    return;
  }
  level++;
  lives++;
  initLevel();
  ball.reset();
  ready();
}

void Environment::move(float dt)
{
  if(status == STATUS_GAME_OVER || status == STATUS_FINISH)
  {
    timer -= dt;
    if(timer <= 0)
    if(lbtn || rbtn) {
       startGame(); 
       if (lbtn) {
         lbtn = false;
       } else {
         rbtn = false;
       }
    }
    
    return;
  }
  if(status == STATUS_READY)
  {
    timer -= dt;
    if(timer <= 0)
    if(lbtn || rbtn)
       status = STATUS_RUNNING; 
  }  
  for(int i = 0; i < BLOCK_COUNT; i++)
    blocks[i].move(dt);
  if(lbtn)
  {
    if(status == STATUS_START)
      status = STATUS_RUNNING;
    player.left(dt);
    lbtn = false;
  }
  if(rbtn)
  {
    if(status == STATUS_START)
      status = STATUS_RUNNING;
    player.right(dt);
    rbtn = false;
  }
  if(status == STATUS_RUNNING)
    ball.move(dt);
  for(int i = 0; i < BLOCK_COUNT; i++)
  if(blocks[i].hit(ball.x, ball.y))
  {
    blocks[i].reflect(ball);
    break;
  }
  
  if(ball.status == Ball::STATUS_INACTIVE)
  {
    lives--;
    if(lives == 0)
    {
      status = STATUS_GAME_OVER;
      timer = 3;
    }
    else
    {
      ball.reset();
      ready();
    }
  }
  for(int i = 0; i < BLOCK_COUNT; i++)
    if(!blocks[i].irelevant()) return;
  //still here.. level clear
  nextLevel();
}

void Environment::draw()
{
  if(status == STATUS_GAME_OVER)
  {
    float t = timer > 0 ? timer : 0;
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(6, 8 + int(t * 20));
    display.println("GAME OVER");
    //if(timer <= 0)
    {
      display.setCursor(18, 20 + int(t * 50));
      display.print("score");  
      int s = score;
      int p = 0;
      do{
        s /= 10;
        p++;
      }while(s > 0);
      p *= default_font.fontWidth();
      display.setCursor((XRES - p) / 2 + t, 40 + int(t * 40));
      display.print(score);  
    }
    return;  
  }
  
  if(status == STATUS_FINISH)
  {
    display.clearDisplay();
    float t = timer > 0 ? timer : 0;
    display.setCursor(8, 8 + int(t * 20));
    display.println("YOU WON!");
    //if(timer <= 0)
    {
      display.setCursor(18, 20 + int(t * 30));
      display.print("score");  
      int s = score;
      int p = 0;
      do{
        s /= 10;
        p++;
      }while(s > 0);
      p *= default_font.fontWidth();
      display.setCursor((XRES - p) / 2 + t, 30 + int(t * 40));
      display.print(score);  
    }
    return;  
  }
  
  for(int i = 0; i < lives; i++)
    display.drawPixel(i * 3, YRES - 1, WHITE);
  for(int i = 0; i < BLOCK_COUNT; i++)
    blocks[i].draw();
  player.draw();
  ball.draw();
  
  if(status == STATUS_READY)
  {
    display.clearDisplay();
    display.drawRect(8, 6, 48, 12, WHITE);
    display.setCursor(11, 8);
    display.print("level ");
    display.print(level);
    if(timer <= 0)
    {
      display.drawRect(8, 18, 48, 12, WHITE);
      display.setCursor(15, 30);
      display.println("ready?");
    }
  }  
}