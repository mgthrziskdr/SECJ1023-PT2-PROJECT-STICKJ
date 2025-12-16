#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <string>
#include <fstream>

class Airplane {
  private:
    int xPosition;
    int yPosition;
    int width;
    int height;

    // --- Sprite ---
    std::string spritePath; // store BMP file path
    bool useSprite;         // if true, draw the sprite

  public:
    Airplane();
    Airplane(int x, int y, int w, int h);

    void drawAirplane(float cameraX) const;
    bool checkCollision(int playerX, int playerY, int playerWidth, int playerHeight) const;

    // Sprite controls
    void setSprite(const char* path);
    void disableSprite();

    // Getters
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
};

#endif
