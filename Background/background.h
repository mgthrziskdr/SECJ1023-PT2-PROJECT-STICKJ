#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>
#include <graphics.h>

#define CLOUD_COUNT 5

class Background {
  private:
    int color;

    // Cloud positions
    int cloudsX[CLOUD_COUNT];
    int cloudsY[CLOUD_COUNT];

    // --- Sprite ---
    std::string spriteCloudPath; // store GIF file path
    bool useSpriteCloud = false;         // if true, draw the sprite

  public:
    // Setting default value of the object from constructor
    Background(int bgColor = WHITE);

    // Draw the background
    void drawBackground(int OFFSET_Y = 0);

    // Change background color dynamically
    void setColor(int bgColor);

    // Get the set background color
    int getColor() const;

    // Sprite controls
    void setSpriteCloud(const char* path);
    void disableSpriteCloud();

    // Optional: Move clouds for animation
    void updateClouds(int speed = 1);

    ~Background();
};

#endif
