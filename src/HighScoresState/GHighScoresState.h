#ifndef GENUS_GHIGHSCORESSTATE_H
#define GENUS_GHIGHSCORESSTATE_H

#include <BGameEngine.h>
#include "THighScoreTable.h"

class GHighScoresState : public BGameEngine {
public:
  GHighScoresState();

  virtual ~GHighScoresState();

public:
  void PostRender();

public:
  THighScoreTable mHighScoreTable;
  BFont *mFont;
};

#endif //GENUS_GHIGHSCORESSTATE_H
