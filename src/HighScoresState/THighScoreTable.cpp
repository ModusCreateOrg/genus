#include "THighScoreTable.h"
#include "Game.h"

// bump this each time the struct is edited in IDE/debugger!
static const TInt VERSION = 1;

// TODO: these should reset to a default High Score table with Modus employee initials and fairly low random
// scores
static THighScore default_score_table[NUM_SCORES];

THighScoreTable::THighScoreTable() {
  for (TInt i=0; i<NUM_SCORES; i++) {
    strcpy(default_score_table[i].name, "AAA");
    default_score_table[i].score.mValue = 0;
  }
}

void THighScoreTable::Reset(TBool aSave) {
  version = VERSION;
  for (TInt i = 0; i < NUM_SCORES; i++) {
    strcpy(easy[i].name, default_score_table[i].name);
    easy[i].score.mValue = default_score_table[i].score.mValue;
    strcpy(moderate[i].name, default_score_table[i].name);
    moderate[i].score.mValue = default_score_table[i].score.mValue;
    strcpy(hard[i].name, default_score_table[i].name);
    hard[i].score.mValue = default_score_table[i].score.mValue;
  }

  TBCD lastScoreNulled;
  lastScoreNulled.FromUint32(0);
  for (TInt i = 0; i < NUM_DIFFICULTIES; i++) {
    lastScore[i] = lastScoreNulled;
  }

  if (aSave) {
    Save();
  }
}

void THighScoreTable::Load() {
  BStore *store = new BStore("scores");
  if (!store->Get("high scores", this, sizeof(THighScoreTable))) {
    Reset();
  } else if (version != VERSION) {
    Reset();
  }
  delete store;
}

void THighScoreTable::Save() {
  version = VERSION;
  BStore *store = new BStore("scores");
  store->Set("high scores", this, sizeof(THighScoreTable));
  delete store;
}

THighScore *THighScoreTable::GetTable(TInt aDifficulty) {
  // gOptions stores the index of selected difficulty, not the value
  if (aDifficulty == 2) {
    return hard;
  }
  else if (aDifficulty == 1) {
    return moderate;
  }
  else {
    return easy;
  }
}

TInt THighScoreTable::IsHighScore(TBCD &aScore) {
  Load();
  lastScore[gOptions->difficulty] = aScore;
  Save();
  THighScore *t = GetTable(gOptions->difficulty);
  for (TInt index = 0; index<NUM_SCORES; index++) {
    if (*t[index].score <= *aScore) {
      return index;
    }
  }
  return -1;
}

void THighScoreTable::InsertScore(TInt aDifficulty, TInt aIndex, char *aInitials, TBCD& aScore) {
  THighScore *t = GetTable(aDifficulty);
  THighScore cacheScore1 = t[NUM_SCORES - 1], cacheScore2;

  // move entries, at index, down 1 to make room for new score
  for (TInt i = aIndex; i < NUM_SCORES - 1; i++) {
    cacheScore2 = t[i];
    t[i] = cacheScore1;
    cacheScore1 = cacheScore2;
  }

  t[aIndex].score.mValue = aScore.mValue;
  strcpy(t[aIndex].name, aInitials);
  Save();
}

TInt THighScoreTable::Render(TInt aDifficulty, TInt aCount, TInt aX, TInt aY, BFont *aFont, TInt aColor, TInt aShadowColor) {
  THighScore *t = GetTable(aDifficulty);
  gDisplay.SetColor(COLOR_TEXT, 255,255,255);
  BBitmap   *bm = gDisplay.renderBitmap;
  char      buf[40], sbuf[10];
  TInt      y   = aY, x = aX;

  // Highlight color
  gDisplay.SetColor(COLOR_MENU_TITLE, 255, 92, 93);

  // Check player highscore flag
  TBool checkPlayerHighScore = *lastScore[gOptions->difficulty] > 0;

  for (TInt i   = 0; i < aCount; i++) {
    if (y + aFont->mHeight > 320) {
      break;
    }

    if (i < 9) {
      buf[0] = ' ';
      buf[1] = '1' + i;
      buf[2] = ' ';
      buf[3] = ' ';
      strcpy(&buf[4], t[i].name);
    } else {
      TBCD j;
      j.FromUint32(i+1);
      j.ToString(buf, ENull);
      strcat(buf, "  ");
      strcpy(&buf[strlen(buf)], t[i].name);
    }

    strcat(buf, "  ");
    t[i].score.ToString(sbuf);
    strcat(buf, sbuf);

    if (checkPlayerHighScore && *t[i].score <= *lastScore[gOptions->difficulty]) {
      bm->DrawStringShadow(gViewPort, buf, aFont, x, y, COLOR_MENU_TITLE, aShadowColor, -1, -4);
      checkPlayerHighScore = EFalse;
    } else {
      bm->DrawStringShadow(gViewPort, buf, aFont, x, y, aColor, aShadowColor, -1, -4);
    }

    y += aFont->mHeight;
  }
  return y;
}
