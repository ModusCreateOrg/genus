#include "GMainMenuPlayfield.h"

GMainMenuPlayfield::GMainMenuPlayfield() {
  mFont8 = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_8x8);
  mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
  gResourceManager.LoadBitmap(MENU_BACKGROUND_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gResourceManager.LoadBitmap(GENUS_LOGO_BMP, PLAYER_SLOT, IMAGE_ENTIRE);
  mLogo = gResourceManager.GetBitmap(PLAYER_SLOT);
  gDisplay.SetPalette(mBackground);
  mState = 0;
  gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
  gDisplay.SetColor(COLOR_TEXT_BG, 0, 0, 0);
}

GMainMenuPlayfield::~GMainMenuPlayfield() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

TInt GMainMenuPlayfield::CenterText8(const char *s, TInt aY, TInt aColor, TInt aBackground) {
  TInt x = TInt((320 - (strlen(s) * 8)) / 2);
  gDisplay.renderBitmap->DrawString(ENull, s, mFont8, x, aY, aColor, aBackground);
  return 8;
}
TInt GMainMenuPlayfield::CenterText16(const char *s, TInt aY, TInt aColor, TInt aBackground) {
  TInt width = aBackground == -1 ? 12 : 16;
  TInt x     = TInt((320 - (strlen(s) * width)) / 2);
  if (aBackground != -1) {
    gDisplay.renderBitmap->DrawString(ENull, s, mFont16, x, aY, aColor, aBackground);
  } else {
    gDisplay.renderBitmap->DrawString(ENull, s, mFont16, x, aY, aColor, aBackground, -4);
  }
  return 16;
}

void GMainMenuPlayfield::Render() {
  gDisplay.renderBitmap->CopyPixels(mBackground);
  TInt w = mLogo->Width(), h = mLogo->Height();
  TInt x = (SCREEN_WIDTH - w) / 2;
  TInt y = 60 ;

  gDisplay.renderBitmap->DrawBitmapTransparent(
      ENull,                      // ViewPort
      mLogo,                      // bitmap
      TRect(0, 0, w - 1, h - 1),  // src rect
      x, y                        // destination point
      );

  mState++;
}
