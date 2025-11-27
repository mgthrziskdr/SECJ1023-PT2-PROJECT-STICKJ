#include "ground.h"
#include <graphics.h>
#include <cstdlib>

Ground::Ground(int xPos, int yPos, int w, int h, int col)
  : xPosition(xPos), yPosition(yPos), width(w), height(h), color(col)
{
    // Pre-generate sand grain positions (static forever)
    int numGrains = width * 0.10; // adjust density if needed

    grainX.reserve(numGrains);
    grainY.reserve(numGrains);

    for (int i = 0; i < numGrains; i++) {
      grainX.push_back(xPosition + rand() % width);
      grainY.push_back(yPosition + rand() % height);
    }
}

// Getters for collision
int Ground::getX() const { return xPosition; }
int Ground::getY() const { return yPosition; }
int Ground::getWidth() const { return width; }
int Ground::getHeight() const { return height; }

void Ground::draw() {
  // Base sand color
  setfillstyle(SOLID_FILL, color);
  bar(xPosition, yPosition, xPosition + width, yPosition + height);

  // Draw static sand grains
  int grainColor = BLACK;

  for (int i = 0; i < grainX.size(); i++) {
      putpixel(grainX[i], grainY[i], grainColor);
  }
}