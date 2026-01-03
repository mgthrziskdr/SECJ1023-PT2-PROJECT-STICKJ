#ifndef PLAYER_H
#define PLAYER_H

#include "../character.h"
#include "../../Ground/ground.h"
#include "../../Airplane/airplane.h"
#include "../../Obstacle/obstacle.h"

// Player animation / state
enum class PlayerState
{
  IDLE_LEFT,
  IDLE_RIGHT,
  MOVE_LEFT,
  MOVE_RIGHT,
  JUMP_LEFT,
  JUMP_RIGHT
};

class Player : public Character
{
  private:
    PlayerState state;
    bool isJumping;
    float jumpSpeed; // pixels/sec
    float gravity;   // pixels/sec^2
    float velocityX;
    float velocityY;
    float acceleration; // How fast player speeds up
    float maxSpeed;     // Maximum horizontal speed
    float friction;     // How fast player slows down when idle

  public:
    Player(int x, int y, float spd = 100, int w = 20, int h = 40);

    int setX(int x);
    int setY(int y);

    void moveLeft(float dt);
    void moveRight(float dt);
    void stopMoving(float dt);
    void resetVelocity();
    void jump();

    void updatePositionWithGroundDT(const Ground &ground, float dt, int worldWidth, Obstacle *obsList, int obsCount);
    bool checkAirplaneCollision(const Airplane &plane);

    void updatePosition() override;
    void drawCharacter() override;
    void drawCharacter(int screenX, int screenY);

    ~Player();
};

#endif
