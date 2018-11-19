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
  TBool  muted;
  TUint  difficulty;
  TFloat music;
  TFloat sfx;

  TOptions();

  void SetDefaults();

  void Save();

  TBool Load();

  const char *DifficultyString(TBool aUpperCase = ETrue) {
    switch (difficulty) {
      case DIFFICULTY_EASY:
        return aUpperCase ? "EASY" : "Easy";
      case DIFFICULTY_INTERMEDIATE:
        return aUpperCase ? "INTERMEDIATE" : "Intermediate";
      case DIFFICULTY_HARD:
        return aUpperCase ? "HARD" : "Hard";
      default:
        Panic("DifficultyString: invalid difficulty %d", difficulty);
    }
    return "Not defined";
  }
};

#endif
