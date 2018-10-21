#include "Game.h"
#include "GGameBoard.h"
#include "GGamePlayfield.h"
#include "GGameProcess.h"

static const TUint8 GRID_COLOR = 253;;

GGameState::GGameState() : BGameEngine(gViewPort) {
  mLevel = 1;
  mGameOver = EFalse;
  mPlayfield = ENull;
  mGameProcess = ENull;
  mBonusTime = 15 * 30;   // TODO: difficulty, etc.
  mBonusTimer = -1;
  LoadLevel();
}

GGameState::~GGameState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
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
      gResourceManager.LoadBitmap(LEVEL1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
      gResourceManager.LoadBitmap(LEVEL1_BKG1A_BMP, BKG_SLOT, IMAGE_ENTIRE);
      delete mPlayfield;
      mPlayfield = new GGamePlayfield(this);
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
    mBackground->DrawFastHLine(ENull, BOARD_X, BOARD_Y + row * 16, VISIBLE_BOARD_COLS * 16, GRID_COLOR);
  }
  for (TInt col = 0; col < VISIBLE_BOARD_COLS + 1; col++) {
    mBackground->DrawFastVLine(ENull, BOARD_X + col * 16, BOARD_Y, VISIBLE_BOARD_ROWS * 16, GRID_COLOR);
  }
#endif
}

