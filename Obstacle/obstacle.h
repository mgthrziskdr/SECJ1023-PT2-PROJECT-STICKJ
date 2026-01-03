#ifndef OBSTACLE_H
#define OBSTACLE_H

// Enum representing different possible obstacle shapes
enum class ObstacleShape
{
  RECTANGLE,
  CIRCLE
};

class Obstacle
{
  private:
    int xPosition;
    int yPosition;
    int width;
    int height;
    ObstacleShape shape;
    bool isPassed;

    std::string spritePath; // store GIF file path
    bool useSprite;         // if true, draw the sprite

  public:
    // Default constructor
    Obstacle();

    // Setting default value of the object from constructor
    Obstacle(int x, int y, int w, int h, ObstacleShape s = ObstacleShape::RECTANGLE, bool passed = false);

     // Sprite controls
    void setSprite(const char* path);
    void disableSprite();

    // Getters for position
    int getX() const;
    int getY() const;

    // Getters for size
    int getWidth() const;
    int getHeight() const;

    // Returns true if the player has already passed this obstacle
    bool getIsPassed() const;

    // Sets whether the obstacle has been passed
    void setIsPassed(bool val);

    // Draws the obstacle on screen, adjusted by camera position
    void drawObstacle(float cameraX) const;


};

#endif
