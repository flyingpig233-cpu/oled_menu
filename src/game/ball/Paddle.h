#pragma once
#include "Ball.h"

class Paddle
{
  public:
  float x, y;
  float speed;
  int width;
  int state;
  bool magnetic;
  Environment& environment;
  
  Paddle(Environment &e);
  void draw();
  void left(float dt);
  void right(float dt);
  bool hit(float bx, float by);
  void reflect(Ball& ball);
  float corner(float bx);
};
