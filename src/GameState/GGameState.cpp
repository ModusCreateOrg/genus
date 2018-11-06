#include "Game.h"
#include "GGameBoard.h"
#include "GameState/Playfields/GLevelCountryside.h"
#include "GameState/Playfields/GLevelCyberpunk.h"
#include "GameState/Playfields/GLevelUnderWater1.h"
#include "GameState/Playfields/GLevelGlacialMountains.h"
#include "GGameProcess.h"

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

GGameState::GGameState() : BGameEngine(gViewPort) {
  mLevel      = 1;
  mGameOver   = EFalse;
  mPlayfield  = ENull;
  mBonusTime  = 15 * 30;   // TODO: difficulty, etc.
  mBonusTimer = -1;

  gResourceManager.LoadBitmap(COMMON_SPRITES_BMP, COMMON_SLOT, IMAGE_16x16);
  gResourceManager.LoadBitmap(CHARSET_8X8_BMP, FONT_8x8_SLOT, IMAGE_8x8);
  gResourceManager.LoadBitmap(CHARSET_16X16_BMP, FONT_16x16_SLOT, IMAGE_16x16);
  mFont = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);

  mGameBoard.Clear();
  LoadLevel();
  mGameProcess = new GGameProcess(this);
  AddProcess((BProcess *) mGameProcess);
}

GGameState::~GGameState() {
  gResourceManager.ReleaseBitmapSlot(FONT_16x16_SLOT);
  gResourceManager.ReleaseBitmapSlot(FONT_8x8_SLOT);
  gResourceManager.ReleaseBitmapSlot(COMMON_SLOT);
  gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
  delete mFont;
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
#if 1
  if (mLevel & 1) {
    mBlocksThisLevel = 20;

    delete mPlayfield;
    mPlayfield = new GLevelCountryside(this);

    gResourceManager.LoadBitmap(LEVEL1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
    gSoundPlayer.PlayMusic(SONG1_S3M);
  } else {
    mBlocksThisLevel = 20;

    delete mPlayfield;
    mPlayfield = new GLevelCyberpunk(this);
    gResourceManager.LoadBitmap(LEVEL1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);

    // TODO: Jay needs to implement this
//      gSoundPlayer.PlayMusic(SONG2_S3M);
    gSoundPlayer.PlayMusic(SONG1_S3M);    // TODO: Jay needs to remove this hack..  Hack for now so we have some music
  }
#else
  switch (mLevel) {
    case 1:
    default:
      mBlocksThisLevel = 100;

      delete mPlayfield;
      mPlayfield = new GLevelCountryside(this);

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
#endif
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


  mBlocksRemaining = mBlocksThisLevel;
}

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

void GGameState::RenderTimer() {
  BBitmap *bm = gDisplay.renderBitmap;
  if (mBonusTimer >= 0) {

    bm->DrawStringShadow(ENull, "Time", mFont, TIMER_X, TIMER_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
    // frame
    bm->DrawRect(ENull, TIMER_BORDER.x1, TIMER_BORDER.y1, TIMER_BORDER.x2, TIMER_BORDER.y2, COLOR_TIMER_BORDER);
    // inner
    const TInt   timer_width = TIMER_INNER.x2 - TIMER_INNER.x1;
    const TFloat pct         = TFloat(mBonusTimer) / TFloat(mBonusTime);
    const TInt   width       = TInt(pct * timer_width);
    bm->FillRect(ENull, TIMER_INNER.x1, TIMER_INNER.y1, TIMER_INNER.x1 + width, TIMER_INNER.y2, COLOR_TIMER_INNER);
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
  TBCD    level((TUint32) mLevel);
  char    lev[10];
  level.ToString(lev, EFalse);
  char out[32];
  if (strlen(lev) == 1) {
    strcpy(out, "Level  ");
  } else {
    strcpy(out, "Level ");
  }
  strcat(out, lev);

  bm->DrawStringShadow(ENull, out, mFont, LEVEL_X, LEVEL_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
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
  const TInt   moves_width = MOVES_INNER.x2 - MOVES_INNER.x1;
  const TFloat pct         = TFloat(mBlocksRemaining) / TFloat(mBlocksThisLevel);
  const TInt   width       = TInt(pct * moves_width);
  bm->FillRect(ENull, MOVES_INNER.x1, MOVES_INNER.y1, MOVES_INNER.x1 + width, MOVES_INNER.y2, COLOR_BORDER2);
}

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

// render on top of the background
void GGameState::PostRender() {
  if (mBlocksRemaining < 1) {
    mLevel++;
    LoadLevel();
  }
  //
  RenderTimer();
  RenderScore();
  RenderLevel();
  RenderMovesLeft();
  RenderNext();

  // render GAME OVER message
  if (mGameOver) {
    if (mFrameCounter & 4) {
      BBitmap *bm = gDisplay.renderBitmap;
      bm->DrawBitmapTransparent(ENull, gResourceManager.GetBitmap(COMMON_SLOT), TRect(0, 0, 127, 15),
                                (DISPLAY_WIDTH - 128) / 2, (DISPLAY_HEIGHT - 16) / 2);
    }
  }
}

