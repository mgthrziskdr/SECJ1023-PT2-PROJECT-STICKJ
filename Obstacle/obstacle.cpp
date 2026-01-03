#include <graphics.h>
#include "obstacle.h"
#include <fstream>

// ----------------------------------------------------
// Default constructor
// ----------------------------------------------------
Obstacle::Obstacle()
    : xPosition(0),
      yPosition(0),
      width(20),
      height(20),
      shape(ObstacleShape::RECTANGLE),
      isPassed(false),
      useSprite(false)
{
}

// ----------------------------------------------------
// Full constructor
// ----------------------------------------------------
Obstacle::Obstacle(int x, int y, int w, int h, ObstacleShape s, bool passed)
    : xPosition(x),
      yPosition(y),
      width(w),
      height(h),
      shape(s),
      isPassed(passed),
      useSprite(false)
{
    // Set sprite based on obstacle type
    if (shape == ObstacleShape::RECTANGLE)
    {
        // Cactus
        setSprite("Images/Assets/gif/cactus.gif");
    }
    else if (shape == ObstacleShape::CIRCLE)
    {
        // Rock
        setSprite("Images/Assets/gif/rock.gif");
    }
}

// ----------------------------------------------------
// Sprite file checker
// ----------------------------------------------------
void Obstacle::setSprite(const char* path)
{
    std::ifstream file(path);
    if (file.good())
    {
        spritePath = path;
        useSprite = true;
    }
    else
    {
        useSprite = false;
        spritePath = "";
    }
    file.close();
}

void Obstacle::disableSprite()
{
    useSprite = false;
    spritePath = "";
}

// ----------------------------------------------------
// Getters
// ----------------------------------------------------
int Obstacle::getX() const { return xPosition; }
int Obstacle::getY() const { return yPosition; }
int Obstacle::getWidth() const { return width; }
int Obstacle::getHeight() const { return height; }

// ----------------------------------------------------
// Passed flag
// ----------------------------------------------------
bool Obstacle::getIsPassed() const { return isPassed; }
void Obstacle::setIsPassed(bool val) { isPassed = val; }

// ----------------------------------------------------
// Draw obstacle
// ----------------------------------------------------
void Obstacle::drawObstacle(float cameraX) const
{
    int screenX = xPosition - (int)cameraX;
    int screenY = yPosition;

    // Only cactus (rectangle) and rock (circle) use sprite
    if (useSprite &&
        (shape == ObstacleShape::RECTANGLE||
         shape == ObstacleShape::CIRCLE))
    {
        readimagefile(
            spritePath.c_str(),
            screenX,
            screenY,
            screenX + width,
            screenY + height
        );
    }
    else
    {
        // Fallback: draw shapes
        switch (shape)
        {
            case ObstacleShape::RECTANGLE:
            {
                setfillstyle(SOLID_FILL, RED);
                bar(
                    screenX,
                    screenY,
                    screenX + width,
                    screenY + height
                );
                break;
            }

            case ObstacleShape::CIRCLE:
            {
                setfillstyle(SOLID_FILL, BLUE);
                fillellipse(
                    screenX + width / 2,
                    screenY + height / 2,
                    width / 2,
                    height / 2
                );
                break;
            }

        }
    }
}

