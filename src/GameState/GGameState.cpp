#include "Game.h"
#include "GGameBoard.h"
#include "GLevel1Playfield.h"
#include "GLevel2Playfield.h"
//#include "GLevel3Playfield.h"
#include "GGameProcess.h"

static const TUint8 GRID_COLOR = 253;;

GGameState::GGameState() : BGameEngine(gViewPort) {
  mLevel       = 1;
  mGameOver    = EFalse;
  mPlayfield   = ENull;
  mGameProcess = ENull;
  mBonusTime   = 15 * 30;   // TODO: difficulty, etc.
  mBonusTimer  = -1;
  LoadLevel();
}

GGameState::~GGameState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG3_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG4_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG5_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG6_SLOT);
}

void GGameState::PreRender() {
  if (mBonusTimer >= 0) {
    mBonusTimer--;
    if (mBonusTimer < 0) {
      printf("remove blocks\b");
      mGameProcess->RemoveBlocks();
    }
  }
}

void GGameState::LoadLevel() {
  switch (mLevel) {
    case 1:
    default:

      delete mPlayfield;
      mPlayfield = new GLevel1Playfield(this);

      gSoundPlayer.PlayMusic(SONG1_S3M);
      break;
  }
  BBitmap *playerBitmap = gResourceManager.GetBitmap(PLAYER_SLOT);

  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBackground, 0, 128);
  gDisplay.SetPalette(playerBitmap, 128, 128);
  gDisplay.SetColor(GRID_COLOR, 255, 255, 255);

  delete mGameProcess;
  mGameProcess = new GGameProcess(this);
  AddProcess((BProcess *) mGameProcess);

  mGameBoard.Clear();

#ifdef RENDER_GRID
  // draw grid on backgrounds
  for (TInt row = 0; row < VISIBLE_BOARD_ROWS + 1; row++) {
    mBackground0->DrawFastHLine(ENull, BOARD_X, BOARD_Y + row * 16, VISIBLE_BOARD_COLS * 16, GRID_COLOR);
  }
  for (TInt col = 0; col < VISIBLE_BOARD_COLS + 1; col++) {
    mBackground0->DrawFastVLine(ENull, BOARD_X + col * 16, BOARD_Y, VISIBLE_BOARD_ROWS * 16, GRID_COLOR);
  }
#endif
}

// render on top of the background
void GGameState::PostRender() {
  BBitmap *bm = gDisplay.renderBitmap;
#if 0
  // render the red circles/dots at the top
for (TInt i = 0, j = mBoardX; i < VISIBLE_BOARD_COLS; i++, j++) {
  BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_OFF, BOARD_X + i*16, BOARD_Y - 16);
//    if (j & 1) {
//      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_ON, BOARD_X + i * 16, SCREEN_HEIGHT - 16);
//      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_ON, BOARD_X + i * 16, BOARD_Y - 16);
//    } else {
//      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_OFF, BOARD_X + i * 16, SCREEN_HEIGHT - 16);
//      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_OFF, BOARD_X + i * 16, BOARD_Y - 16);
//    }
}
#endif
#if 0
  for (TInt i = 0, j = mBoardY; i < VISIBLE_BOARD_ROWS; i++, j++) {
//    if (j & 1) {
//      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_ON, BOARD_X - 16, BOARD_Y + i * 16);
//      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_ON, BOARD_X + VISIBLE_BOARD_COLS * 16, BOARD_Y + i * 16);
//    } else {
//      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_OFF, BOARD_X - 16, BOARD_Y + i * 16);
  BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_OFF, BOARD_X + VISIBLE_BOARD_COLS * 16, BOARD_Y + i * 16);
//    }
}
#endif
  // Score
  BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE, 8, 0);
  BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE + 1, 24, 0);
  BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE + 2, 40, 0);
  TInt      x = 56;
  for (TInt i = 0; i < 7; i++) {
    TInt v = (mScore.mValue >> ((7 - i) * 4)) & 0x0f;
    // commented out to show lead zeros
//    if (v) {
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, 0);
//    }
    x += 8;
  }
  TInt      v = mScore.mValue & 0x0f;
  BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, 0);

  // render GAME OVER message
  if (mGameOver) {
    x = BOARD_X + VISIBLE_BOARD_COLS * 16 + 32;
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER, x, BOARD_Y);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER + 1, x + 16, BOARD_Y);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER + 2, x + 32, BOARD_Y);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER + 3, x + 48, BOARD_Y);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2, x, BOARD_Y + 16);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2 + 1, x + 16, BOARD_Y + 16);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2 + 2, x + 32, BOARD_Y + 16);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2 + 3, x + 48, BOARD_Y + 16);
  }

  // render timer
  // TODO: move to GGameTimer class?
  static const TInt TIMER_X     = BOARD_X + 47;
  static const TInt TIMER_Y     = BOARD_Y - 20;
  static const TInt TIMER_WIDTH = 100; // BOARD_X + BOARD_COLS * 16 - TIMER_X;

  if (mBonusTimer >= 0) {
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_TIME, 16, 14);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_TIME + 1, 16 + 16, 14);
//  bm->DrawFastHLine(gViewPort, BOARD_X + 48, BOARD_Y - 20, BOARD_COLS * 12, COLOR_TIMERBORDER);
//  bm->DrawFastHLine(gViewPort, BOARD_X + 48, BOARD_Y - 8, BOARD_COLS * 12, COLOR_TIMERBORDER);
    bm->DrawFastHLine(gViewPort, TIMER_X, TIMER_Y, TIMER_WIDTH, COLOR_TIMERBORDER);
    bm->DrawFastHLine(gViewPort, TIMER_X, TIMER_Y + 12, TIMER_WIDTH, COLOR_TIMERBORDER);

    // calculate width and offset of timer, based upon time remaining
    const TFloat pct   = TFloat(mBonusTimer) / TFloat(mBonusTime);
    const TInt   width = pct * TIMER_WIDTH;
    for (TInt    y     = 0; y < 9; y++) {
      bm->DrawFastHLine(gViewPort, TIMER_X, TIMER_Y + 2 + y, width, COLOR_TIMERINNER);
    }
  }

}

