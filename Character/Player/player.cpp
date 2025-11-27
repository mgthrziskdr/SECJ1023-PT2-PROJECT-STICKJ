#include "player.h"
#include <algorithm>

Player::Player(int x, int y, float spd, int w, int h)
    : Character(x, y, spd, w, h)
{
  velocityX = 0;
  velocityY = 0;
  gravity = 1200.0f;  // pixels/sec^2
  jumpSpeed = 500.0f; // pixels/sec
  isJumping = false;
  acceleration = 2500.0f; // pixels/sec^2
  maxSpeed = 400.0f;      // pixels/sec
  friction = 2000.0f;     // pixels/sec^2
}

int Player::setX(int x) { xPosition = x; return xPosition; }
int Player::setY(int y) { yPosition = y; return yPosition; }

void Player::moveLeft(float dt)
{
  velocityX -= acceleration * dt;
  if (velocityX < -maxSpeed)
    velocityX = -maxSpeed;
}

void Player::moveRight(float dt)
{
  velocityX += acceleration * dt;
  if (velocityX > maxSpeed)
    velocityX = maxSpeed;
}

void Player::stopMoving(float dt)
{
  const float friction = 1500.0f;
  if (velocityX > 0)
  {
    velocityX -= friction * dt;
    if (velocityX < 0)
      velocityX = 0;
  }
  else if (velocityX < 0)
  {
    velocityX += friction * dt;
    if (velocityX > 0)
      velocityX = 0;
  }
}

void Player::resetVelocity() {
  velocityX = 0;
  velocityY = 0;
  isJumping = false;
}

void Player::jump()
{
  if (!isJumping)
  {
    velocityY = -jumpSpeed;
    isJumping = true;
  }
}

void Player::updatePositionWithGroundDT(const Ground &ground, float dt, int worldWidth, Obstacle *obsList, int obsCount)
{
  // --- Apply gravity ---
  velocityY += gravity * dt;

  // --- Update position ---
  xPosition += velocityX * dt;
  yPosition += velocityY * dt;

  // --- Clamp inside world ---
  if (xPosition < 0)
    xPosition = 0;
  if (xPosition + width > worldWidth)
    xPosition = worldWidth - width;

  // --- Obstacle collisions ---
  for (int i = 0; i < obsCount; i++)
  {
    const Obstacle &obs = obsList[i];

    int left = xPosition;
    int right = xPosition + width;
    int bottom = yPosition + height;

    int obsLeft = obs.getX();
    int obsRight = obs.getX() + obs.getWidth();
    int obsTop = obs.getY();
    int obsBottom = obs.getY() + obs.getHeight();

    // Vertical collision (landing on top)
    if (bottom > obsTop && bottom < obsBottom &&
        right > obsLeft && left < obsRight &&
        velocityY >= 0)
    {
      yPosition = obsTop - height;
      velocityY = 0;
      isJumping = false;
    }

    // Horizontal collisions
    if (right > obsLeft && left < obsLeft &&
        bottom > obsTop && yPosition < obsBottom)
    {
      xPosition = obsLeft - width;
      velocityX = 0;
    }

    if (left < obsRight && right > obsRight &&
        bottom > obsTop && yPosition < obsBottom)
    {
      xPosition = obsRight;
      velocityX = 0;
    }
  }

  // --- Ground collision ---
  int groundY = ground.getY();
  if (yPosition + height >= groundY)
  {
    yPosition = groundY - height;
    velocityY = 0;
    isJumping = false;
  }
}
