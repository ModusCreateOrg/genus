#ifndef GENUS_THIGHSCORETABLE_H
#define GENUS_THIGHSCORETABLE_H

#include "BTypes.h"
#include "BStore.h"

struct HighScore {
  char name[4];
  TBCD score;
};

struct HighScoreTable {
  HighScore easy[10];
  HighScore moderate[10];
  HighScore hard[10];

  void Reset(TBool aSave = ETrue) {
    for (TInt i = 0; i < 10; i++) {
      strcpy(easy[i].name, "AAA");
      easy[i].score.FromUint32(0);
      strcpy(moderate[i].name, "AAA");
      moderate[i].score.FromUint32(0);
      strcpy(hard[i].name, "AAA");
      hard[i].score.FromUint32(0);
    }

    if (aSave) {
      BStore f("Genus");
      f.Set("high_scores", this, sizeof(HighScoreTable));
    }
  }
};

#endif
