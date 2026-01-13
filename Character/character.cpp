#include "character.h"
#include <graphics.h>
#include <string>
#include <fstream>

// ----------------------------------------------------
// Constructor
// Initializes basic character attributes
// ----------------------------------------------------
Character::Character(int x, int y, float spd, int w, int h)
    : xPosition(x), yPosition(y), speed(spd), width(w), height(h), useSprite(false)
{
  spritePath = ""; // No sprite initially
}

// ----------------------------------------------------
// Set a sprite image for the character
// Enables sprite only if the file exists
// ----------------------------------------------------
void Character::setSprite(const char *path)
{
  std::ifstream file(path); // Open file to check existence

  if (file.good())
  {
    spritePath = path; // Save valid path
    useSprite = true;

    // --- Visual OK message (optional debug) ---
    // settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    // setcolor(GREEN);
    // outtextxy(50, 50, (char*)"OK: Sprite BMP found!");
    // delay(2000);  // pause 2 seconds so you can see it
  }
  else
  {
    useSprite = false;

    // --- Visual error message (optional debug) ---
    // setcolor(RED);
    // settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    // outtextxy(50, 50, (char*)"Error: Sprite BMP not found!");
    // delay(2000);  // pause 2 seconds so you can see it
  }

  file.close();
}

// ----------------------------------------------------
// Disable sprite rendering
// ----------------------------------------------------
void Character::disableSprite()
{
  useSprite = false;
}

// ----------------------------------------------------
// Base updatePosition function
// Can be overridden by derived classes
// ----------------------------------------------------
void Character::updatePosition()
{
  // Default: do nothing
}

// ----------------------------------------------------
// Draw character at its current position
// Uses sprite if available, else draws a rectangle
// ----------------------------------------------------
void Character::drawCharacter()
{
  if (useSprite)
  {
    readimagefile(
        spritePath.c_str(),
        xPosition,
        yPosition,
        xPosition + width,
        yPosition + height);
  }
  else
  {
    setcolor(WHITE);
    rectangle(xPosition, yPosition, xPosition + width, yPosition + height);
  }
}

// ----------------------------------------------------
// Draw character at specific screen coordinates
// Can be overridden by derived classes
// ----------------------------------------------------
void Character::drawCharacter(int screenX, int screenY)
{
  if (useSprite)
  {
    readimagefile(
        spritePath.c_str(),
        xPosition,
        yPosition,
        xPosition + width,
        yPosition + height);
  }
  else
  {
    setcolor(WHITE);
    rectangle(xPosition, yPosition, xPosition + width, yPosition + height);
  }
}

// ----------------------------------------------------
// Getter functions
// ----------------------------------------------------
int Character::getX() const { return xPosition; }
int Character::getY() const { return yPosition; }
int Character::getWidth() const { return width; }
int Character::getHeight() const { return height; }
bool Character::getUseSprite() const { return useSprite; }
