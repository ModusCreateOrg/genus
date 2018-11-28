#include "GGameOverHighScoreMessageProcess.h"

static const char *splash_message1 = "Press START button";
static const char *splash_message2 = "";

GGameOverHighScoreMessageProcess::GGameOverHighScoreMessageProcess() : BProcess() {
  mColor = 0;
  mState = STATE_FADEIN;
  mFont = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
  mCurrentText = splash_message1;
}

GGameOverHighScoreMessageProcess::~GGameOverHighScoreMessageProcess() {
  delete mFont;
}

TBool GGameOverHighScoreMessageProcess::RunBefore() {
  RenderText();

  return ETrue;
}

TBool GGameOverHighScoreMessageProcess::FadeInState() {
  mColor += (255 / 30);
  if (mColor > 255) {
    mColor = 255;
  }
  gDisplay.SetColor(COLOR_DIALOG_FG, mColor, mColor, mColor);
  if (mColor == 255) {
    mState = STATE_WAIT;
    mTimer = 30;
  }
  return ETrue;
}
TBool GGameOverHighScoreMessageProcess::FadeOutState() {
  mColor -= (255 / 30);
  if (mColor < 0) {
    mColor = 0;
  }
  gDisplay.SetColor(COLOR_DIALOG_FG, mColor, mColor, mColor);
  if (mColor == 0) {
    mState = STATE_FADEIN;
    mCurrentText = mCurrentText == splash_message1 ? splash_message2 : splash_message1;
  }
  return ETrue;
}
TBool GGameOverHighScoreMessageProcess::WaitState() {
  mTimer--;
  if (mTimer < 0) {
    mState = STATE_FADEOUT;
  }
  return ETrue;
}

void GGameOverHighScoreMessageProcess::RenderText() {
  if (!mCurrentText) {
    return;
  }
  TInt width = TInt(strlen(mCurrentText) * 12);
  TInt x = (SCREEN_WIDTH - width) / 2;
  gDisplay.renderBitmap->DrawString(ENull, mCurrentText, mFont, x, 210, COLOR_DIALOG_FG, -1, -4);
}

TBool GGameOverHighScoreMessageProcess::RunAfter() {
  switch (mState) {
    case STATE_FADEIN:
      return FadeInState();
    case STATE_FADEOUT:
      return FadeOutState();
    case STATE_WAIT:
      return WaitState();
    default:
      Panic("GGameOverHighScoreMessageProcess invalid state");
  }
  return ETrue;
}

