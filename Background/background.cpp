#include "background.h"
#include <graphics.h>
#include <fstream>
#include <string>

// ----------------------------------------------------
// Constructor
// Initializes background color and random cloud positions
// ----------------------------------------------------
Background::Background(int bgColor) 
    : color(bgColor)
{
  // Random initial cloud positions
  for (int i = 0; i < CLOUD_COUNT; i++)
  {
    cloudsX[i] = rand() % 800; // Random X within screen width
    cloudsY[i] = rand() % 200; // Random Y in top part of sky
  }

  // Automatically try to load cloud sprite
  setSpriteCloud("Images/Assets/gif/cloud.gif");
}

// ----------------------------------------------------
// Set cloud sprite path if file exists
// Enables sprite rendering if found
// ----------------------------------------------------
void Background::setSpriteCloud(const char *path)
{
  std::ifstream file(path);  // Open file to check existence

  if (file.good())
  {
    spriteCloudPath = path;  // Store valid sprite path
    useSpriteCloud = true;   // Enable sprite drawing
  }
  else
  {
    useSpriteCloud = false;  // Disable if file not found
  }

  file.close();
}

// ----------------------------------------------------
// Disable cloud sprite and clear path
// ----------------------------------------------------
void Background::disableSpriteCloud()
{
  useSpriteCloud = false;
  spriteCloudPath = "";
}

// ----------------------------------------------------
// Draw background and clouds
// OFFSET_Y can be used to shift clouds vertically
// ----------------------------------------------------
void Background::drawBackground(int OFFSET_Y)
{
  // Fill entire screen with background color
  setfillstyle(SOLID_FILL, color);
  bar(0, 0, getmaxx(), getmaxy());

  // Draw each cloud
  for (int i = 0; i < CLOUD_COUNT; i++)
  {
    int cx = cloudsX[i];       // Cloud X
    int cy = cloudsY[i] + OFFSET_Y; // Cloud Y

    if (useSpriteCloud && !spriteCloudPath.empty())
    {
      // Draw cloud sprite (example size 80x40)
      readimagefile(spriteCloudPath.c_str(), cx, cy, cx + 80, cy + 40);
    }
    else
    {
      // Fallback: simple rectangle clouds
      setfillstyle(SOLID_FILL, WHITE);
      bar(cx, cy, cx + 60, cy + 20);          // Main rectangle
      bar(cx + 20, cy - 8, cx + 80, cy + 12); // Upper offset for fluff
    }
  }
}

// ----------------------------------------------------
// Change background color
// ----------------------------------------------------
void Background::setColor(int bgColor)
{
  color = bgColor;
}

// ----------------------------------------------------
// Return current background color
// ----------------------------------------------------
int Background::getColor() const 
{ 
  return color; 
}

// ----------------------------------------------------
// Move clouds horizontally for simple animation
// Wrap around when clouds exit screen
// ----------------------------------------------------
void Background::updateClouds(int speed)
{
  for (int i = 0; i < CLOUD_COUNT; i++)
  {
    cloudsX[i] += speed;             // Move cloud by speed

    // Wrap around screen when off the right edge
    if (cloudsX[i] > getmaxx() + 100)
    {
      cloudsX[i] = -100;             // Reappear on left
    }
  }
}

// ----------------------------------------------------
// Destructor
// ----------------------------------------------------
Background::~Background() {}