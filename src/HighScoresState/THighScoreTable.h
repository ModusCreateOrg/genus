#ifndef GENUS_THIGHSCORETABLE_H
#define GENUS_THIGHSCORETABLE_H

#include "BTypes.h"
#include "BFont.h"

static const TInt NUM_DIFFICULTIES = 3;
static const TInt NUM_INITIALS = 3;
static const TInt SIZE_INITIALS = (NUM_INITIALS+1);
static const TInt NUM_SCORES = 10;
struct THighScore {
  char name[SIZE_INITIALS];
  TBCD score;
};

struct THighScoreTable {
  TInt       version;
  THighScore easy[NUM_SCORES];
  THighScore moderate[NUM_SCORES];
  THighScore hard[NUM_SCORES];
  TBCD       lastScore[NUM_DIFFICULTIES];

public:
  THighScoreTable();

public:
  /**
   * Reset high score table to default values
   */
  void Reset(TBool aSave = ETrue);

  /**
   * Check if score belongs in high score table
   * That is, if the score is higher than any in the table
   *
   * @param aScore
   * @return index in table of score that was beaten, or -1 if not a high score
   */
  TInt IsHighScore(TBCD &aScore);

  /**
   * Insert new high score into high score table
   * @param aIndex
   * @param aInitials
   * @param aScore
   */
  void InsertScore(TInt aDifficulty, TInt aIndex, char *aInitials, TBCD &aScore);

public:
  void Load();

  void Save();

public:
  /**
   * Render High Score table on screen.
   * Returns y just below the rendered table
   *
   * @param aDifficulty
   * @param aCount
   * @param aX
   * @param aY
   * @param aFont
   * @param aColor
   * @return
   */
  TInt Render(TInt aDifficulty, TInt aCount, TInt aX, TInt aY, BFont *aFont, TInt aColor, TInt aShadowColor);

protected:
  THighScore *GetTable(TInt aDifficulty);
};

#endif //GENUS_THIGHSCORETABLE_H
