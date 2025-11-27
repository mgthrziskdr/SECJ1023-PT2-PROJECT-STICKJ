#ifndef GUARD_H
#define GUARD_H

#include "../character.h"
#include "../Player/player.h"
#include "../../Ground/ground.h"
#include "../../Obstacle/obstacle.h"

class Guard : public Character {
  private:
    int patrolDistance;
    int direction; // 1 for right, -1 for left
    int startX;

    float velocityX;
    float velocityY;
    float gravity;
    bool isCaught;

  public:
    // Constructor
    Guard();
    Guard(int x, int y, int patrolDist, int w = 20, int h = 40);

    void updatePositionWithGroundDT(const Ground &ground, float dt, Obstacle* obsList, int obsCount);

    // Collision detection with player
    bool checkCollisionWithPlayer(const Player& player);

    void handleObstacleCollision(const Obstacle &obs);

    bool getIsCaught() const;
    void setIsCaught(bool caught);

    // Override base class methods
    void updatePosition() override {};
    void drawCharacter() override {};

    void reset();
};

#endif
