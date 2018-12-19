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

enum {
  PLAYER_NO_POWERUP,
  PLAYER_COLOR_SWAP,
  PLAYER_MODUS_BOMB
};

struct GameProgress {
  TBool  savedState;
  TUint8 difficulty;
  TUint8 playerType;
  TInt   level;
  TInt   bonusTimer;
  TInt   blocksRemaining;
  TUint8 board[BOARD_ROWS][BOARD_COLS];
  TUint8 playerBlocks[4];
  TUint8 nextBlocks[4];
  TBCD   score;

  GameProgress() {
    savedState = EFalse;
    level = 1;
    bonusTimer = -1;
    blocksRemaining = -1;
    score = TBCD(TUint32(0));
    playerType = PLAYER_NO_POWERUP;
    difficulty = DIFFICULTY_EASY;
    memset(board, 255, sizeof(board));
    memset(playerBlocks, 0, sizeof(playerBlocks));
    memset(nextBlocks, 0, sizeof(nextBlocks));
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

  void ResetGameProgress();

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
