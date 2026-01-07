#include "guard.h"
#include <graphics.h>

// ----------------------------------------------------
// Default constructor
// Creates a basic guard at position (0,0) with default size
// ----------------------------------------------------
Guard::Guard()
    : Character(0, 0, 1.5f, 20, 40), // Call base Character constructor
      patrolDistance(0)
{
  direction = 1;    // Start moving right
  startX = 0;       // Save initial X position
  velocityX = 0;    // Horizontal velocity
  velocityY = 0;    // Vertical velocity
  gravity = 900.0f; // Gravity force
  isCaught = false; // Not caught initially

  // Set default facing direction and sprite
  facing = FacingGuard::RIGHT;
  setSprite("Images/Assets/gif/guard-right.gif");
}

// ----------------------------------------------------
// Full constructor
// Initializes guard with position, patrol distance, and size
// ----------------------------------------------------
Guard::Guard(int x, int y, int patrolDist, int w, int h)
    : Character(x, y, 1.5f, w, h) // Base speed = 1.5
{
  patrolDistance = patrolDist; // Patrol range
  direction = 1;               // Start moving right
  startX = x;                  // Store starting X position
  velocityX = 0;               // Horizontal velocity
  velocityY = 0;               // Vertical velocity
  gravity = 900.0f;            // Same as player
  isCaught = false;            // Guard has not caught player

  facing = FacingGuard::RIGHT;                    // Initial facing
  setSprite("Images/Assets/gif/guard-right.gif"); // Load sprite
}

// ----------------------------------------------------
// Update guard position with delta time and collisions
// ----------------------------------------------------
void Guard::updatePositionWithGroundDT(
    const Ground &ground,
    float dt,
    Obstacle *obsList,
    int obsCount)
{
  // --- Horizontal movement ---
  xPosition += direction * speed * 100 * dt; // Move left or right

  // --- Gravity ---
  velocityY += gravity * dt;
  yPosition += velocityY * dt;

  // --- Ground collision ---
  int groundTop = ground.getY();
  if (yPosition + height >= groundTop)
  {
    yPosition = groundTop - height; // Place guard on ground
    velocityY = 0;
  }

  // --- Obstacle collision ---
  for (int i = 0; i < obsCount; i++)
  {
    handleObstacleCollision(obsList[i]);
  }

  // --- Update facing direction based on movement ---
  if (direction == 1)
  {
    facing = FacingGuard::RIGHT;
  }
  else
  {
    facing = FacingGuard::LEFT;
  }
}

// ----------------------------------------------------
// Handle collisions with a single obstacle
// Changes direction if hitting obstacle horizontally
// ----------------------------------------------------
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
    xPosition = obsLeft - width; // Place guard just before obstacle
    direction = -1;              // Reverse direction
    facing = FacingGuard::LEFT;  // Update sprite
  }

  // Hitting obstacle while moving left
  if (direction == -1 &&
      left < obsRight && right > obsRight &&
      bottom > obsTop)
  {
    xPosition = obsRight;        // Place guard just after obstacle
    direction = 1;               // Reverse direction
    facing = FacingGuard::RIGHT; // Update sprite
  }
}

// ----------------------------------------------------
// Check collision between guard and player
// Uses axis-aligned bounding box (AABB)
// ----------------------------------------------------
bool Guard::checkCollisionWithPlayer(const Player &player)
{
  return !(
      player.getX() + player.getWidth() < xPosition ||
      player.getX() > xPosition + width ||
      player.getY() + player.getHeight() < yPosition ||
      player.getY() > yPosition + height);
}

// ----------------------------------------------------
// Getters and setters for "caught" state
// ----------------------------------------------------
bool Guard::getIsCaught() const { return isCaught; }
void Guard::setIsCaught(bool caught) { isCaught = caught; }

// ----------------------------------------------------
// Empty update function (required by base class)
// ----------------------------------------------------
void Guard::updatePosition() {}

// ----------------------------------------------------
// Draw guard using default position
// ----------------------------------------------------
void Guard::drawCharacter()
{
  drawCharacter(xPosition, yPosition);
}

// ----------------------------------------------------
// Draw guard at specific screen coordinates
// ----------------------------------------------------
void Guard::drawCharacter(int screenX, int screenY)
{
  if (useSprite)
  {
    // Draw sprite based on facing direction
    if (facing == FacingGuard::LEFT)
    {
      readimagefile("Images/Assets/gif/guard-left.gif",
                    screenX, screenY,
                    screenX + width, screenY + height);
    }
    else
    {
      readimagefile("Images/Assets/gif/guard-right.gif",
                    screenX, screenY,
                    screenX + width, screenY + height);
    }
  }
  else
  {
    // Fallback: draw green rectangle
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(screenX, screenY, screenX + width, screenY + height);
  }
}

// ----------------------------------------------------
// Reset guard to starting position and default state
// ----------------------------------------------------
void Guard::reset()
{
  xPosition = startX; // Back to starting X
  direction = 1;      // Start moving right
  velocityX = 0;
  velocityY = 0;
  isCaught = false; // Not caught
}

// ----------------------------------------------------
// Destructor
// ----------------------------------------------------
Guard::~Guard() {}