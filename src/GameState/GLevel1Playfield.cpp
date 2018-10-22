//
// Created by mschwartz on 10/21/18.
//

#include "Game.h"
#include "GLevel1Playfield.h"

GLevel1Playfield::GLevel1Playfield(GGameState *aGameEngine) {
  mGameEngine = aGameEngine;
  mTextColor = 0;
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
}

GLevel1Playfield::~GLevel1Playfield()  {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GLevel1Playfield::Animate() {
  mTextColor += 1;
  mTextColor %= 64;
  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);
  // TODO: wrong place
  gSoundPlayer.PlayMusic(SONG1_S3M);

}

void GLevel1Playfield::Render() {
  gDisplay.renderBitmap->CopyPixels(mBackground);
  mGameEngine->mGameBoard.Render();

}

