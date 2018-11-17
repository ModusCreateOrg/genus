#include "THighScoreTable.h"
#include "Game.h"

// bump this each time the struct is edited!
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

void THighScoreTable::Reset() {
  version = VERSION;
  for (TInt i = 0; i < NUM_SCORES; i++) {
    strcpy(easy[i].name, default_score_table[i].name);
    easy[i].score.mValue = default_score_table[i].score.mValue;
    strcpy(moderate[i].name, default_score_table[i].name);
    moderate[i].score.mValue = default_score_table[i].score.mValue;
    strcpy(hard[i].name, default_score_table[i].name);
    hard[i].score.mValue = default_score_table[i].score.mValue;
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
  BStore *store = new BStore("scores");
  store->Set("high scores", this, sizeof(THighScoreTable));
  delete store;
}

THighScore *THighScoreTable::GetTable(TInt aDifficulty) {
  if (aDifficulty == 3) {
    return hard;
  }
  else if (aDifficulty == 2) {
    return moderate;
  }
  else {
    return easy;
  }
}

TInt THighScoreTable::IsHighScore(TBCD &aScore) {
  Load();
  lastScore = aScore;
  Save();
  THighScore *t = GetTable(gOptions->difficulty);
  for (TInt index = 0; index<NUM_SCORES; index++) {
    if (*t->score <= *aScore) {
      return index;
    }
  }
  return -1;
}

void THighScoreTable::InsertScore(TInt aDifficulty, TInt aIndex, char *aInitials, TBCD& aScore) {
  THighScore *t = GetTable(aDifficulty);

  // move entries, at index, down 1 to make room for new score
  for (TInt i = aIndex; i<NUM_SCORES-1; i++) {
    t[i+1].score.mValue = t[i].score.mValue;
    strcpy(t[i+1].name, t[i].name);
  }
  t[aIndex].score.mValue = aScore.mValue;
  strcpy(t[aIndex].name, aInitials);
}

TInt THighScoreTable::Render(TInt aDifficulty, TInt aCount, TInt aX, TInt aY, BFont *aFont, TInt aColor) {
  THighScore *t = GetTable(aDifficulty);
  gDisplay.SetColor(COLOR_TEXT, 255,255,255);
  BBitmap   *bm = gDisplay.renderBitmap;
  char      buf[40], sbuf[10];
  TInt      y   = aY, x = aX;
  for (TInt i   = 0; i < aCount; i++) {
    if (y + aFont->mHeight > 320) {
      break;
    }
    strcpy(&buf[0], t[i].name);
    strcat(buf, "  ");
    t[i].score.ToString(sbuf);
    strcat(buf, sbuf);
    bm->DrawString(gViewPort, buf, aFont, x, y, aColor);
    y += aFont->mHeight;
  }
  return y;
}
