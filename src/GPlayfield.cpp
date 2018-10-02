#include "GPlayfield.h"
#include "GGameEngine.h"
#include <Display.h>
#include "Resources.h"
#include "GResources.h"

GPlayfield::GPlayfield(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  mGameEngine = aGameEngine;
  mDisplay = &gDisplay;
  mFont = new BFont(FONT_SLOT);
//  gResourceManager.LoadBitmap(BKG7_BMP, BKG_SLOT, IMAGE_ENTIRE);
//  mBitmap = gResourceManager.GetBitmap(BKG_SLOT);
//  display.SetPalette(mBitmap);
}

void GPlayfield::Render() {
  BViewPort *vp = mGameEngine->GetViewPort();
  mDisplay->renderBitmap->Clear(197);
  mDisplay->renderBitmap->DrawSprite(vp, BKG_SLOT, 0, 0, 0);
  mDisplay->renderBitmap->DrawString(ENull, mFont, 10,10, "Hello, world");
  mDisplay->renderBitmap->DrawString(vp, mFont, 140,10, "Hello, world");
}
