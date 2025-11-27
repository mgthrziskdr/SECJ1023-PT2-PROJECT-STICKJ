#ifndef GROUND_H
#define GROUND_H

#include <graphics.h>
#include <vector>

class Ground {
  private:
    int xPosition;
    int yPosition;
    int width;
    int height;
    int color;

    // Store grain positions
    std::vector<int> grainX;
    std::vector<int> grainY;

  public:
    Ground(int xPos, int yPos, int w, int h, int col = DARKGRAY);

    void draw();

    // Getters for collision
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
};

#endif
