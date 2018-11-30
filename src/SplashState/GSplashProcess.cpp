#include "GSplashProcess.h"

static const char *splash_message1 = "Happy Holidays 2018";
static const char *splash_message2 = "Press a button";

GSplashProcess::GSplashProcess() : BProcess() {
  mColor = 0;
  mState = STATE_FADEIN;
  mFont = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
  mCurrentText = splash_message1;
}

GSplashProcess::~GSplashProcess() {
  delete mFont;
}

TBool GSplashProcess::RunBefore() {
  RenderText();

  return ETrue;
}

TBool GSplashProcess::FadeInState() {
  mColor += (255/30);
  if (mColor > 255) {
    mColor = 255;
  }
  gDisplay.SetColor(COLOR_TEXT, mColor, mColor, mColor);
  if (mColor == 255) {
    mState = STATE_WAIT;
    mTimer = 2 * 30;
  }
  return ETrue;
}
TBool GSplashProcess::FadeOutState() {
  mColor -= (255/30);
  if (mColor < 0) {
    mColor = 0;
  }
  gDisplay.SetColor(COLOR_TEXT, mColor, mColor, mColor);
  if (mColor == 0) {
    mState = STATE_FADEIN;
    mCurrentText = mCurrentText == splash_message1 ? splash_message2 : splash_message1;
  }
  return ETrue;
}
TBool GSplashProcess::WaitState() {
  mTimer--;
  if (mTimer < 0) {
    mState = STATE_FADEOUT;
  }
  return ETrue;
}

void GSplashProcess::RenderText() {
  if (!mCurrentText) {
    return;
  }
  TInt width = TInt(strlen(mCurrentText) * 12);
  TInt x = (320-width)/2;
  gDisplay.renderBitmap->DrawString(ENull, mCurrentText, mFont, x, 200, COLOR_TEXT, -1, -4);
}

TBool GSplashProcess::RunAfter() {
  if (gControls.WasPressed(BUTTON_ANY)) { // } || --mTimer <= 0) {
    gGame->SetState(GAME_STATE_MAIN_MENU);
    return EFalse;
  }
  switch (mState) {
    case STATE_FADEIN:
      return FadeInState();
    case STATE_FADEOUT:
      return FadeOutState();
    case STATE_WAIT:
      return WaitState();
    default:
      Panic("GSplashProcess invalid state");
  }
  return ETrue;
}

