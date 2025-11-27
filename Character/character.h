// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include <graphics.h>

class Character {
  protected:
    int xPosition;
    int yPosition;
    float speed;
    int width;
    int height;
    // sprite is optional for now; we will use rectangles first
    // image sprite;

  public:
    Character(int x, int y, float spd = 0.6, int w = 20, int h = 40);

    virtual void updatePosition();

    virtual void drawCharacter();

    // Getters
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
};

#endif
