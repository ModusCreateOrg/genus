#include "GGameOverProcess.h"

static const TInt16 NEW_SCORE_X = ((320 - (14 * 16)) / 2);
static const TInt16 NEW_SCORE_Y = 50;

static const TInt16 INITIALS_X = ((320 - (NUM_INITIALS * 16)) / 2);
static const TInt16 INITIALS_Y = NEW_SCORE_Y + 24;

static const TInt16 TITLE_Y = 12;

static const TInt16 HIGHSCORES_X = 50;
static const TInt16 HIGHSCORES_Y = TITLE_Y + 32;

GGameOverProcess::GGameOverProcess() : BProcess() {
  gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
  mFont8  = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_8x8);
  mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
  mInitials[NUM_INITIALS] = '\0';
  mHighScoreTable.Load();
  mScoreIndex = mHighScoreTable.IsHighScore(mHighScoreTable.lastScore[gOptions->difficulty]);
  if (mScoreIndex != -1) {
    mState = STATE_INITIALS;
    strcpy(mInitials, mHighScoreTable.lastInitials);
    mInitialsPos = 0;
  } else {
    mState = STATE_HIGHSCORES;
  }
  gSoundPlayer.PlayMusic(ENTERCREDITS_XM);

}

GGameOverProcess::~GGameOverProcess() {
  delete mFont16;
  delete mFont8;
}

TInt GGameOverProcess::CenterText8(const char *s, TInt aY, TInt aColor, TInt aBackground) {
  TInt x = TInt((320 - (strlen(s) * 8)) / 2);
  gDisplay.renderBitmap->DrawStringShadow(ENull, s, mFont8, x, aY, (TUint8)aColor, (TUint8)COLOR_TEXT_SHADOW, (TInt16)aBackground);
  return 8;
}

TInt GGameOverProcess::CenterText16(const char *s, TInt aY, TInt aColor, TInt aBackground) {
  TInt width = aBackground == -1 ? 12 : 16;
  TInt x     = TInt((320 - (strlen(s) * width)) / 2);
  if (aBackground != -1) {
    gDisplay.renderBitmap->DrawStringShadow(ENull, s, mFont16, x, aY, (TUint8)aColor, (TUint8)COLOR_TEXT_SHADOW, (TInt16)aBackground);
  } else {
    gDisplay.renderBitmap->DrawStringShadow(ENull, s, mFont16, x, aY, (TUint8)aColor, (TUint8)COLOR_TEXT_SHADOW, (TInt16)aBackground, -4);
  }
  return 16;
}

TBool GGameOverProcess::HighScoresState() {
  TInt y = TITLE_Y;
  y += CenterText16("HIGH SCORES", y);
  y += TITLE_Y;
  y += CenterText8(gOptions->DifficultyString(), y);
  y += TITLE_Y;
  mHighScoreTable.Render(gOptions->difficulty, 10, HIGHSCORES_X, y, mFont16, COLOR_TEXT, COLOR_TEXT_SHADOW);
  if (gControls.WasPressed(BUTTON_ANY)) {
    gGame->SetState(GAME_STATE_MAIN_MENU);
    gSoundPlayer.SfxMenuCancel();
    return EFalse;
  }
  return ETrue;
}

TBool GGameOverProcess::InitialsState() {
  TInt y = TITLE_Y;
  y += CenterText16("CONGRATULATIONS!", y);
  y += CenterText16("New High Score", y) + 8;
  y += CenterText16("Enter your initials:", y) + 24;
  y += CenterText16(mInitials, y, COLOR_TEXT_BG, COLOR_TEXT);
  gDisplay.renderBitmap->DrawFastHLine(ENull, INITIALS_X + mInitialsPos * 16, y + 4, 16, COLOR_TEXT);
  y += 40;
  y += CenterText8("Up/Down to change letters", y) + 2;
  y += CenterText8("Left/Right to move cursor", y) + 2;
  y += CenterText8("A or B to accept", y);
  if (gControls.WasPressed(JOYUP)) {
    if (mInitials[mInitialsPos] == 'A') {
      mInitials[mInitialsPos] = 'Z';
    } else {
      mInitials[mInitialsPos]--;
    }
    gSoundPlayer.SfxMenuNavUp();
  }
  if (gControls.WasPressed(JOYDOWN | BUTTON_SELECT)) {
    if (mInitials[mInitialsPos] == 'Z') {
      mInitials[mInitialsPos] = 'A';
    } else {
      mInitials[mInitialsPos]++;
    }
    gSoundPlayer.SfxMenuNavDown();
  }
  if (gControls.WasPressed(JOYRIGHT)) {
    mInitialsPos++;
    if (mInitialsPos > NUM_INITIALS - 1) {
      mInitialsPos = 0;
    }
    gSoundPlayer.SfxOptionSelect();
  }
  if (gControls.WasPressed(JOYLEFT)) {
    mInitialsPos--;
    if (mInitialsPos < 0) {
      mInitialsPos = NUM_INITIALS - 1;
    }
    gSoundPlayer.SfxOptionSelect();
  }

  if (gControls.WasPressed(BUTTONA | BUTTONB)) {
    // either A or B pressed
    mHighScoreTable.InsertScore(gOptions->difficulty, mScoreIndex, mInitials, mHighScoreTable.lastScore[gOptions->difficulty]);
    mState = STATE_HIGHSCORES;

    // reset dKeys so next state doesn't react to any keys already pressed
    gControls.dKeys = 0;
    gSoundPlayer.SfxMenuAccept();
  }
  return ETrue;
}

TBool GGameOverProcess::RunBefore() {
  switch (mState) {
    case STATE_INITIALS:
      return InitialsState();
    case STATE_HIGHSCORES:
      return HighScoresState();
    default:
      Panic("GGameOverProcess: invalid mState: %d\n", mState);
  }
  return ETrue;
}

TBool GGameOverProcess::RunAfter() {
  return ETrue;
}
