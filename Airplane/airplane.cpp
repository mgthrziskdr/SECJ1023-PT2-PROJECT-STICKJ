#include "airplane.h"
#include <graphics.h>
#include <fstream>

// Default constructor
Airplane::Airplane()
    : xPosition(0), yPosition(0), width(20), height(20), useSprite(false) {}

// Full constructor with optional sprite
Airplane::Airplane(int x, int y, int w, int h)
    : xPosition(x), yPosition(y), width(w), height(h), useSprite(false)
{
  // automatically check file existence
  setSprite("Images/Assets/.bmp");
}

// File check for sprite
void Airplane::setSprite(const char* path)
{
  std::ifstream file(path);
  if (file.good()) {
    spritePath = path;
    useSprite = true;
  } else {
    useSprite = false;
  }
  file.close();
}

void Airplane::disableSprite()
{
  useSprite = false;
  spritePath = "";
}

void Airplane::drawAirplane(float cameraX) const
{
  int screenX = xPosition - (int)cameraX;
  int screenY = yPosition;

  if (useSprite && !spritePath.empty()) {
    readimagefile(spritePath.c_str(), screenX, screenY, screenX + width, screenY + height);
  } else {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(screenX, screenY, screenX + width, screenY + height);

    setcolor(WHITE);
    outtextxy(screenX + 5, screenY + 5, (char*)"PLANE");
  }
}

bool Airplane::checkCollision(int playerX, int playerY, int playerWidth, int playerHeight) const
{
  return !(playerX + playerWidth < xPosition ||
            playerX > xPosition + width ||
            playerY + playerHeight < yPosition ||
            playerY > yPosition + height);
}

// Getters
int Airplane::getX() const { return xPosition; }
int Airplane::getY() const { return yPosition; }
int Airplane::getWidth() const { return width; }
int Airplane::getHeight() const { return height; }
