#include "ground.h"
#include <graphics.h>
#include <cstdlib> // For rand()

// ----------------------------------------------------
// Constructor
// Initializes ground position, size, color, and sand grains
// ----------------------------------------------------
Ground::Ground(int xPos, int yPos, int w, int h, int col)
    : xPosition(xPos), yPosition(yPos), width(w), height(h), color(col)
{
  // Pre-generate static sand grain positions for visual effect
  // Roughly 10% of the ground width as number of grains
  int numGrains = width * 0.10;

  grainX.reserve(numGrains); // Reserve space to improve performance
  grainY.reserve(numGrains);

  // Randomize positions within ground rectangle
  for (int i = 0; i < numGrains; i++)
  {
    grainX.push_back(xPosition + rand() % width);
    grainY.push_back(yPosition + rand() % height);
  }
}

// ----------------------------------------------------
// Getter functions for collision detection
// ----------------------------------------------------
int Ground::getX() const { return xPosition; }
int Ground::getY() const { return yPosition; }
int Ground::getWidth() const { return width; }
int Ground::getHeight() const { return height; }

// ----------------------------------------------------
// Draw ground rectangle and sand grains
// ----------------------------------------------------
void Ground::drawGround()
{
  // Draw base ground rectangle
  setfillstyle(SOLID_FILL, color);
  bar(xPosition, yPosition, xPosition + width, yPosition + height);

  // Draw individual sand grains as black pixels
  int grainColor = BLACK;
  for (int i = 0; i < grainX.size(); i++)
  {
    putpixel(grainX[i], grainY[i], grainColor);
  }
}

// ----------------------------------------------------
// Destructor
// ----------------------------------------------------
Ground::~Ground() {}