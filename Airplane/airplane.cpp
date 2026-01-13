#include "airplane.h"
#include <graphics.h> // Graphics functions for drawing
#include <fstream>    // File handling to check sprite existence

// ----------------------------------------------------
// Default constructor
// Creates a small airplane with default values
// ----------------------------------------------------
Airplane::Airplane()
    : xPosition(0),    // X position in world space
      yPosition(0),    // Y position in world space
      width(20),       // Default width
      height(20),      // Default height
      useSprite(false) // Sprite disabled by default
{}

// ----------------------------------------------------
// Full constructor
// Initializes airplane with given position and size
// ----------------------------------------------------
Airplane::Airplane(int x, int y, int w, int h)
    : xPosition(x),    // Set X position
      yPosition(y),    // Set Y position
      width(w),        // Set width
      height(h),       // Set height
      useSprite(false) // Sprite disabled until verified
{
  // Automatically try to load airplane sprite
  setSprite("Images/Assets/gif/half_plane.gif");
}

// ----------------------------------------------------
// Sprite file checker
// Enables sprite only if file exists
// ----------------------------------------------------
void Airplane::setSprite(const char *path)
{
  std::ifstream file(path); // Attempt to open sprite file

  if (file.good())
  {
    spritePath = path; // Store valid sprite path
    useSprite = true;  // Enable sprite drawing
  }
  else
  {
    useSprite = false; // Disable sprite if file not found
  }

  file.close(); // Close file stream
}

// ----------------------------------------------------
// Disable sprite rendering and clear sprite path
// ----------------------------------------------------
void Airplane::disableSprite()
{
  useSprite = false;
  spritePath = "";
}

// ----------------------------------------------------
// Draw airplane on screen
// cameraX is used for horizontal scrolling
// ----------------------------------------------------
void Airplane::drawAirplane(float cameraX) const
{
  // Convert world position to screen position
  int screenX = xPosition - (int)cameraX;
  int screenY = yPosition;

  // Draw sprite if available
  if (useSprite && !spritePath.empty())
  {
    readimagefile(
        spritePath.c_str(),
        screenX,
        screenY,
        screenX + width,
        screenY + height);
  }
  else
  {
    // Fallback drawing using simple graphics
    setbkcolor(COLOR(70, 180, 255));
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(screenX, screenY, screenX + width, screenY + height);

    // Label for clarity
    setcolor(WHITE);
    outtextxy(screenX + 5, screenY + 5, (char *)"PLANE");
  }
}

// ----------------------------------------------------
// Check collision between airplane and player
// Uses AABB (axis-aligned bounding box) collision
// ----------------------------------------------------
bool Airplane::checkCollision(
    int playerX,
    int playerY,
    int playerWidth,
    int playerHeight) const
{
  return !(playerX + playerWidth < xPosition ||
           playerX > xPosition + width ||
           playerY + playerHeight < yPosition ||
           playerY > yPosition + height);
}

// ----------------------------------------------------
// Getter functions
// ----------------------------------------------------
int Airplane::getX() const { return xPosition; }
int Airplane::getY() const { return yPosition; }
int Airplane::getWidth() const { return width; }
int Airplane::getHeight() const { return height; }

// ----------------------------------------------------
// Destructor
// ----------------------------------------------------
Airplane::~Airplane() {}