#include "score.h"
#include <graphics.h>
#include <string>
#include <sstream>

Score::Score()
{
  currentScore = 0;
}

void Score::addObstacleScore()
{
  currentScore += 5;
}

void Score::addGuardScore()
{
  currentScore += 10;
}

void Score::reset()
{
  currentScore = 0;
}

int Score::getScore() const
{
  return currentScore;
}

// Draw the score at top-right corner but accepts only variables input
void Score::draw(int bgColor, int txtColor) const
{
  // Draw at top-right corner
  settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
  setcolor(txtColor);
  setbkcolor(bgColor);
  std::ostringstream ss;
  ss << currentScore << " Score...";
  outtextxy(900, 20, (char *)ss.str().c_str());
}

// Draw the score at top-right corner but accepts only class-object and a variable input
void Score::draw(const Background &bg, int txtColor) const
{
  // Draw at top-right corner
  settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
  setcolor(txtColor);
  setbkcolor(bg.getColor());
  std::ostringstream ss;
  ss << currentScore << " Score...";
  outtextxy(900, 20, (char *)ss.str().c_str());
}
