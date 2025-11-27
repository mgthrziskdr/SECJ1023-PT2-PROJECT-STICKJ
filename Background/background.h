#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <graphics.h>

#define CLOUD_COUNT 5

class Background {
  private:
    int color;

    // Cloud positions
    int cloudsX[CLOUD_COUNT];
    int cloudsY[CLOUD_COUNT];

  public:
    // Constructor: default white background
    Background(int bgColor = WHITE);

    // Draw the background
    void draw(int OFFSET_Y = 0);

    // Change background color dynamically
    void setColor(int bgColor);

    // Optional: Move clouds for animation
    void updateClouds(int speed = 1);

    int getColor() const { return color; }
};

#endif
