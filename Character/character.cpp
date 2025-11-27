#include "character.h"
#include <graphics.h>

// Constructor (no default parameters here)
Character::Character(int x, int y, float spd, int w, int h)
  : xPosition(x), yPosition(y), speed(spd), width(w), height(h) {}

// Base updatePosition (can be overridden)
void Character::updatePosition() {
    // Default: do nothing
}

// Base drawCharacter (can be overridden)
void Character::drawCharacter() {
    setcolor(WHITE);
    rectangle(xPosition, yPosition, xPosition + width, yPosition + height);
}

// Getters
int Character::getX() const { return xPosition; }
int Character::getY() const { return yPosition; }
int Character::getWidth() const { return width; }
int Character::getHeight() const { return height; }
