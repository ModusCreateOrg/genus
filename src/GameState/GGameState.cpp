#include "Game.h"
#include "GGameBoard.h"
#include "GGameStateGameOverProcess.h"
#include "Playfields/GLevelCountryside.h"
#include "Playfields/GLevelCyberpunk.h"
#include "Playfields/GLevelUnderWater1.h"
#include "Playfields/GLevelGlacialMountains.h"
#include "Playfields/GLevelUnderWaterFantasy.h"
#include "Playfields/GLevelSpace.h"

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

GGameState::GGameState() : BGameEngine(gViewPort) {
  mLevel      = 1;
  mGameOver   = EFalse;
  mPlayfield  = ENull;
  mBonusTimer = -1;

  gResourceManager.LoadBitmap(COMMON_SPRITES_BMP, COMMON_SLOT, IMAGE_16x16);
  gResourceManager.LoadBitmap(CHARSET_8X8_BMP, FONT_8x8_SLOT, IMAGE_8x8);
  gResourceManager.LoadBitmap(CHARSET_16X16_BMP, FONT_16x16_SLOT, IMAGE_16x16);

  mFont8 = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_8x8);
  mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);

  mGameBoard.Clear();
  LoadLevel();

  mSprite = new GPlayerSprite();
  AddSprite(mSprite);
  mSprite->x  = PLAYER_X;
  mSprite->y  = PLAYER_Y;
  mSprite->vy = 0;

  mNextSprite    = new GPlayerSprite();
  AddSprite(mNextSprite);
  mNextSprite->flags |= SFLAG_RENDER;
  mNextSprite->x = NEXT_BLOCK_X;
  mNextSprite->y = NEXT_BLOCK_Y;
  mNextSprite->Randomize();

  mGameProcess = new GNoPowerup(mSprite, this);
  AddProcess(mGameProcess);
  Next(EFalse);
}

GGameState::~GGameState() {
  mGameProcess->Remove();
  delete mGameProcess;
  mNextSprite->Remove();
  delete mNextSprite;
  mSprite->Remove();
  delete mSprite;

  gResourceManager.ReleaseBitmapSlot(COMMON_SLOT);
  gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
  delete mFont16;
  delete mFont8;
}

/**
 * Next - process next piece
 *
 * This is called by the various *Powerup processes when they are done with their work.
 * For example, M Bomb process will control the piece, place it, loop while blowing up the appropriate pieces,
 * then will call Next() before committing suicide (return EFalse from Run*).
 *
 * This routine will then either copy mNextSprite blocks to mPlayerSprite or if a powerup is possible, maybe
 * will spawn a random powerup.
 *
 * @param aCanPowerup true if Next piece can be a powerup
 */
void GGameState::Next(TBool aCanPowerup) {
  if (aCanPowerup) {
    if (mBonusTimer > 0) {
      printf("canPowerup with bonus timer running!\n");
    }
    TInt maybe = Random(15, 20);
    if (maybe == 16) {
      mGameProcess->Wait();
      if (Random() & 1) {
        AddProcess(new GModusBombPowerup(mSprite, this));
      } else {
        AddProcess(new GColorSwapPowerup(mSprite, this));
      }
      return;
    }
  }

  // NOT a powerup
  if (mGameBoard.IsGameOver()) {   // this belongs in game for production!
    mSprite->flags &= ~SFLAG_RENDER;
    if (mBonusTimer > 1) {
      mBonusTimer = 0;
    }
    else {
      mGameProcess->Wait();
      mGameOver = ETrue;
      AddProcess(new GGameStateGameOverProcess(this));
      THighScoreTable h;
      h.Load();
      h.lastScore[gOptions->difficulty].mValue = mScore.mValue;
      h.Save();
    }
    return;
  }

  mSprite->x = PLAYER_X;
  mSprite->y = PLAYER_Y;
  mSprite->Copy(mNextSprite);
  mNextSprite->Randomize();
  mGameProcess->Signal();
}

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

void GGameState::PreRender() {
  //
}

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

void GGameState::LoadLevel() {
  if ((mLevel % 5) == 1) {  // every 5th level
    delete mPlayfield;
    // difficulty
    // TODO: Jay tweak until you are satisfied!
    mBlocksThisLevel = 20 + mLevel*5 + gOptions->difficulty * 10;
    switch(gOptions->difficulty) {
      case DIFFICULTY_EASY:
        mBonusTime = 20 * 30;
        break;
      case DIFFICULTY_INTERMEDIATE:
        mBonusTime = 15 * 30;
        break;
      case DIFFICULTY_HARD:
        mBonusTime = 10 * 30;
        break;
    }
    //
    switch ((mLevel / 5) % 5) {
      case 0:
        mPlayfield = new GLevelCountryside(this);
        gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
        gResourceManager.LoadBitmap(LEVEL1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(COUNTRYSIDE_XM);
        break;
      case 1:
        mPlayfield = new GLevelUnderWater1(this); // Playfield 2
        gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
        gResourceManager.LoadBitmap(LEVEL2_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(UNDER_WATER_XM);
        break;
      case 2:
        mPlayfield = new GLevelGlacialMountains(this); // Playfield 3
        gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
        gResourceManager.LoadBitmap(LEVEL3_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(GLACIAL_MOUNTAINS_XM);
        break;
      case 3:
        // TODO: @Jay???
        mPlayfield = new GLevelUnderWaterFantasy(this); // Playfield 2    // temporary TODO: @Jay
        gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
        gResourceManager.LoadBitmap(LEVEL4_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(UNDER_WATER_XM);
        break;
      case 4:
        mPlayfield = new GLevelCyberpunk(this); // Playfield 5
        gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
        gResourceManager.LoadBitmap(LEVEL5_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(CITY_SCAPES_XM);
        break;
      case 5:
        mPlayfield = new GLevelSpace(this); // Todo: @Mike, this is Level 6
        gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
        gResourceManager.LoadBitmap(LEVEL6_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(SPAAACE_XM);
        break;
      default:
        Panic("LoadLevel invalid level\n");
    }
  }
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

    bm->DrawStringShadow(ENull, "Time", mFont16, TIMER_X, TIMER_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
    // frame
    bm->DrawRect(ENull, TIMER_BORDER.x1, TIMER_BORDER.y1, TIMER_BORDER.x2, TIMER_BORDER.y2, COLOR_TIMER_BORDER);
    // inner
    const TInt   timer_width = TIMER_INNER.x2 - TIMER_INNER.x1;
    const TFloat pct         = TFloat(mBonusTimer) / TFloat(mBonusTime);
    const TInt   width       = TInt(pct * timer_width);
    if (width > (TIMER_INNER.x2 - TIMER_INNER.x1 + 1)) {
      printf("BUG!  mBonusTimer: %d, mBonusTime: %d\n", mBonusTimer, mBonusTime);
      Panic("Aborting\n");
    }
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
  bm->DrawStringShadow(ENull, score_text, mFont16, SCORE_X, SCORE_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
  bm->DrawStringShadow(ENull, gOptions->DifficultyString(), mFont8, SCORE_X+4, SCORE_Y+18, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -1);
}

void GGameState::RenderLevel() {
  BBitmap *bm = gDisplay.renderBitmap;
  TBCD level;
  level.FromUint32(mLevel);
  char    lev[20];
  level.ToString(lev, ENull);
  char out[32];
  if (strlen(lev) == 1) {
    strcpy(out, "Level  ");
  } else {
    strcpy(out, "Level ");
  }
  strcat(out, lev);

  bm->DrawStringShadow(ENull, out, mFont16, LEVEL_X, LEVEL_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
}

void GGameState::RenderNext() {
  BBitmap *bm = gDisplay.renderBitmap;
  bm->DrawStringShadow(ENull, "Next", mFont16, NEXT_X, NEXT_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
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
  if (!mGameOver && mBlocksRemaining < 1) {
    mLevel++;
    LoadLevel();
  }
  //
  RenderTimer();
  RenderScore();
  RenderLevel();
  RenderMovesLeft();
  RenderNext();
}

