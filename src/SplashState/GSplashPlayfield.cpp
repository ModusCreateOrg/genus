#include "GSplashPlayfield.h"


GSplashPlayfield::GSplashPlayfield() {
  gResourceManager.LoadBitmap(SPLASH1_BMP, BKG_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(SPLASH_SPRITES_BMP, PLAYER_SLOT, IMAGE_32x32);
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBackground);
  gSoundPlayer.PlayMusic(MAIN_MENU_XM);
}

GSplashPlayfield::~GSplashPlayfield() {
  gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GSplashPlayfield::Render() {
  gDisplay.renderBitmap->CopyPixels(mBackground);
}
