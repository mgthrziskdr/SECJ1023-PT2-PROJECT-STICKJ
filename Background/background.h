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
    // Setting default value of the object from constructor
    Background(int bgColor = WHITE);

    // Draw the background
    void drawBackground(int OFFSET_Y = 0);

    // Change background color dynamically
    void setColor(int bgColor);

    // Get the set background color
    int getColor() const;

    // Optional: Move clouds for animation
    void updateClouds(int speed = 1);
};

#endif
