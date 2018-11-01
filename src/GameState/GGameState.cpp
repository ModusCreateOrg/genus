#include "Game.h"
#include "GGameBoard.h"
#include "GLevel1Playfield.h"
#include "GLevel2Playfield.h"
//#include "GLevel3Playfield.h"
#include "GGameProcess.h"

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

GGameState::GGameState() : BGameEngine(gViewPort) {
  mLevel       = 1;
  mGameOver    = EFalse;
  mPlayfield   = ENull;
  mGameProcess = ENull;
  mBonusTime   = 15 * 30;   // TODO: difficulty, etc.
  mBonusTimer  = -1;

  gResourceManager.LoadBitmap(CHARSET_8X8_BMP, FONT_8x8_SLOT, IMAGE_8x8);
  gResourceManager.LoadBitmap(CHARSET_16X16_BMP, FONT_16x16_SLOT, IMAGE_16x16);
  mFont = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);

  LoadLevel();

}

GGameState::~GGameState() {
  delete mFont;
  // TODO: check these should be done in the BPlayfield children
  //  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  //  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
  //  gResourceManager.ReleaseBitmapSlot(BKG3_SLOT);
  //  gResourceManager.ReleaseBitmapSlot(BKG4_SLOT);
  //  gResourceManager.ReleaseBitmapSlot(BKG5_SLOT);
  //  gResourceManager.ReleaseBitmapSlot(BKG6_SLOT);
  //  gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
}

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

void GGameState::PreRender() {
  if (mBonusTimer >= 0) {
    mBonusTimer--;
    if (mBonusTimer < 0) {
      printf("remove blocks\b");
      mGameProcess->RemoveBlocks();
    }
  }
}

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

void GGameState::LoadLevel() {
  switch (mLevel) {
    case 1:
    default:
      mBlocksThisLevel = 100;

      delete mPlayfield;
      mPlayfield = new GLevel1Playfield(this);

      gSoundPlayer.PlayMusic(SONG1_S3M);
      break;
    case 2:
      mBlocksThisLevel = 100;

      delete mPlayfield;
      mPlayfield = new GLevel2Playfield(this);
      // TODO: Jay needs to implement this
//      gSoundPlayer.PlayMusic(SONG2_S3M);
      gSoundPlayer.PlayMusic(SONG1_S3M);    // TODO: Jay needs to remove this hack..  Hack for now so we have some music
      break;
  }

  // TODO: Jay we're assuming the playfield we just created loads the player slot
  // each level might have different blocks, for example
  BBitmap *playerBitmap = gResourceManager.GetBitmap(PLAYER_SLOT);

  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  // TODO: Jay - this logic can be moved to BPlayfield children
  // this assumes BKG_SLOT bmp has the correct palette for the display
  gDisplay.SetPalette(mBackground, 0, 128);
  gDisplay.SetPalette(playerBitmap, 128, 128);
  gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
  gDisplay.SetColor(COLOR_TEXT_SHADOW, 0, 0, 0);


  if (mGameProcess) {
    mGameProcess->Remove();
    delete mGameProcess;
    mGameProcess = ENull;
  }
  mGameProcess = new GGameProcess(this);
  AddProcess((BProcess *) mGameProcess);

  mBlocksRemaining = mBlocksThisLevel;
  mGameBoard.Clear();
}

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

void GGameState::RenderTimer() {
  BBitmap *bm = gDisplay.renderBitmap;
  if (mBonusTimer >= 0 || true) {

    bm->DrawStringShadow(ENull, "Time", mFont, TIMER_X, TIMER_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
    // frame
    bm->DrawRect(ENull, TIMER_BORDER.x1, TIMER_BORDER.y1, TIMER_BORDER.x2, TIMER_BORDER.y2, COLOR_TIMERBORDER);
    // inner
    const TInt timer_width = TIMER_INNER.x2 - TIMER_INNER.x1;
    const TFloat pct   = TFloat(mBonusTimer) / TFloat(mBonusTime);
    const TInt   width = TInt(pct * timer_width);
    bm->FillRect(ENull, TIMER_INNER.x1, TIMER_INNER.y1, TIMER_INNER.x1 + width, TIMER_INNER.y2, COLOR_TIMERINNER);
  }
}

void GGameState::RenderScore() {
  BBitmap *bm = gDisplay.renderBitmap;
  char    score_text[12];

  for (TInt i   = 0; i < 8; i++) {
    TInt v = (mScore.mValue >> ((7 - i) * 4)) & 0x0f;
    score_text[i] = '0' + char(v);
  }
  score_text[8] = '\0';
  bm->DrawStringShadow(ENull, score_text, mFont, SCORE_X, SCORE_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
}

void GGameState::RenderLevel() {
  BBitmap *bm = gDisplay.renderBitmap;
  bm->DrawStringShadow(ENull, "Level 25", mFont, LEVEL_X, LEVEL_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
//  BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE, 8, 0);
//  BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE + 1, 24, 0);
//  BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE + 2, 40, 0);
//  TInt      x = 56;
//  for (TInt i = 0; i < 7; i++) {
//    TInt v = (mScore.mValue >> ((7 - i) * 4)) & 0x0f;
//    // commented out to show lead zeros
////    if (v) {
//    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, 0);
////    }
//    x += 8;
//  }
//  TInt      v = mScore.mValue & 0x0f;
//  BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, 0);

}

void GGameState::RenderNext() {
  BBitmap *bm = gDisplay.renderBitmap;
  bm->DrawStringShadow(ENull, "Next", mFont, NEXT_X, NEXT_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
}

void GGameState::RenderMovesLeft() {
  BBitmap *bm = gDisplay.renderBitmap;

  // frame
  bm->DrawRect(ENull, MOVES_BORDER.x1, MOVES_BORDER.y1, MOVES_BORDER.x2, MOVES_BORDER.y2, COLOR_BORDER1);
  // inner
  const TInt moves_width = MOVES_INNER.x2 - MOVES_INNER.x1;
  const TFloat pct   = TFloat(mBlocksRemaining) / TFloat(mBlocksThisLevel);
  const TInt   width = TInt(pct * moves_width);
  bm->FillRect(ENull, MOVES_INNER.x1, MOVES_INNER.y1, MOVES_INNER.x1 + width, MOVES_INNER.y2, COLOR_BORDER2);
}

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

// render on top of the background
void GGameState::PostRender() {
  BBitmap *bm = gDisplay.renderBitmap;
  //
  RenderTimer();
  RenderScore();
  RenderLevel();
  RenderMovesLeft();
  RenderNext();

  // render GAME OVER message
  if (mGameOver) {
    TInt x = BOARD_X + VISIBLE_BOARD_COLS * 16 + 32;
    // TODO: draw using DrawBitmapTransparent() in one call
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER, x, BOARD_Y);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER + 1, x + 16, BOARD_Y);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER + 2, x + 32, BOARD_Y);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER + 3, x + 48, BOARD_Y);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2, x, BOARD_Y + 16);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2 + 1, x + 16, BOARD_Y + 16);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2 + 2, x + 32, BOARD_Y + 16);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2 + 3, x + 48, BOARD_Y + 16);
  }


}

