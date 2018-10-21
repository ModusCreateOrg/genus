//
// Created by mschwartz on 10/21/18.
//

#include "Game.h"
#include "GGamePlayfield.h"

GGamePlayfield::GGamePlayfield(GGameState *aGameEngine) {
  mGameEngine = aGameEngine;
  mTextColor = 0;
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
}

//~GGamePlayfield::GGamePlayfield()  {
//
//}

void GGamePlayfield::Animate() {
  mTextColor += 1;
  mTextColor %= 64;
  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);
}

void GGamePlayfield::Render() {
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
  TInt x = 56;
  for (TInt i = 0; i < 7; i++) {
    TInt v = (mGameEngine->mScore.mValue >> ((7 - i) * 4)) & 0x0f;
    // commented out to show lead zeros
//    if (v) {
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, 0);
//    }
    x += 8;
  }
  TInt v = mGameEngine->mScore.mValue & 0x0f;
  BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, 0);

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

  // render timer
  // TODO: move to GGameTimer class?
  static const TInt TIMER_X = BOARD_X + 56;
  static const TInt TIMER_Y = BOARD_Y - 20;
  static const TInt TIMER_WIDTH = BOARD_X + BOARD_COLS * 16 - TIMER_X;

  if (mGameEngine->mBonusTimer >= 0) {
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_TIME, 16, 14);
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_TIME + 1, 16 + 16, 14);
//  bm->DrawFastHLine(gViewPort, BOARD_X + 48, BOARD_Y - 20, BOARD_COLS * 12, COLOR_TIMERBORDER);
//  bm->DrawFastHLine(gViewPort, BOARD_X + 48, BOARD_Y - 8, BOARD_COLS * 12, COLOR_TIMERBORDER);
    bm->DrawFastHLine(gViewPort, TIMER_X, TIMER_Y, TIMER_WIDTH, COLOR_TIMERBORDER);
    bm->DrawFastHLine(gViewPort, TIMER_X, TIMER_Y + 12, TIMER_WIDTH, COLOR_TIMERBORDER);

    // calculate width and offset of timer, based upon time remaining
    const TFloat pct = TFloat(mGameEngine->mBonusTimer) / TFloat(mGameEngine->mBonusTime);
    const TInt width = pct * TIMER_WIDTH;
    for (TInt y = 0; y < 9; y++) {
      bm->DrawFastHLine(gViewPort, TIMER_X, TIMER_Y + 2 + y, width, COLOR_TIMERINNER);
    }
  }

}

