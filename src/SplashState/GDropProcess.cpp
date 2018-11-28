//
// Created by Michael Schwartz on 11/16/18.
//

#include "GDropProcess.h"


static ANIMSCRIPT Drop1Animation[] = {
  ABITMAP(PLAYER_SLOT),
  ASTEP(1, IMG_DROP1),
  ASTEP(1, IMG_DROP1+1),
  ASTEP(1, IMG_DROP1+2),
  AEND
};

static ANIMSCRIPT Drop2Animation[] = {
  ABITMAP(PLAYER_SLOT),
  ASTEP(1, IMG_DROP2),
  ASTEP(1, IMG_DROP2+1),
  ASTEP(1, IMG_DROP2+2),
  AEND
};

static ANIMSCRIPT Drop3Animation[] = {
  ABITMAP(PLAYER_SLOT),
  ASTEP(1, IMG_DROP3),
  ASTEP(1, IMG_DROP3+1),
  ASTEP(1, IMG_DROP3+2),
  ASTEP(1, IMG_DROP3+3),
  AEND
};

static ANIMSCRIPT Drop4Animation[] = {
  ABITMAP(PLAYER_SLOT),
  ASTEP(1, IMG_DROP4),
  ASTEP(1, IMG_DROP4+1),
  ASTEP(1, IMG_DROP4+2),
  ASTEP(1, IMG_DROP4+3),
  AEND
};

static ANIMSCRIPT Drop5Animation[] = {
  ABITMAP(PLAYER_SLOT),
  ASTEP(1, IMG_DROP5),
  ASTEP(1, IMG_DROP5+1),
  ASTEP(1, IMG_DROP5+2),
  ASTEP(1, IMG_DROP5+3),
  AEND
};

static ANIMSCRIPT Drop6Animation[] = {
  ABITMAP(PLAYER_SLOT),
  ASTEP(1, IMG_DROP6),
  ASTEP(1, IMG_DROP6+1),
  ASTEP(1, IMG_DROP6+2),
  AEND
};

//class GSplashState;

GDropProcess::GDropProcess(GSplashState *aSplashState, TInt16 aDropNumber ) : BProcess() {
  mSplashState = aSplashState;
  mSprite      = new BAnimSprite(1, PLAYER_SLOT);
  mSplashState->AddSprite(mSprite);
  mSprite->flags |= SFLAG_MOVE;

  SetTimer();
  mState      = STATE_WAIT;
  mDropNumber = aDropNumber;
}

void GDropProcess::SetTimer() {
  mTimer = TInt16(Random(30, 60) + Random(10, 35));
  mSprite->flags &= ~SFLAG_RENDER;
}

TBool GDropProcess::WaitState() {
  mTimer--;
  if (mTimer > 0) {
    return ETrue;
  }
  switch (mDropNumber) {
    case 0:
      mSprite->x = 37;
      mSprite->y = 118;
      mSprite->StartAnimation(Drop1Animation);
      break;
    case 1:
      mSprite->x = 97;
      mSprite->y = 124;
      mSprite->StartAnimation(Drop2Animation);
      break;
    case 2:
      mSprite->x = 175;
      mSprite->y = 120;
      mSprite->StartAnimation(Drop3Animation);
      break;
    case 3:
      mSprite->x = 222;
      mSprite->y = 122;
      mSprite->StartAnimation(Drop4Animation);
      break;
    case 4:
      mSprite->x = 40;
      mSprite->y = 138;
      mSprite->StartAnimation(Drop5Animation);
      break;
    case 5:
      mSprite->x = 235;
      mSprite->y = 156;
      mSprite->StartAnimation(Drop6Animation);
      break;
    default:
      Panic("GDropProcess: invalid drop number");
  }
  mState = STATE_FORM;
  mSprite->vy = 0;
  return ETrue;
}

TBool GDropProcess::FormState() {
  if (mSprite->AnimDone()) {
    mState = STATE_FALL;
    switch (mDropNumber) {
      case 0:
        mSprite->x += 6;
        mSprite->y += 11;
        mSprite->mImageNumber = IMG_DROP1 + 3;
        break;
      case 1:
        mSprite->x += 1;
        mSprite->y += 11;
        mSprite->mImageNumber = IMG_DROP2 + 3;
        break;
      case 2:
        mSprite->x += 5;
        mSprite->y += 18;
        mSprite->mImageNumber = IMG_DROP3 + 4;
        break;
      case 3:
        mSprite->x += 7;
        mSprite->y += 18;
        mSprite->mImageNumber = IMG_DROP4 + 4;
        break;
      case 4:
        mSprite->x += 7;
        mSprite->y += 18;
        mSprite->mImageNumber = IMG_DROP5 + 4;
        break;
      case 5:
        mSprite->x += 0;
        mSprite->y += 18;
        mSprite->mImageNumber = IMG_DROP6 + 3;
        break;
    }
  }
  return ETrue;
}

TBool GDropProcess::FallState() {
  if (mSprite->y > 240) {
    mState = STATE_WAIT;
    SetTimer();
  } else {
    mSprite->vy += GRAVITY;
  }
  return ETrue;
}

TBool GDropProcess::RunAfter() {
  switch (mState) {
    case STATE_WAIT:
      return WaitState();
    case STATE_FORM:
      return FormState();
    case STATE_FALL:
    default:
      return FallState();
  }
}


