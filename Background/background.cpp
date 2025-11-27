#include "background.h"
#include <graphics.h>
// Constructor
Background::Background(int bgColor) : color(bgColor)
{
  // Random initial cloud positions
  for (int i = 0; i < CLOUD_COUNT; i++)
  {
    cloudsX[i] = rand() % 800; // screen width
    cloudsY[i] = rand() % 200; // top sky
  }
}

// Draw background + clouds
void Background::draw(int OFFSET_Y)
{
  // Fill the whole screen
  setfillstyle(SOLID_FILL, color);
  bar(0, 0, getmaxx(), getmaxy());

  // Draw clouds
  setfillstyle(SOLID_FILL, WHITE);
  for (int i = 0; i < CLOUD_COUNT; ++i)
  {
    int cx = cloudsX[i];
    int cy = cloudsY[i] + OFFSET_Y;

    // Your cloud drawing shape
    bar(cx, cy, cx + 60, cy + 20);
    bar(cx + 20, cy - 8, cx + 80, cy + 12);
  }
}

// Change background color
void Background::setColor(int bgColor)
{
  color = bgColor;
}

// Move clouds slowly for animation
void Background::updateClouds(int speed)
{
  for (int i = 0; i < CLOUD_COUNT; i++)
  {
    cloudsX[i] += speed;
    if (cloudsX[i] > getmaxx() + 100)
    {
      cloudsX[i] = -100; // wrap around
    }
  }
}