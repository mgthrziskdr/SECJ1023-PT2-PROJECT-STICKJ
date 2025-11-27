#ifndef SCORE_H
#define SCORE_H

#include "../Background/background.h"

class Score
{
  private:
    int currentScore;

  public:
    Score();

    void addObstacleScore(); // +5 points
    void addGuardScore();    // +10 points
    void reset();            // Reset score to 0

    int getScore() const;

    // Draw score at top-right corner
    void draw(int bgColor, int txtColor) const;
    void draw(const Background &bg, int txtColor) const;
};

#endif
