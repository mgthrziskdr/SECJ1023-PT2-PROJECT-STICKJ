#ifndef GAME_H
#define GAME_H

#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

#include "Background/background.h"
#include "Ground/ground.h"
#include "Character/Player/player.h"
#include "Character/Guard/guard.h"
#include "Obstacle/obstacle.h"
#include "Airplane/airplane.h"
#include "Scoreboard/scoreboard.h"

class Game
{
  private:
    // Window & World
    const int screenWidth = 1080;
    const int screenHeight = 500;
    const int worldWidth = 5000;
    int page;
    float cameraX;
    int screenCenter;
    float cameraSmooth;

    // Game state
    bool isGameOver;
    bool gameWon;

    // Objects
    Background bg;
    Ground ground;
    Scoreboard score;
    Player stickJ;
    Airplane plane;

    // Having no. of 10 obstacles spawning
    static const int numObstacles = 10;
    Obstacle obstacles[numObstacles];

    // Having no. of 10 guards spawning
    static const int numGuards = 10;
    Guard guards[numGuards];

    // Delta time
    DWORD lastTime;
    float deltaTime;

    // Music setting
    bool backgroundMusicState;

    // Private functions
    void drawStartScreen();
    void handleInput();
    void updateGame();
    void renderGame();
    void drawGameOver();
    void resetGame();
    void playBackgroundMusic();
    void stopBackgroundMusic();

  public:
    Game();
    void run(); // main game loop
};

#endif
