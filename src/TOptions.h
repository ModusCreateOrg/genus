#ifndef GENUS_TOPTIONS_H
#define GENUS_TOPTIONS_H

#include "BTypes.h"
#include "BStore.h"
#include "Panic.h"

enum {
  DIFFICULTY_EASY,
  DIFFICULTY_INTERMEDIATE,
  DIFFICULTY_HARD
};

struct TOptions {
  TInt   version;
  TBool  muted;
  TUint  difficulty;
  TFloat music;
  TFloat sfx;
  TFloat brightness;

  TOptions();

  void SetDefaults();

  void Reset(TBool aSave = ETrue);

  void Save();

  void Load();

  const char *DifficultyString(TBool aUpperCase = ETrue, TInt aDifficulty = -1) {
    if (aDifficulty == -1) {
      aDifficulty = difficulty;
    }

    switch (aDifficulty) {
      case DIFFICULTY_EASY:
        return aUpperCase ? "EASY" : "Easy";
      case DIFFICULTY_INTERMEDIATE:
        return aUpperCase ? "NORMAL" : "Normal";
      case DIFFICULTY_HARD:
        return aUpperCase ? "HARD" : "Hard";
      default:
        Panic("DifficultyString: invalid difficulty %d", aDifficulty);
    }
    return "Not defined";
  }
};

#endif
