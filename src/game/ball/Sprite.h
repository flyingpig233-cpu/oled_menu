#pragma once

class Sprite
{
  public:
  const unsigned char *data;
  const unsigned char *sprite;
  int sx, sy;
  int cx, cy;
  const unsigned char *points;

  const int LAYER_OPACITY = 7;
  
  Sprite(const unsigned char *data);
  void draw(int x, int y, int layer = 0);
  bool hit(int x, int y, int layer = 1);
};

#include "../../screen.h"

Sprite::Sprite(const unsigned char *data)
{
  this->data = data;
  sx = data[0];
  sy = data[1];
  sprite = data + 2;
  points = sprite + sx * sy;
  cx = points[0];
  cy = points[1];
}

void Sprite::draw(int x, int y, int layer)
{
  for(int j = 0; j < sy; j++)
    for(int i = 0; i < sx; i++)
    {
      int ax = x + i - cx; 
      int ay = y + j - cy;
      int p = sprite[j * sx + i];
      if(p & (1 << LAYER_OPACITY))
        display.drawPixel(ax, ay, WHITE);
    }
}

bool Sprite::hit(int x, int y, int layer)
{
  x += cx;
  y += cy;
  if(x < 0 || y < 0 || x >= sx || y >= sy) return false;
  return sprite[y * sx + x] & (1 << layer) > 0;
}