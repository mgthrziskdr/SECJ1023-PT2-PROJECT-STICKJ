#include <graphics.h>
#include "obstacle.h"
#include <fstream>

// ----------------------------------------------------
// Default constructor
// Creates a basic obstacle with default values
// ----------------------------------------------------
Obstacle::Obstacle()
    : xPosition(0),                    // X position in the world
      yPosition(0),                    // Y position in the world
      width(20),                       // Default obstacle width
      height(20),                      // Default obstacle height
      shape(ObstacleShape::RECTANGLE), // Default shape is rectangle
      isPassed(false),                 // Player has not passed it yet
      useSprite(false)                 // No sprite used initially
{
}

// ----------------------------------------------------
// Full constructor
// Used when creating an obstacle with custom values
// ----------------------------------------------------
Obstacle::Obstacle(int x, int y, int w, int h, ObstacleShape s, bool passed)
    : xPosition(x),     // Set X position
      yPosition(y),     // Set Y position
      width(w),         // Set width
      height(h),        // Set height
      shape(s),         // Set obstacle shape
      isPassed(passed), // Set passed state
      useSprite(false)  // Sprite disabled until verified
{
  // Assign sprite depending on obstacle shape
  if (shape == ObstacleShape::RECTANGLE)
  {
    // Rectangle obstacles represent cactus
    setSprite("Images/Assets/gif/cactus.gif");
  }
  else if (shape == ObstacleShape::CIRCLE)
  {
    // Circle obstacles represent rock
    setSprite("Images/Assets/gif/rock.gif");
  }
}

// ----------------------------------------------------
// Sprite file checker
// Checks if sprite file exists before using it
// ----------------------------------------------------
void Obstacle::setSprite(const char *path)
{
  std::ifstream file(path); // Try opening the sprite file

  if (file.good())
  {
    // File exists → enable sprite rendering
    spritePath = path;
    useSprite = true;
  }
  else
  {
    // File does not exist → disable sprite rendering
    useSprite = false;
    spritePath = "";
  }

  file.close(); // Close the file stream
}

// ----------------------------------------------------
// Disable sprite rendering and clear sprite path
// ----------------------------------------------------
void Obstacle::disableSprite()
{
  useSprite = false;
  spritePath = "";
}

// ----------------------------------------------------
// Getter functions
// Return obstacle properties
// ----------------------------------------------------
int Obstacle::getX() const { return xPosition; }
int Obstacle::getY() const { return yPosition; }
int Obstacle::getWidth() const { return width; }
int Obstacle::getHeight() const { return height; }

// ----------------------------------------------------
// Passed flag handling
// Used to check if player already passed this obstacle
// ----------------------------------------------------
bool Obstacle::getIsPassed() const { return isPassed; }
void Obstacle::setIsPassed(bool val) { isPassed = val; }

// ----------------------------------------------------
// Draw obstacle on the screen
// cameraX is used for scrolling effect
// ----------------------------------------------------
void Obstacle::drawObstacle(float cameraX) const
{
  // Convert world position to screen position
  int screenX = xPosition - (int)cameraX;
  int screenY = yPosition;

  // If a sprite is available and the shape supports sprites
  if (useSprite &&
      (shape == ObstacleShape::RECTANGLE ||
       shape == ObstacleShape::CIRCLE))
  {
    // Draw sprite image
    readimagefile(
        spritePath.c_str(),
        screenX,
        screenY,
        screenX + width,
        screenY + height);
  }
  else
  {
    // Fallback drawing using simple shapes
    switch (shape)
    {
      case ObstacleShape::RECTANGLE:
      {
        // Draw rectangle obstacle (cactus placeholder)
        setfillstyle(SOLID_FILL, RED);
        bar(
            screenX,
            screenY,
            screenX + width,
            screenY + height);
        break;
      }

      case ObstacleShape::CIRCLE:
      {
        // Draw circle obstacle (rock placeholder)
        setfillstyle(SOLID_FILL, BLUE);
        fillellipse(
            screenX + width / 2,
            screenY + height / 2,
            width / 2,
            height / 2);
        break;
      }
    }
  }
}

// ----------------------------------------------------
// Destructor
// ----------------------------------------------------
Obstacle::~Obstacle() {}
