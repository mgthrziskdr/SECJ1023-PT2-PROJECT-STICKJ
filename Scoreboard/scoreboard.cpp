#include "scoreboard.h"
#include <graphics.h>
#include <string>
#include <sstream>

// Default constructor
Scoreboard::Scoreboard()
{
  currentScore = 0;
}

// Add +5 to the score when avoid obstacles
void Scoreboard::addObstacleScore()
{
  currentScore += 5;
}

// Add +10 to the score when avoid guards
void Scoreboard::addGuardScore()
{
  currentScore += 10;
}

// Resets the scorebord
void Scoreboard::reset()
{
  currentScore = 0;
}

// Return the current score
int Scoreboard::getScore() const
{
  return currentScore;
}

// Draw the score at top-right corner but accepts only variables input
void Scoreboard::drawScoreboard(int bgColor, int txtColor) const
{
  // Draw at top-right corner
  settextstyle(BOLD_FONT, HORIZ_DIR, 2);
  setcolor(txtColor);
  setbkcolor(bgColor);
  std::ostringstream ss;
  ss << currentScore << " Score...";
  outtextxy(900, 20, (char *)ss.str().c_str());
}

// Draw the score at top-right corner but accepts only class-object and a variable input
void Scoreboard::drawScoreboard(const Background &bg, int txtColor) const
{
  // Draw at top-right corner
  settextstyle(BOLD_FONT, HORIZ_DIR, 2);
  setcolor(txtColor);
  setbkcolor(bg.getColor());
  std::ostringstream ss;
  ss << currentScore << " Score...";
  outtextxy(900, 20, (char *)ss.str().c_str());
}

// ----------------------------------------------------
// Destructor
// ----------------------------------------------------
Scoreboard::~Scoreboard() {}