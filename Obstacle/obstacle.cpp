#include <graphics.h>
#include "obstacle.h"

// Default constructor: initializes to a basic 20×20 rectangle at (0,0)
Obstacle::Obstacle()
    : xPosition(0), yPosition(0), width(20), height(20), shape(ObstacleShape::RECTANGLE), isPassed(false) {}

// Full constructor allowing custom position, size, shape, and passed-state
Obstacle::Obstacle(int x, int y, int w, int h, ObstacleShape s, bool passed)
    : xPosition(x), yPosition(y), width(w), height(h), shape(s), isPassed(passed) {}

// Basic getters
int Obstacle::getX() const { return xPosition; }
int Obstacle::getY() const { return yPosition; }
int Obstacle::getWidth() const { return width; }
int Obstacle::getHeight() const { return height; }

// Passed-state flag access
bool Obstacle::getIsPassed() const { return isPassed; }
void Obstacle::setIsPassed(bool val) { isPassed = val; }

void Obstacle::drawObstacle(float cameraX) const
{
  // Convert world coordinates to screen coordinates
  int screenX = xPosition - (int)cameraX;
  int screenY = yPosition;

  switch (shape)
  {
    // Draw a filled rectangle
    case ObstacleShape::RECTANGLE:
    {
      setfillstyle(SOLID_FILL, RED);
      bar(screenX, screenY, screenX + width, screenY + height);
      break;
    }

    // Draw a filled circle (fillellipse uses center + radii)
    case ObstacleShape::CIRCLE:
    {
      setfillstyle(SOLID_FILL, BLUE);
      fillellipse(screenX + width / 2, screenY + height / 2, width / 2, height / 2);
      break;
    }

    // Draw a filled triangle defined by three points
    case ObstacleShape::TRIANGLE:
    {
      setfillstyle(SOLID_FILL, GREEN);

      // Each pair in this array is a vertex: (x1,y1),(x2,y2),(x3,y3)
      int points[6] = {
        screenX, screenY + height,
        screenX + width / 2, screenY,
        screenX + width, screenY + height
      };
      fillpoly(3, points);
      break;
    }
  }
  // setfillstyle(SOLID_FILL, DARKGRAY);
  // bar(sx, yPosition, sx + width, yPosition + height);
}
