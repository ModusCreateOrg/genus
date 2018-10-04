#include "Game.h"

const TInt ANIMATE_TIME = 6;
const TInt BEAT_TIME    = 20;

class GPlayerSprite : public BSprite {
public:
  GPlayerSprite() : BSprite(0, PLAYER_SLOT) {
    this->flags = SFLAG_RENDER;
    Randomize();
  }

  virtual ~GPlayerSprite() {}

public:
  void Randomize() {
    mBlocks[0] = TInt8(Random() & 1);
    mBlocks[1] = TInt8(Random() & 1);
    mBlocks[2] = TInt8(Random() & 1);
    mBlocks[3] = TInt8(Random() & 1);
    this->x  = PLAYERX;
    this->y  = PLAYERY;
    this->vy = 0;
  }

  void RotateLeft() {
    TInt8 save = mBlocks[0];

    mBlocks[0] = mBlocks[1];
    mBlocks[1] = mBlocks[3];
    mBlocks[3] = mBlocks[2];
    mBlocks[2] = save;
  }

  void RotateRight() {
    TInt8 save = mBlocks[0];

    mBlocks[0] = mBlocks[2];
    mBlocks[2] = mBlocks[3];
    mBlocks[3] = mBlocks[1];
    mBlocks[1] = save;
  }

  TBool Render(BViewPort *aVP) {
    BBitmap *bm = gDisplay.renderBitmap;
    TInt    xx  = TInt(x + .5);
    TInt    yy  = TInt(y + .5);

    bm->DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[0], xx, yy);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[1], xx + 16, yy);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[2], xx, yy + 16);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[3], xx + 16, yy + 16);
    return ETrue;
  }

  void Swap(GPlayerSprite *aOther) {
    TInt8 save;

    save = aOther->mBlocks[0];
    aOther->mBlocks[0]   = this->mBlocks[0];
    this->mBlocks[0] = save;

    save = aOther->mBlocks[1];
    aOther->mBlocks[1]   = this->mBlocks[1];
    this->mBlocks[1] = save;

    save = aOther->mBlocks[2];
    aOther->mBlocks[2]   = this->mBlocks[2];
    this->mBlocks[2] = save;

    save = aOther->mBlocks[3];
    aOther->mBlocks[3]   = this->mBlocks[3];
    this->mBlocks[3] = save;
  }

public:
  TInt8 mBlocks[4];
};;

class GGameProcess : public BProcess {
public:
  GGameProcess() : BProcess() {
    mSprite = new GPlayerSprite();
    gGameEngine->AddSprite(mSprite);
    //
    mHoldSprite = new GPlayerSprite();
    mHoldSprite->x = SCREEN_WIDTH-40;
    mHoldSprite->y = 24;
    gGameEngine->AddSprite(mHoldSprite);
    //
    mNextSprite1 = new GPlayerSprite();
    mNextSprite1->x = 32;
    mNextSprite1->y = PLAYERY;
    gGameEngine->AddSprite(mNextSprite1);

    //
    mNextSprite2 = new GPlayerSprite();
    mNextSprite2->x = 32;
    mNextSprite2->y = PLAYERY + 48;
    gGameEngine->AddSprite(mNextSprite2);
  }

  virtual ~GGameProcess() {
    gGameEngine->RemoveSprite(mSprite);
    delete mSprite;
    mSprite = ENull;
  }

public:
  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (gControls.WasPressed(BUTTONA)) {
      mSprite->RotateLeft();
    } else if (gControls.WasPressed(BUTTONB)) {
      mSprite->RotateRight();
    } else if (gControls.WasPressed(JOYLEFT)) {
      mSprite->x = MAX(mSprite->x - 16, PLAYERX_MIN);
    } else if (gControls.WasPressed(JOYRIGHT)) {
      mSprite->x = MIN(mSprite->x + 16, PLAYERX_MAX);
    } else if (gControls.WasPressed(JOYDOWN)) {
      mSprite->y += 16;
    } else if (gControls.WasPressed(JOYUP)) {
      Hold();
    }
    if (gControls.WasPressed(BUTTON_START)) {
      gGameEngine->SetState(GAME_STATE_GAMEOVER);
      return EFalse;
    }
    return ETrue;
  }

  void Hold() {
    mSprite->Swap(mHoldSprite);
  }

  GPlayerSprite *mSprite;
  GPlayerSprite *mHoldSprite;
  GPlayerSprite *mNextSprite1;
  GPlayerSprite *mNextSprite2;
};

GGameState::GGameState(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  mAnimationTimer = ANIMATE_TIME;
  mGameEngine     = aGameEngine;
  mLevel          = 1;
  mBeat           = 0;
  mTimer          = BEAT_TIME;

//  mScore = TBCD("0");
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
      gResourceManager.LoadBitmap(LEVEL1_BKG1_BMP, BKG_SLOT, IMAGE_ENTIRE);
      gResourceManager.LoadBitmap(LEVEL1_BKG2_BMP, BKG2_SLOT, IMAGE_ENTIRE);
      break;
  }
  mBackground1       = gResourceManager.GetBitmap(BKG_SLOT);
  mBackground2       = gResourceManager.GetBitmap(BKG2_SLOT);
  mCurrentBackground = mBackground1;

//  gDisplay.SetPalette(gResourceManager.GetBitmap(PLAYER_SLOT));
  gDisplay.SetPalette(mBackground1);
  auto *p = new GGameProcess();
  mGameEngine->AddProcess(p);

  Clear();
}

void GGameState::Clear() {
  for (TInt row = 0; row < GAMEBOARD_ROWS; row++) {
    for (TInt col = 0; col < GAMEBOARD_COLS; col++) {
      mGameBoard[row][col] = -1;
    }
  }
}

void GGameState::Animate() {
  if (--mAnimationTimer <= 0) {
    mCurrentBackground = mCurrentBackground == mBackground1 ? mBackground2 : mBackground1;
    mAnimationTimer    = ANIMATE_TIME;
  }
}

void GGameState::Render() {
  gDisplay.renderBitmap->CopyPixels(mCurrentBackground);
  BBitmap *bm = gDisplay.renderBitmap;

  // render the board
  TInt      y   = BOARDY;
  for (TInt row = 0; row < GAMEBOARD_ROWS; row++) {
    TInt      x   = BOARDX;
    for (TInt col = 0; col < GAMEBOARD_COLS; col++) {
      if (mGameBoard[row][col] != -1) {
        bm->DrawSprite(gViewPort, PLAYER_SLOT, mGameBoard[row][col], x, y);
      }
    }
  }

  // render the red circles/dots at the bottom
  if (--mTimer < 1) {
    mBeat  = (mBeat + 1) % GAMEBOARD_COLS;
    mTimer = BEAT_TIME;
  }
  y             = SCREEN_HEIGHT - 16;
  for (TInt i = 0; i < GAMEBOARD_COLS; i++) {
    if (i == mBeat) {
      bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_ON, BOARDX + i * 16, y);
    } else {
      bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_OFF, BOARDX + i * 16, y);
    }
  }

  // render text bits in the right column
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_HOLD, SCREEN_WIDTH-40, 8);
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_HOLD+1, SCREEN_WIDTH-40+16, 8);

  // Score
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE, SCREEN_WIDTH-40-8, 8+64);
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE+1, SCREEN_WIDTH-40+8, 8+64);
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE+2, SCREEN_WIDTH-40+24, 8+64);
  y = 8 + 64 + 16;
  TInt x = (SCREEN_WIDTH - 8) - 8 * 16;
  for (TInt i = 0; i<7; i++) {
    TInt v = (mScore.mValue>>((7-i)*4)) & 0x0f;
    if (v) {
      bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, y);
    }
    x += 16;
  }
  TInt v = mScore.mValue & 0x0f;
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, y);
}

