// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include <graphics.h>
#include <string>
#include <fstream>

class Character {
  protected:
    int xPosition;
    int yPosition;
    float speed;
    int width;
    int height;

    // --- Sprite stuff ---
    std::string spritePath; // store BMP file path
    bool useSprite;         // if true, draw the sprite

  public:
    // Setting default value of the object from constructor
    Character(int x, int y, float spd = 0.6, int w = 20, int h = 40);

    virtual void updatePosition();

    // Old drawCharacter (for override)
    virtual void drawCharacter();

    // New drawCharacter with screen coordinates
    virtual void drawCharacter(int screenX, int screenY);

    // Sprite controls
    void setSprite(const char* path);
    void disableSprite();

    // Getters
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    bool getUseSprite() const;
};

#endif
