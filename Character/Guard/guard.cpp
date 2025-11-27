#include "guard.h"
#include <graphics.h>

// Constructor
Guard::Guard() : Character(0, 0, 1.5f, 20, 40), patrolDistance(0)
{
  direction = 1;
  startX = 0;
  velocityX = 0;
  velocityY = 0;
  gravity = 900.0f;
  isCaught = false;
}

Guard::Guard(int x, int y, int patrolDist, int w, int h)
    : Character(x, y, 1.5f, w, h) // <-- Guard speed
{
  patrolDistance = patrolDist;
  direction = 1; // Start by moving right
  startX = x;    // Save original position
  velocityX = 0;
  velocityY = 0;
  gravity = 900.0f; // Same gravity as player
  isCaught = false;
}

void Guard::updatePositionWithGroundDT(const Ground &ground, float dt, Obstacle *obsList, int obsCount)
{
  // Move horizontally
  xPosition += direction * speed * 100 * dt;

  // Gravity
  velocityY += gravity * dt;
  yPosition += velocityY * dt;

  // Ground collision
  int groundTop = ground.getY();
  if (yPosition + height >= groundTop)
  {
    yPosition = groundTop - height;
    velocityY = 0;
  }

  // Obstacle collision
  for (int i = 0; i < obsCount; i++)
  {
    handleObstacleCollision(obsList[i]);
  }
}

bool Guard::checkCollisionWithPlayer(const Player &player)
{
  return !(
      player.getX() + player.getWidth() < xPosition ||
      player.getX() > xPosition + width ||
      player.getY() + player.getHeight() < yPosition ||
      player.getY() > yPosition + height);
}

void Guard::handleObstacleCollision(const Obstacle &obs)
{
  int left = xPosition;
  int right = xPosition + width;
  int bottom = yPosition + height;

  int obsLeft = obs.getX();
  int obsRight = obs.getX() + obs.getWidth();
  int obsTop = obs.getY();

  // Hitting obstacle while moving right
  if (direction == 1 &&
      right > obsLeft && left < obsLeft &&
      bottom > obsTop)
  {
    xPosition = obsLeft - width;
    direction = -1;
  }

  // Hitting obstacle while moving left
  if (direction == -1 &&
      left < obsRight && right > obsRight &&
      bottom > obsTop)
  {
    xPosition = obsRight;
    direction = 1;
  }
}

bool Guard::getIsCaught() const { return isCaught; }
void Guard::setIsCaught(bool caught) { isCaught = caught; }

void Guard::reset()
{
  xPosition = startX;
  direction = 1;
  velocityX = 0;
  velocityY = 0;
  isCaught = false;
}
