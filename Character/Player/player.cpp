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

  // Set the sprite
  facing = FacingPlayer::RIGHT;
  setSprite("Images/Assets/stickj-right.bmp");
}

int Player::setX(int x)
{
  xPosition = x;
  return xPosition;
}
int Player::setY(int y)
{
  yPosition = y;
  return yPosition;
}

void Player::moveLeft(float dt)
{
  velocityX -= acceleration * dt;
  if (velocityX < -maxSpeed) {
    velocityX = -maxSpeed;
  }

  facing = FacingPlayer::LEFT;
}

void Player::moveRight(float dt)
{
  velocityX += acceleration * dt;
  if (velocityX > maxSpeed) {
    velocityX = maxSpeed;
  }

  facing = FacingPlayer::RIGHT;
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

void Player::resetVelocity()
{
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

// Update position with ground and delta time
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

// Player-Airplane collision
bool Player::checkAirplaneCollision(const Airplane &plane)
{
  return !(xPosition + width < plane.getX() ||
            xPosition > plane.getX() + plane.getWidth() ||
            yPosition + height < plane.getY() ||
            yPosition > plane.getY() + plane.getHeight());
}

void Player::updatePosition() {}

void Player::drawCharacter()
{
  Character::drawCharacter(xPosition, yPosition); // reuse base
}

void Player::drawCharacter(int screenX, int screenY)
{
  if (useSprite) {
    if (facing == FacingPlayer::LEFT) {
      readimagefile("Images/Assets/stickj-left.bmp",
                    screenX, screenY,
                    screenX + width, screenY + height);
    } else {
      readimagefile("Images/Assets/stickj-right.bmp",
                    screenX, screenY,
                    screenX + width, screenY + height);
    }
  } else {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    bar(screenX, screenY, screenX + width, screenY + height);
  }
}