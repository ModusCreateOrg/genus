#ifndef GENUS_GHIGHSCORESSTATE_H
#define GENUS_GHIGHSCORESSTATE_H

#include <BGameEngine.h>

struct HighScore {
  char name[4];
  TBCD score;
};

struct HighScoreTable {
  HighScore easy[10];
  HighScore moderate[10];
  HighScore hard[10];

  void Reset() {
    for (TInt i = 0; i < 10; i++) {
      strcpy(easy[i].name, "AAA");
      easy[i].score.FromUint32(0);
      strcpy(moderate[i].name, "AAA");
      moderate[i].score.FromUint32(0);
      strcpy(hard[i].name, "AAA");
      hard[i].score.FromUint32(0);
    }
  }
};

class GHighScoresState : public BGameEngine {
public:
  GHighScoresState();

  virtual ~GHighScoresState();

public:
  void PostRender();

public:
  HighScoreTable mHighScoreTable;
  BFont *mFont;
};

#endif //GENUS_GHIGHSCORESSTATE_H
