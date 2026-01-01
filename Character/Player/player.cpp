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
  state = PlayerState::IDLE_RIGHT;
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
  if (velocityX < -maxSpeed)
  {
    velocityX = -maxSpeed;
  }

  if (isJumping)
  {
    state = PlayerState::JUMP_LEFT;
  }
  else
  {
    state = PlayerState::MOVE_LEFT;
  }
}

void Player::moveRight(float dt)
{
  velocityX += acceleration * dt;
  if (velocityX > maxSpeed)
  {
    velocityX = maxSpeed;
  }

  if (isJumping)
  {
    state = PlayerState::JUMP_RIGHT;
  }
  else
  {
    state = PlayerState::MOVE_RIGHT;
  }
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

  if (!isJumping && velocityX == 0)
  {
    if (state == PlayerState::MOVE_LEFT)
    {
      state = PlayerState::IDLE_LEFT;
    }
    else if (state == PlayerState::MOVE_RIGHT)
    {
      state = PlayerState::IDLE_RIGHT;
    }
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

    if (state == PlayerState::MOVE_LEFT || state == PlayerState::IDLE_LEFT)
    {
      state = PlayerState::JUMP_LEFT;
    }
    else
    {
      state = PlayerState::JUMP_RIGHT;
    }
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
  {
    xPosition = 0;
  }

  if (xPosition + width > worldWidth)
  {
    xPosition = worldWidth - width;
  }

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

      if (state == PlayerState::JUMP_LEFT)
      {
        state = PlayerState::IDLE_LEFT;
      }
      else if (state == PlayerState::JUMP_RIGHT)
      {
        state = PlayerState::IDLE_RIGHT;
      }
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

    if (state == PlayerState::JUMP_LEFT)
    {
      state = PlayerState::IDLE_LEFT;
    }
    else if (state == PlayerState::JUMP_RIGHT)
    {
      state = PlayerState::IDLE_RIGHT;
    }
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
  const char *sprite = nullptr;

  switch (state)
  {
  case PlayerState::MOVE_LEFT:
    sprite = "Images/Assets/gif/stickj-move-left.gif";
    break;

  case PlayerState::MOVE_RIGHT:
    sprite = "Images/Assets/gif/stickj-move-right.gif";
    break;

  case PlayerState::IDLE_LEFT:
    sprite = "Images/Assets/gif/stickj-left.gif";
    break;

  case PlayerState::IDLE_RIGHT:
    sprite = "Images/Assets/gif/stickj-right.gif";
    break;

  case PlayerState::JUMP_LEFT:
    sprite = "Images/Assets/gif/stickj-jump-left.gif";
    break;

  case PlayerState::JUMP_RIGHT:
    sprite = "Images/Assets/gif/stickj-jump-right.gif";
    break;
  }

  if (sprite)
  {
    readimagefile(sprite, screenX, screenY, screenX + width, screenY + height);
  }
  else
  {
    setfillstyle(SOLID_FILL, YELLOW);
    bar(screenX, screenY, screenX + width, screenY + height);
  }
}