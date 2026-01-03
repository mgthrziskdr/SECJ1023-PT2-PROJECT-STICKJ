#include "background.h"
#include <graphics.h>
#include <fstream>
#include <string>

// Constructor
Background::Background(int bgColor) : color(bgColor)
{
  // Random initial cloud positions
  for (int i = 0; i < CLOUD_COUNT; i++)
  {
    cloudsX[i] = rand() % 800; // screen width
    cloudsY[i] = rand() % 200; // top sky
  }

   // automatically check file existence
  setSpriteCloud("Images/Assets/gif/cloud.gif");
}

// File check for sprite
void Background::setSpriteCloud(const char* path)
{
  std::ifstream file(path);
  if (file.good()) {
    spriteCloudPath = path;
    useSpriteCloud = true;
  } else {
    useSpriteCloud = false;
  }
  file.close();
}

void Background::disableSpriteCloud()
{
  useSpriteCloud = false;
  spriteCloudPath = "";
}

void Background::drawBackground(int OFFSET_Y)
{
    // Fill background
    setfillstyle(SOLID_FILL, color);
    bar(0, 0, getmaxx(), getmaxy());

    // Draw clouds
    for (int i = 0; i < CLOUD_COUNT; i++)
    {
        int cx = cloudsX[i];
        int cy = cloudsY[i] + OFFSET_Y;

        if (useSpriteCloud && !spriteCloudPath.empty())
        {
            // Draw cloud image (example size 80x40)
            readimagefile(
                spriteCloudPath.c_str(),
                cx, cy,
                cx + 80, cy + 40
            );
        }
        else
        {
            // Fallback: rectangle clouds
            setfillstyle(SOLID_FILL, WHITE);
            bar(cx, cy, cx + 60, cy + 20);
            bar(cx + 20, cy - 8, cx + 80, cy + 12);
        }
    }
}


// Change background color
void Background::setColor(int bgColor)
{
  color = bgColor;
}

// Returning the background color
int Background::getColor() const { return color; }

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