#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../Background/background.h"

class Scoreboard
{
  private:
    int currentScore;

  public:
    // Default constructor
    Scoreboard();

    void addObstacleScore(); // +5 points
    void addGuardScore();    // +10 points
    void reset();            // Reset score to 0

    // Return the current score
    int getScore() const;

    // Draw score at top-right corner
    void drawScoreboard(int bgColor, int txtColor) const;
    void drawScoreboard(const Background &bg, int txtColor) const;

    ~Scoreboard();
};

#endif
