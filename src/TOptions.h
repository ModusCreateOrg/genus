#ifndef GENUS_TOPTIONS_H
#define GENUS_TOPTIONS_H

#include "BTypes.h"
#include "BStore.h"
#include "Panic.h"
#include "GGameBoard.h"

enum {
  DIFFICULTY_EASY,
  DIFFICULTY_INTERMEDIATE,
  DIFFICULTY_HARD
};

struct GameProgress {
  TInt level;
  TInt bonusTimer;
  TInt blocksRemaining;
  TBCD score;
  TUint8 board[BOARD_ROWS][BOARD_COLS];

  GameProgress() {
    level = 1;
    bonusTimer = -1;
    blocksRemaining = -1;
    score = TBCD(TUint32(0));
    memset(board, 255, sizeof(board));
  }
};

struct TOptions {
  TInt   version;
  TBool  muted;
  TUint  difficulty;
  TFloat music;
  TFloat sfx;
  TFloat brightness;
  GameProgress gameProgress;

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
