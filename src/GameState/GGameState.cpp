#include "Game.h"
#include "GGameBoard.h"
#include "GGameStateGameOverProcess.h"
#include "Playfields/GLevelCountryside.h"
#include "Playfields/GLevelCyberpunk.h"
#include "Playfields/GLevelUnderWaterOne.h"
#include "Playfields/GLevelGlacialMountains.h"
#include "Playfields/GLevelUnderWaterFantasy.h"
#include "Playfields/GLevelSpace.h"

#ifdef CHICKEN_MODE
class GGameState;
class ChickenModeProcess : public BProcess {
  public:
    ChickenModeProcess(GGameState *aState) : BProcess() {
      mState = aState;
    }

    ~ChickenModeProcess() {}

    TBool RunBefore() {
      if (gControls.WasPressed(BUTTON_SELECT)) {
        while (mState->mLevel % 5 > 0) {
          mState->mLevel++;
        }
        mState->mBlocksRemaining = 0;
      }
      return ETrue;
    }

    TBool RunAfter() {
      return ETrue;
    }

    GGameState *mState;
};
#endif

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

GGameState::GGameState() : BGameEngine(gViewPort) {
  mLevel      = 1;
  mGameOver   = EFalse;
  mPlayfield  = ENull;
  mBonusTimer = -1;

  gResourceManager.LoadBitmap(COMMON_SPRITES_BMP, COMMON_SLOT, IMAGE_16x16);

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
  mNextSprite->flags |= SFLAG_RENDER | SFLAG_NEXT_BLOCK;
  mNextSprite->x = NEXT_BLOCK_X;
  mNextSprite->y = NEXT_BLOCK_Y;
  mNextSprite->Randomize();

  mGameProcess = new GNoPowerup(mSprite, this);
  AddProcess(mGameProcess);

#ifdef CHICKEN_MODE
  AddProcess(new ChickenModeProcess(this));
#endif

  Next(EFalse);
}

GGameState::~GGameState() {
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
  mSprite->x = PLAYER_X;
  mSprite->y = PLAYER_Y;

  if (mGameOver || mGameBoard.IsGameOver()) {
    mSprite->Copy(mNextSprite);
    mNextSprite->Randomize();
    mGameProcess->Signal();
    return;
  }

  if (aCanPowerup) {
    TInt maybe = 0;

    switch (gOptions->difficulty) {
      case DIFFICULTY_EASY:
        maybe = Random(15, 20);
        break;
      case DIFFICULTY_INTERMEDIATE:
        maybe = Random(15, 22);
        break;
      case DIFFICULTY_HARD:
        maybe = Random(15, 24);
        break;
      default:
        Panic("DifficultyString: invalid difficulty %d", gOptions->difficulty);
    }

    if (maybe == 16) {
      if (Random() & 1) {
        AddProcess(new GModusBombPowerup(mSprite, this));
        return;
      } else if (mGameBoard.CountColorSwappableBlocks() > 0) {
        AddProcess(new GColorSwapPowerup(mSprite, this));
        return;
      }
    }
  }

  // NOT a powerup or powerup criteria not met
  mSprite->Copy(mNextSprite);
  mNextSprite->Randomize();
  mGameProcess->Signal();
}

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

void GGameState::GameOver() {
  mSprite->flags &= ~(SFLAG_RENDER | SFLAG_ANIMATE);
  mGameProcess->Wait();
  mBonusTimer = -1;
  mGameOver = ETrue;
  AddProcess(new GGameStateGameOverProcess(this));
  THighScoreTable h;
  h.Load();
  h.lastScore[gOptions->difficulty].mValue = mScore.mValue;
  h.Save();
  gSoundPlayer.PlayMusic(GAMEOVER_XM);
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
  bool newStage = false;

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

    // Release only if bitmap was loaded
    if (gResourceManager.GetBitmap(PLAYER_SLOT)) {
      gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
    }


    switch ((mLevel / 5) % 6) {
      case 0:
        mPlayfield = new GLevelCountryside(this); // Playfield 1
        gResourceManager.LoadBitmap(LEVEL1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(COUNTRYSIDE_XM);
        newStage = true;
        break;
      case 1:
        mPlayfield = new GLevelUnderWaterOne(this); // Playfield 2
        gResourceManager.LoadBitmap(LEVEL2_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(UNDER_WATER_XM);
        newStage = true;
        break;
      case 2:
        mPlayfield = new GLevelGlacialMountains(this); // Playfield 3
        gResourceManager.LoadBitmap(LEVEL3_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(GLACIAL_MOUNTAINS_XM);
        newStage = true;
        break;
      case 3:
        // TODO: @Jay???
        mPlayfield = new GLevelUnderWaterFantasy(this); // Playfield 2
        gResourceManager.LoadBitmap(LEVEL4_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(UNDERWATERFANTASY_XM);
        newStage = true;
        break;
      case 4:
        mPlayfield = new GLevelCyberpunk(this); // Playfield 5
        gResourceManager.LoadBitmap(LEVEL5_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(CYBERPUNK_XM);
        newStage = true;
        break;
      case 5:
        mPlayfield = new GLevelSpace(this); // Playfield 6
        gResourceManager.LoadBitmap(LEVEL6_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
        gSoundPlayer.PlayMusic(SPAAACE_XM);
        newStage = true;
        break;
      default:
        Panic("LoadLevel invalid level\n");
    }


  }


  if (newStage && mLevel > 1) {
    gSoundPlayer.SfxNextStage();
  }
  else if (mLevel > 1) {
    gSoundPlayer.SfxNextLevel();
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
  switch (strlen(lev)) {
    case 1:
      strcpy(out, "Level  ");
      strcat(out, lev);
      break;
    case 2:
      strcpy(out, "Level ");
      strcat(out, lev);
      break;
    case 3:
      strcpy(out, "Level");
      strcat(out, lev);
      break;
    default:
      // Levels are limited to 999 in UI
      strcpy(out, "Level");
      strcat(out, "999");
  }

  bm->DrawStringShadow(ENull, out, mFont16, LEVEL_X, LEVEL_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
}

void GGameState::RenderNext() {
  BBitmap *bm = gDisplay.renderBitmap;
  bm->DrawStringShadow(ENull, "Next", mFont16, NEXT_X, NEXT_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);

  // On HARD difficulty draw a "?" over a filled block
  if (gOptions->difficulty == DIFFICULTY_HARD) {
    bm->DrawStringShadow(ENull, "?", mFont16, NEXT_BLOCK_X + 8, NEXT_BLOCK_Y + 8, COLOR_TEXT, COLOR_TEXT_SHADOW, -1);
  }
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

