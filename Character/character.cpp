#include "character.h"
#include <graphics.h>
#include <string>
#include <fstream>

// Constructor (no default parameters here)
Character::Character(int x, int y, float spd, int w, int h)
    : xPosition(x), yPosition(y), speed(spd), width(w), height(h), useSprite(false) {
      spritePath = "";
    }

// Applying an image... to the sprite of the character
void Character::setSprite(const char* path)
{
  std::ifstream file(path);

  if (file.good()) {
    spritePath = path;
    useSprite = true;
    
    // --- Visual OK message ---
    // settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    // setcolor(GREEN);
    // outtextxy(50, 50, (char*)"OK: Sprite BMP found!");
    // delay(2000);  // pause 2 seconds so you can see it
  } else {
    useSprite = false;

    // --- Visual error message ---
    // setcolor(RED);
    // settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    // outtextxy(50, 50, (char*)"Error: Sprite BMP not found!");
    // delay(2000);  // pause 2 seconds so you can see it
  }
  file.close();
}

void Character::disableSprite()
{
  useSprite = false;
}

// Base updatePosition (can be overridden)
void Character::updatePosition()
{
  // Default: do nothing
}

// Base drawCharacter (can be overridden)
void Character::drawCharacter()
{
  if (useSprite) {
    readimagefile(
      spritePath.c_str(),
      xPosition,
      yPosition,
      xPosition + width,
      yPosition + height
    );
  } else {
    setcolor(WHITE);
    rectangle(xPosition, yPosition, xPosition + width, yPosition + height);
  }
}

// Base drawCharacter with parameters (can be overridden)
void Character::drawCharacter(int screenX, int screenY)
{
  if (useSprite) {
    readimagefile(
      spritePath.c_str(),
      xPosition,
      yPosition,
      xPosition + width,
      yPosition + height
    );
  } else {
    setcolor(WHITE);
    rectangle(xPosition, yPosition, xPosition + width, yPosition + height);
  }
}

// Getters
int Character::getX() const { return xPosition; }
int Character::getY() const { return yPosition; }
int Character::getWidth() const { return width; }
int Character::getHeight() const { return height; }
bool Character::getUseSprite() const { return useSprite; }
