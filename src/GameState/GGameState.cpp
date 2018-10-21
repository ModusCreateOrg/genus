#include "Game.h"
#include "GGameBoard.h"
#include "GGameProcess.h"

class GGamePlayfield : public BPlayfield {
public:
  GGamePlayfield(GGameState *aGameEngine) {
    mGameEngine = aGameEngine;
    mTextColor  = 0;
    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  }

  ~GGamePlayfield() {

  }

public:
  void Animate() {
    mTextColor += 1;
    mTextColor %= 64;
    gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);
  }

  void Render() {
    BBitmap *bm = gDisplay.renderBitmap;

    // TODO: wrong place
    gSoundPlayer.PlayMusic(SONG1_S3M);

    gDisplay.renderBitmap->CopyPixels(mBackground);
    mGameEngine->mGameBoard.Render();

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
      TInt v = (mGameEngine->mScore.mValue >> ((7 - i) * 4)) & 0x0f;
      // commented out to show lead zeros
//    if (v) {
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, 0);
//    }
      x += 8;
    }
    TInt      v = mGameEngine->mScore.mValue & 0x0f;
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, 0);

    // render timer
    // TODO: move to GGameTimer class
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_TIME, 16, 14);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_TIME + 1, 16 + 16, 14);
    bm->DrawFastHLine(gViewPort, BOARD_X + 48, BOARD_Y - 20, BOARD_COLS * 12, COLOR_TIMERBORDER);
    bm->DrawFastHLine(gViewPort, BOARD_X + 48, BOARD_Y - 8, BOARD_COLS * 12, COLOR_TIMERBORDER);

    for (TInt y = 0; y < 9; y++) {
      bm->DrawFastHLine(gViewPort, BOARD_X + 48, BOARD_Y - 18 + y, BOARD_COLS * 12, COLOR_TIMERINNER);
    }

    // render GAME OVER message
    if (mGameEngine->mGameOver) {
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

  }

public:
  GGameState *mGameEngine;
  BBitmap    *mBackground;
  TUint8     mTextColor;
};

static const TUint8 GRID_COLOR = 253;;

GGameState::GGameState() : BGameEngine(gViewPort) {
  mLevel       = 1;
  mGameOver    = EFalse;
  mPlayfield   = ENull;
  mGameProcess = ENull;
  LoadLevel();
}

GGameState::~GGameState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
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

