#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <windows.h>
#include <cstdlib>
#include <ctime>

// Link with WinMM library
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib") // Link with WinMM library

#include "Background/background.h"
#include "Ground/ground.h"
#include "Character/Player/player.h"
#include "Character/Guard/guard.h"
#include "Obstacle/Obstacle.h"
#include "Score/Score.h"

#define DEFAULT_BG_COLOR COLOR(70, 180, 255)

// Parameters:
//   screenWidth - the width of the window
//   screenHeight - the height of the window
void drawStartScreen(int screenWidth, int screenHeight);

int main()
{
  // Window config
  const int screenWidth = 1080;
  const int screenHeight = 500;
  initwindow(screenWidth, screenHeight, "Stick J Test v0.1");

  int page = 0;

  bool backgroundMusicEnabled = false;

  if (backgroundMusicEnabled)
  {
    // Play background music on loop
    PlaySound(TEXT("Audio\\stickJ.wav"), NULL, SND_ASYNC | SND_LOOP);
  }

  // Game config
  bool isGameOver = false;

  Score score;

  // Sky background
  Background bg(COLOR(70, 180, 255));

  // World and ground
  const int worldWidth = 5000;
  Ground ground(0, 400, worldWidth, 100, COLOR(255, 165, 0));

  // Camera
  float cameraX = 0;
  int screenCenter = screenWidth / 2;
  float cameraSmooth = 0.15f;

  // Seed random for obstacle and guards generation
  srand(time(NULL));

  // Obstacles
  const int numObstacles = 10;
  Obstacle obstacles[numObstacles];

  // --- Obstacles random generation ---
  for (int i = 0; i < numObstacles; i++)
  {
    bool ok;
    int x;

    do
    {
      ok = true;
      x = 500 + rand() % (worldWidth - 600); // avoid near start and end

      // Ensure obstacles are at least 200px apart
      for (int j = 0; j < i; j++)
      {
        if (abs(x - obstacles[j].getX()) < 200)
        {
          ok = false;
          break;
        }
      }
    } while (!ok);

    int w = 30 + rand() % 40; // width 30–70
    int h = 30 + rand() % 50; // height 30–80
    ObstacleShape type = static_cast<ObstacleShape>(rand() % 3);

    obstacles[i] = Obstacle(x, 360, w, 40, type);
  }

  // Player
  Player stickJ(100, 350, 0.95f, 40, 40);

  // Guards
  const int numGuards = 10;
  Guard guards[numGuards];

  // --- Guards random generation ---
  for (int i = 0; i < numGuards; i++)
  {
    bool ok;
    int x;

    do
    {
      ok = true;
      x = 600 + rand() % (worldWidth - 800); // position

      // Ensure guards are at least 200px apart
      for (int j = 0; j < i; j++)
      {
        if (abs(x - guards[j].getX()) < 200)
        {
          ok = false;
          break;
        }
      }
    } while (!ok);

    int patrol = 150 + rand() % 300; // patrol distance 150–450
    guards[i] = Guard(x, 350, patrol, 40, 40);
  }

  // Delta time system
  DWORD lastTime = GetTickCount();
  float deltaTime = 0.0f;

  while (!(GetAsyncKeyState(VK_SPACE) & 0x8000)) // wait for SPACE
  {
    setactivepage(page);
    setvisualpage(1 - page);
    cleardevice();

    drawStartScreen(screenWidth, screenHeight);

    page = 1 - page;
    delay(2); // small delay to reduce CPU usage
  }

  while (true)
  {
    // --- DELTA TIME ---
    DWORD currentTime = GetTickCount();
    deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    if (deltaTime > 0.05f)
      deltaTime = 0.05f;

    // --- DOUBLE BUFFERING ---
    setactivepage(page);
    setvisualpage(1 - page);
    cleardevice();

    // --- GAME OVER STATE ---
    if (isGameOver)
    {
      // Stop the background music
      if (backgroundMusicEnabled)
      {
        PlaySound(NULL, 0, 0);
      }

      // Draw background
      bg.draw();

      // Draw "GAME OVER" text
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
      setcolor(RED);
      char gameOverText[] = "GAME OVER!";
      int goWidth = textwidth(gameOverText);
      outtextxy((screenWidth - goWidth) / 2, screenHeight / 2 - 100, gameOverText);

      // Draw last score
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
      setcolor(BLACK);
      char scoreText[50];
      sprintf(scoreText, "%d Score...", score.getScore());
      int scoreWidth = textwidth(scoreText);
      outtextxy((screenWidth - scoreWidth) / 2, screenHeight / 2 - 30, scoreText);

      // Draw restart/exit instructions
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
      setcolor(BLACK);
      char instrText[] = "[Press R to restart] or [ESC to exit]";
      int instrWidth = textwidth(instrText);
      outtextxy((screenWidth - instrWidth) / 2, screenHeight / 2 + 30, instrText);

      // Check for restart or exit input
      if (GetAsyncKeyState('R') & 0x8000)
      {
        // Reset everything
        stickJ.setX(100);
        stickJ.setY(350);
        stickJ.resetVelocity();
        for (int i = 0; i < numGuards; i++)
        {
          guards[i].reset();
        }
        for (int i = 0; i < numObstacles; i++)
        {
          obstacles[i].setIsPassed(false);
        }
        score.reset();
        isGameOver = false;

        if (backgroundMusicEnabled)
        {
          // Restart background music on loop
          PlaySound(TEXT("Audio\\stickJ.wav"), NULL, SND_ASYNC | SND_LOOP);
        }
      }
      else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
      {
        break; // exit game
      }

      // Swap buffers and continue
      page = 1 - page;
      delay(2);
      continue;
    }

    // --- GAME LOGIC WHEN NOT GAME OVER ---
    // --- Draw background & ground ---
    bg.updateClouds(1);
    bg.draw();
    ground.draw();

    // --- Draw obstacles ---
    for (int i = 0; i < numObstacles; i++)
      obstacles[i].draw(cameraX);

    // --- PLAYER INPUT ---
    bool left = GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A');
    bool right = GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D');
    bool up = GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState('W');

    if (left && !right)
      stickJ.moveLeft(deltaTime);
    else if (right && !left)
      stickJ.moveRight(deltaTime);
    else
      stickJ.stopMoving(deltaTime);

    if (up)
      stickJ.jump();

    // --- Update player ---
    stickJ.updatePositionWithGroundDT(ground, deltaTime, worldWidth, obstacles, numObstacles);

    // --- Update guards ---
    for (int i = 0; i < numGuards; i++)
    {
      int dx = guards[i].getX() - stickJ.getX();
      if (dx < 500 && dx > -500)
      {
        guards[i].updatePositionWithGroundDT(ground, deltaTime, obstacles, numObstacles);
      }
    }

    // --- Update score for guards passed ---
    for (int i = 0; i < numGuards; i++)
    {
      if (!guards[i].getIsCaught() && stickJ.getX() > guards[i].getX() + guards[i].getWidth())
      {
        score.addGuardScore();       // +10 points
        guards[i].setIsCaught(true); // mark guard as counted
      }
    }

    // --- Update score for obstacles passed ---
    for (int i = 0; i < numObstacles; i++)
    {
      if (!obstacles[i].getIsPassed() &&
          stickJ.getX() > obstacles[i].getX() + obstacles[i].getWidth())
      {
        score.addObstacleScore();       // +5 points
        obstacles[i].setIsPassed(true); // mark obstacle as counted
      }
    }

    // --- Collision detection ---
    for (int i = 0; i < numGuards; i++)
    {
      if (guards[i].checkCollisionWithPlayer(stickJ))
      {
        isGameOver = true;
        break;
      }
    }

    // --- CAMERA SMOOTH FOLLOW ---
    float targetCamX = stickJ.getX() - screenCenter;
    cameraX += (targetCamX - cameraX) * (cameraSmooth * (deltaTime * 60));

    if (cameraX < 0)
      cameraX = 0;
    if (cameraX > worldWidth - screenWidth)
      cameraX = worldWidth - screenWidth;

    // --- DRAW PLAYER ---
    int playerScreenX = stickJ.getX() - cameraX;
    int playerScreenY = stickJ.getY();
    setfillstyle(SOLID_FILL, YELLOW);
    bar(playerScreenX, playerScreenY,
        playerScreenX + stickJ.getWidth(),
        playerScreenY + stickJ.getHeight());

    // --- DRAW GUARDS ---
    for (int i = 0; i < numGuards; i++)
    {
      int guardScreenX = guards[i].getX() - cameraX;
      if (guardScreenX < -100 || guardScreenX > screenWidth + 100)
        continue;

      int guardScreenY = guards[i].getY();
      setfillstyle(SOLID_FILL, GREEN);
      bar(guardScreenX, guardScreenY,
          guardScreenX + guards[i].getWidth(),
          guardScreenY + guards[i].getHeight());
    }

    // --- DRAW SCORE ---
    score.draw(bg, BLACK);

    // --- SWAP BUFFERS ---
    page = 1 - page;

    // --- Small delay for stability ---
    delay(2);
  }

  closegraph();
  return 0;
}

// --- START SCREEN ---
void drawStartScreen(int screenWidth, int screenHeight)
{
  setfillstyle(SOLID_FILL, COLOR(70, 180, 255)); // sky color
  bar(0, 0, screenWidth, screenHeight);

  // Draw course title
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
  setbkcolor(DEFAULT_BG_COLOR);
  setcolor(BLACK);
  char titleText[] = "SECJ1023 PT2 PROJECT";
  int titleWidth = textwidth(titleText);
  outtextxy((screenWidth - titleWidth) / 2, screenHeight / 2 - 100, titleText);

  // Draw game title
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
  setbkcolor(DEFAULT_BG_COLOR);
  setcolor(BLACK);
  char title2Text[] = "STICK J";
  int title2Width = textwidth(title2Text);
  outtextxy((screenWidth - title2Width) / 2, screenHeight / 2 - 60, title2Text);

  // Draw instructions
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
  setbkcolor(DEFAULT_BG_COLOR);
  setcolor(BLACK);
  char instrText[] = "[Press SPACE to start]";
  int instrWidth = textwidth(instrText);
  outtextxy((screenWidth - instrWidth) / 2, screenHeight / 2, instrText);

  // Draw developer credit
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
  setbkcolor(DEFAULT_BG_COLOR);
  setcolor(BLACK);
  char creditText[] = "Developed by: Megat, Syazani, Riva & Nurain";
  int creditWidth = textwidth(creditText);
  outtextxy((screenWidth - creditWidth) / 2, screenHeight / 2 + 200, creditText);
}
