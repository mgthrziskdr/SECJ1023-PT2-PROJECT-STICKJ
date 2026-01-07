#include "player.h"
#include <algorithm>

// ----------------------------------------------------
// Player constructor
// Initializes player physics, movement values, and state
// ----------------------------------------------------
Player::Player(int x, int y, float spd, int w, int h)
    : Character(x, y, spd, w, h) // Call base class constructor
{
  velocityX = 0;          // Horizontal speed
  velocityY = 0;          // Vertical speed
  gravity = 1200.0f;      // Gravity force (pixels per second^2)
  jumpSpeed = 500.0f;     // Initial jump velocity
  isJumping = false;      // Player starts on ground
  acceleration = 2500.0f; // Acceleration when moving
  maxSpeed = 400.0f;      // Maximum horizontal speed
  friction = 2000.0f;     // Deceleration when stopping

  // Initial animation state
  state = PlayerState::IDLE_RIGHT;
}

// ----------------------------------------------------
// Set X position
// ----------------------------------------------------
int Player::setX(int x)
{
  xPosition = x;
  return xPosition;
}

// ----------------------------------------------------
// Set Y position
// ----------------------------------------------------
int Player::setY(int y)
{
  yPosition = y;
  return yPosition;
}

// ----------------------------------------------------
// Move player left with acceleration
// dt = delta time
// ----------------------------------------------------
void Player::moveLeft(float dt)
{
  // Apply acceleration to the left
  velocityX -= acceleration * dt;

  // Clamp to max speed
  if (velocityX < -maxSpeed)
  {
    velocityX = -maxSpeed;
  }

  // Update animation state
  if (isJumping)
  {
    state = PlayerState::JUMP_LEFT;
  }
  else
  {
    state = PlayerState::MOVE_LEFT;
  }
}

// ----------------------------------------------------
// Move player right with acceleration
// dt = delta time
// ----------------------------------------------------
void Player::moveRight(float dt)
{
  // Apply acceleration to the right
  velocityX += acceleration * dt;

  // Clamp to max speed
  if (velocityX > maxSpeed)
  {
    velocityX = maxSpeed;
  }

  // Update animation state
  if (isJumping)
  {
    state = PlayerState::JUMP_RIGHT;
  }
  else
  {
    state = PlayerState::MOVE_RIGHT;
  }
}

// ----------------------------------------------------
// Stop horizontal movement using friction
// ----------------------------------------------------
void Player::stopMoving(float dt)
{
  const float friction = 1500.0f; // Friction force

  // Slow down gradually
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

  // Switch to idle state if stopped on ground
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

// -------------------------------------------------------
// Reset all velocities (used after collisions or restart)
// -------------------------------------------------------
void Player::resetVelocity()
{
  velocityX = 0;
  velocityY = 0;
  isJumping = false;
}

// -------------------------------------------------------
// Reset player state back to IDLE RIGHT
// -------------------------------------------------------
void Player::resetState()
{
  state = PlayerState::IDLE_RIGHT;
}

// ----------------------------------------------------
// Make the player jump if on ground
// ----------------------------------------------------
void Player::jump()
{
  if (!isJumping)
  {
    velocityY = -jumpSpeed; // Apply upward force
    isJumping = true;

    // Set jump animation direction
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

// ----------------------------------------------------
// Update player position with gravity, ground,
// obstacles, and delta time
// ----------------------------------------------------
void Player::updatePositionWithGroundDT(
    const Ground &ground,
    float dt,
    int worldWidth,
    Obstacle *obsList,
    int obsCount)
{
  // --- Apply gravity ---
  velocityY += gravity * dt;

  // --- Update position using velocity ---
  xPosition += velocityX * dt;
  yPosition += velocityY * dt;

  // --- Keep player inside world bounds ---
  if (xPosition < 0)
  {
    xPosition = 0;
  }

  if (xPosition + width > worldWidth)
  {
    xPosition = worldWidth - width;
  }

  // --- Check collision with obstacles ---
  for (int i = 0; i < obsCount; i++)
  {
    const Obstacle &obs = obsList[i];

    // Player bounding box
    int left = xPosition;
    int right = xPosition + width;
    int bottom = yPosition + height;

    // Obstacle bounding box
    int obsLeft = obs.getX();
    int obsRight = obs.getX() + obs.getWidth();
    int obsTop = obs.getY();
    int obsBottom = obs.getY() + obs.getHeight();

    // Vertical collision (landing on obstacle)
    if (bottom > obsTop && bottom < obsBottom &&
        right > obsLeft && left < obsRight &&
        velocityY >= 0)
    {
      yPosition = obsTop - height;
      velocityY = 0;
      isJumping = false;

      // Switch to idle animation
      if (state == PlayerState::JUMP_LEFT)
      {
        state = PlayerState::IDLE_LEFT;
      }
      else if (state == PlayerState::JUMP_RIGHT)
      {
        state = PlayerState::IDLE_RIGHT;
      }
    }

    // Horizontal collision (left side)
    if (right > obsLeft && left < obsLeft &&
        bottom > obsTop && yPosition < obsBottom)
    {
      xPosition = obsLeft - width;
      velocityX = 0;
    }

    // Horizontal collision (right side)
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

    // Switch to idle animation
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

// ----------------------------------------------------
// Check collision between player and airplane
// Uses AABB collision detection
// ----------------------------------------------------
bool Player::checkAirplaneCollision(const Airplane &plane)
{
  return !(xPosition + width < plane.getX() ||
           xPosition > plane.getX() + plane.getWidth() ||
           yPosition + height < plane.getY() ||
           yPosition > plane.getY() + plane.getHeight());
}

// ----------------------------------------------------
// Unused update function (required by base class)
// ----------------------------------------------------
void Player::updatePosition() {}

// ----------------------------------------------------
// Draw player using base class function
// ----------------------------------------------------
void Player::drawCharacter()
{
  Character::drawCharacter(xPosition, yPosition);
}

// ----------------------------------------------------
// Draw player sprite based on current state
// ----------------------------------------------------
void Player::drawCharacter(int screenX, int screenY)
{
  const char *sprite = nullptr;

  // Choose sprite based on state
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

  // Draw sprite or fallback rectangle
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

// ----------------------------------------------------
// Destructor
// ----------------------------------------------------
Player::~Player() {}