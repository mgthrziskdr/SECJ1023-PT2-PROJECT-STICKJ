#include "game.h"
#include <mmsystem.h>
#include <cmath>
#include <fstream>
#include <string>

// Link with WinMM library
#pragma comment(lib, "winmm.lib")

// Color Themes
#define SKY_COLOR COLOR(70, 180, 255)
#define GROUND_COLOR COLOR(180, 148, 96)

// Types of Fonts
/**
  > DEFAULT_FONT        0
  > TRIPLEX_FONT        1
  > SMALL_FONT          2
  > SANS_SERIF_FONT     3
  > GOTHIC_FONT         4
  > SCRIPT_FONT         5
  > SIMPLEX_FONT        6
  > TRIPLEX_SCR_FONT    7
  > COMPLEX_FONT        8
  > EUROPEAN_FONT       9
  > BOLD_FONT           10
*/

// ================================
// --- Game Default Constructor ---
// ================================
Game::Game()
    : page(0),
      cameraX(0.0f),
      screenCenter(screenWidth / 2),
      cameraSmooth(0.15f),
      isGameStarted(false),
      isGameOver(false),
      gameWon(false),
      bg(SKY_COLOR), // Sky Blue
      ground(0, 400, worldWidth, 100, GROUND_COLOR),
      score(),
      stickJ(100, 355, 0.95f, 40, 40),
      plane(worldWidth - 80, 340, 80, 60),
      lastTime(GetTickCount()),
      deltaTime(0.0f),
      backgroundMusicState(false),
      gameVers("2.0")
{
  srand(time(NULL));

  // Generate obstacles randomly
  for (int i = 0; i < numObstacles; i++)
  {
    bool ok;
    int x;

    do
    {
      ok = true;
      x = 500 + rand() % (worldWidth - 600);
      for (int j = 0; j < i; j++)
      {
        if (abs(x - obstacles[j].getX()) < 200)
        {
          ok = false;
          break;
        }
      }
    } while (!ok);

    int w = 30 + rand() % 40;
    int h = 30 + rand() % 50;
    ObstacleShape type = static_cast<ObstacleShape>(rand() % 3);
    obstacles[i] = Obstacle(x, 360, w, 40, type);
  }

  // Generate guards randomly
  for (int i = 0; i < numGuards; i++)
  {
    bool ok;
    int x;
    do
    {
      ok = true;
      x = 600 + rand() % (worldWidth - 800);
      for (int j = 0; j < i; j++)
      {
        if (abs(x - guards[j].getX()) < 200)
        {
          ok = false;
          break;
        }
      }
    } while (!ok);

    int patrol = 150 + rand() % 300;

    // Configuration for guards
    guards[i] = Guard(x, 360, patrol, 40, 40);
  }
}

// ======================
// --- GAME RUN START ---
// ======================
void Game::run()
{
  // Setting game window version
  std::string getVers = "Stick J Test v" + gameVers;
  const char *cgetVers = getVers.c_str();
  initwindow(screenWidth, screenHeight, cgetVers);

  playBackgroundMusic();

  // Wait for SPACE to start
  while (!(GetAsyncKeyState(VK_SPACE) & 0x8000))
  {
    setactivepage(page);
    setvisualpage(1 - page);
    cleardevice();
    drawStartScreen();
    page = 1 - page;
    delay(2);
  }

  // Main game loop
  while (true)
  {
    // --- Delta Time ---
    DWORD currentTime = GetTickCount();
    deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    if (deltaTime > 0.05f)
    {
      deltaTime = 0.05f;
    }

    // --- Double Buffering ---
    setactivepage(page);
    setvisualpage(1 - page);
    cleardevice();

    if (isGameOver || gameWon)
    {
      stopBackgroundMusic();
    }

    if (isGameOver)
    {
      drawGameOver();
      page = 1 - page;
      delay(2);
      continue;
    }

    // --- Handle Input ---
    handleInput();

    // --- Update Game State ---
    updateGame();

    // --- Render Game ---
    renderGame();

    page = 1 - page;
    delay(2);
  }

  closegraph();
}

// --- DRAW START SCREEN ---
void Game::drawStartScreen()
{
  setfillstyle(COMPLEX_FONT, SKY_COLOR);
  bar(0, 0, screenWidth, screenHeight);

  settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);

  // Pre-Render game for start screen
  renderGame();

  // ====================================================================================
  setbkcolor(SKY_COLOR); // ground color
  settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
  setcolor(BLACK);

  setcolor(BLACK);
  char titleText[] = "SECJ1023 PT2 PROJECT";
  outtextxy((screenWidth - textwidth(titleText)) / 2, screenHeight / 2 - 120, titleText);
  // ====================================================================================

  settextstyle(BOLD_FONT, HORIZ_DIR, 5);
  setcolor(BLACK);
  char title2Text[] = "STICK J";
  outtextxy((screenWidth - textwidth(title2Text)) / 2, screenHeight / 2 - 90, title2Text);

  settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
  setcolor(BLACK);
  char instrText[] = "Press";
  outtextxy((screenWidth - textwidth(instrText)) / 2, screenHeight / 2 - 25, instrText);

  int imgWidth = 200;
  int imgHeight = 50;

  int left = (screenWidth - imgWidth) / 2;
  int right = left + imgWidth;
  int bottom = (screenHeight / 2) + 55;
  int top = bottom - imgHeight;

  readimagefile("Images/Assets/gif/space_cap.gif", left, top, right, bottom);

  // ====================================================================================
  // Set different background font color
  setbkcolor(GROUND_COLOR); // ground color
  settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
  setcolor(BLACK);

  setcolor(BLACK);
  char creditText[] = "Developed by: Megat, Syazani, Riva & Nurain";
  outtextxy((screenWidth - textwidth(creditText)) / 2, screenHeight / 2 + 190, creditText);
  // ====================================================================================
}

// =============
// --- INPUT ---
// =============
void Game::handleInput()
{
  bool left = GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A');
  bool right = GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D');
  bool up = GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState('W');

  if (left && !right)
  {
    stickJ.moveLeft(deltaTime);
  }
  else if (right && !left)
  {
    stickJ.moveRight(deltaTime);
  }
  else
  {
    stickJ.stopMoving(deltaTime);
  }

  if (up)
  {
    stickJ.jump();
  }

  if (GetAsyncKeyState('M') & 0x1)
  {
    backgroundMusicState = !backgroundMusicState;

    if (backgroundMusicState)
    {
      playBackgroundMusic();
    }
    else
    {
      stopBackgroundMusic();
    }
  }
}

// ======================================
// --- UPDATE GAME STATE / GAME LOGIC ---
// ======================================
void Game::updateGame()
{
  stickJ.updatePositionWithGroundDT(ground, deltaTime, worldWidth, obstacles, numObstacles);

  for (int i = 0; i < numGuards; i++)
  {
    int dx = guards[i].getX() - stickJ.getX();
    if (dx < 500 && dx > -500)
    {
      guards[i].updatePositionWithGroundDT(ground, deltaTime, obstacles, numObstacles);
    }
  }

  // Check for collisions
  for (int i = 0; i < numGuards; i++)
  {
    if (guards[i].checkCollisionWithPlayer(stickJ))
    {
      isGameOver = true;
      return;
    }
  }

  // Update scores
  for (int i = 0; i < numGuards; i++)
  {
    if (!guards[i].getIsCaught() && stickJ.getX() > guards[i].getX() + guards[i].getWidth())
    {
      score.addGuardScore();
      guards[i].setIsCaught(true);
    }
  }

  for (int i = 0; i < numObstacles; i++)
  {
    if (!obstacles[i].getIsPassed() && stickJ.getX() > obstacles[i].getX() + obstacles[i].getWidth())
    {
      score.addObstacleScore();
      obstacles[i].setIsPassed(true);
    }
  }

  // Check if player reaches airplane
  if (stickJ.checkAirplaneCollision(plane))
  {
    isGameOver = true;
    gameWon = true;
  }

  // Camera follow
  float targetCamX = stickJ.getX() - screenCenter;
  cameraX += (targetCamX - cameraX) * (cameraSmooth * (deltaTime * 60));
  if (cameraX < 0)
  {
    cameraX = 0;
  }

  if (cameraX > worldWidth - screenWidth)
  {
    cameraX = worldWidth - screenWidth;
  }
}

// ===================
// --- RENDER GAME ---
// ===================
void Game::renderGame()
{
  bg.updateClouds(1);
  bg.drawBackground();
  ground.drawGround();
  plane.drawAirplane(cameraX);

  for (int i = 0; i < numObstacles; i++)
  {
    // Draw Obstacles
    obstacles[i].drawObstacle(cameraX);
  }

  // Draw Player
  stickJ.drawCharacter(stickJ.getX() - cameraX, stickJ.getY());

  for (int i = 0; i < numGuards; i++)
  {
    int guardScreenX = guards[i].getX() - cameraX;
    if (guardScreenX < -100 || guardScreenX > screenWidth + 100)
    {
      continue;
    }

    // Draw Guards
    guards[i].drawCharacter(guardScreenX, guards[i].getY());
  }

  // Draw Scoreboard
  score.drawScoreboard(bg, BLACK);

  // Draw Game Version
  drawVersion();
}

// ========================
// --- BACKGROUND MUSIC ---
// ========================
void Game::playBackgroundMusic()
{
  if (backgroundMusicState)
  {
    PlaySound(TEXT("Audio\\stickJ.wav"),
              NULL,
              SND_ASYNC | SND_LOOP);
  }
}

// ============================
// -- STOP BACKGROUND MUSIC ---
// ============================
void Game::stopBackgroundMusic()
{
  PlaySound(NULL, NULL, 0); // stops all sounds
}

// ==============================
// --- GAME OVER / WIN SCREEN ---
// ==============================
void Game::drawGameOver()
{
  bg.drawBackground();

  settextstyle(BOLD_FONT, HORIZ_DIR, 5);
  if (gameWon)
  {
    setcolor(GREEN);
  }
  else
  {
    setcolor(RED);
  }

  char text[20]; // make sure the array is big enough

  if (gameWon)
  {
    strcpy(text, "WIN!");
  }
  else
  {
    strcpy(text, "GAME OVER!");
  }

  outtextxy((screenWidth - textwidth(text)) / 2, screenHeight / 2 - 100, text);

  setbkcolor(SKY_COLOR);
  settextstyle(BOLD_FONT, HORIZ_DIR, 3);
  setcolor(BLACK);
  char scoreText[50];
  sprintf(scoreText, "%d Score...", score.getScore());
  outtextxy((screenWidth - textwidth(scoreText)) / 2, screenHeight / 2 - 30, scoreText);

  settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
  setcolor(BLACK);
  char instrText[] = "[Press R to restart] or [ESC to exit]";
  outtextxy((screenWidth - textwidth(instrText)) / 2, screenHeight / 2 + 30, instrText);

  if (GetAsyncKeyState('R') & 0x8000)
  {
    resetGame();
  }
  else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
  {
    exit(0);
  }
}

// ==================
// --- RESET GAME ---
// ==================
void Game::resetGame()
{
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
  gameWon = false;
  playBackgroundMusic();
}

// =====================================
// ---- GAME VERSION (bottom-right) ----
// =====================================
void Game::drawVersion()
{
  int textH = 15;
  int x = screenWidth - 250;
  int y = screenHeight - textH - 10;

  setbkcolor(GROUND_COLOR);
  settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
  setcolor(BLACK);

  std::string temp = "Build v" + gameVers + " \xA9 2025/2026";

  char versionText[80];
  strcpy(versionText, temp.c_str()); // copy to mutable array

  outtextxy(x, y, versionText);
}
