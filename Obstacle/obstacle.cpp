#include <graphics.h>
#include "Obstacle.h"

Obstacle::Obstacle()
    : xPosition(0), yPosition(0), width(20), height(20), shape(ObstacleShape::RECTANGLE), isPassed(false) {}

Obstacle::Obstacle(int x, int y, int w, int h, ObstacleShape s, bool passed)
    : xPosition(x), yPosition(y), width(w), height(h), shape(s), isPassed(passed) {}

int Obstacle::getX() const { return xPosition; }
int Obstacle::getY() const { return yPosition; }
int Obstacle::getWidth() const { return width; }
int Obstacle::getHeight() const { return height; }

bool Obstacle::getIsPassed() const { return isPassed; }
void Obstacle::setIsPassed(bool val) { isPassed = val; }

void Obstacle::draw(float cameraX) const
{
  int screenX = xPosition - (int)cameraX;
  int screenY = yPosition;

  switch (shape)
  {
    case ObstacleShape::RECTANGLE:
    {
      setfillstyle(SOLID_FILL, RED);
      bar(screenX, screenY, screenX + width, screenY + height);
      break;
    }

    case ObstacleShape::CIRCLE:
    {
      setfillstyle(SOLID_FILL, BLUE);
      fillellipse(screenX + width / 2, screenY + height / 2, width / 2, height / 2);
      break;
    }

    case ObstacleShape::TRIANGLE:
    {
      setfillstyle(SOLID_FILL, GREEN);
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
