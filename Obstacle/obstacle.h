#ifndef OBSTACLE_H
#define OBSTACLE_H

enum class ObstacleShape
{
  RECTANGLE,
  CIRCLE,
  TRIANGLE
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

  public:
    Obstacle();
    Obstacle(int x, int y, int w, int h, ObstacleShape s = ObstacleShape::RECTANGLE, bool passed = false);

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    bool getIsPassed() const;
    void setIsPassed(bool val);

    void draw(float cameraX) const;
};

#endif
