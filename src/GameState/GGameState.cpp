#include "Game.h"
#include "GGameProcess.h"

// options
// comment out the undefs to enable the option
#define RENDER_GRID
//#undef RENDER_GRID
#define RENDER_CHECKERBOARD
//#undef RENDER_CHECKERBOARD

static const TUint8 GRID_COLOR = 253;;

GGameState::GGameState(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  mGameEngine = aGameEngine;
  mLevel      = 1;
  mGameOver   = EFalse;
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
      break;
  }
  BBitmap *playerBitmap = gResourceManager.GetBitmap(PLAYER_SLOT);

  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBackground, 0, 128);
  gDisplay.SetPalette(playerBitmap, 128, 128);
  gDisplay.SetColor(GRID_COLOR, 255, 255, 255);

  mGameProcess = new GGameProcess(this);
  mGameEngine->AddProcess((BProcess *) mGameProcess);

  mBoardX = mBoardY = 0;

  Clear();

#ifdef RENDER_GRID
  // draw grid on backgrounds
  for (TInt row = 0; row < VISIBLE_BOARD_ROWS + 1; row++) {
    mBackground->DrawFastHLine(ENull, BOARD_X, BOARD_Y + row * 16, VISIBLE_BOARD_COLS * 16, GRID_COLOR);
  }
  for (TInt col = 0; col < VISIBLE_BOARD_COLS + 1; col++) {
    mBackground->DrawFastVLine(ENull, BOARD_X + col * 16, BOARD_Y, VISIBLE_BOARD_ROWS * 16, GRID_COLOR);
  }
#endif

  mTextColor = 0;
}

void GGameState::Clear() {
  for (TInt row = 0; row < BOARD_ROWS; row++) {
    for (TInt col = 0; col < BOARD_COLS; col++) {
      mGameBoard[row][col] = 255;
    }
  }
}

void GGameState::Animate() {
  mTextColor += 1;
  mTextColor %= 64;
  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);
}

void GGameState::CountScore() {
  TUint32 accumulated_score = 0;
  TUint8  quad[4];

  for (TInt row = 0; row < BOARD_ROWS - 1; row++) {
    for (TInt col = 0; col < BOARD_COLS - 1; col++) {
      if (!GetQuad(row, col, quad)) {
        continue;
      }
      if (quad[0] > 1 || quad[1] > 1 || quad[2] > 1 || quad[3] > 1) {
        continue;
      }

      TInt      score  = 1;
      // look right
      for (TInt right  = col + 1; right < BOARD_COLS; right++) {
        if (!GetQuad(row, right, quad)) {
          break;
        }
        score *= 2;
      }
      // look down
      for (TInt bottom = row + 1; bottom < BOARD_ROWS; bottom++) {
        if (!GetQuad(bottom, col, quad)) {
          break;
        }
        score *= 2;
      }
      accumulated_score += score;

    }
  }
  mPoints += accumulated_score;

  if (accumulated_score > 0) {
    gSoundPlayer.PlaySound(5,0,EFalse);
  }

  mLastScore.FromUint32(0);
  TBCD p;
  p.FromUint32(accumulated_score);
  mScore.Add(p);
  printf("Score: %d\n", accumulated_score);
}

void GGameState::Combine() {
  TUint8  quad[4];

  for (TInt row = 0; row < BOARD_ROWS - 1; row++) {
    for (TInt col = 0; col < BOARD_COLS - 1; col++) {
      if (!GetQuad(row, col, quad)) {
        continue;
      }
      if (quad[0] > 1 || quad[1] > 1 || quad[2] > 1 || quad[3] > 1) {
        continue;
      }

      mGameBoard[row][col] |= 8;
      mGameBoard[row][col + 1] |= 8;
      mGameBoard[row + 1][col] |= 8;
      mGameBoard[row + 1][col + 1] |= 8;
      // look right
      for (TInt right  = col + 1; right < BOARD_COLS; right++) {
        if (!GetQuad(row, right, quad)) {
          break;
        }
        mGameBoard[row][right] |= 8;
        mGameBoard[row + 1][right] |= 8;
      }
      // look down
      for (TInt bottom = row + 1; bottom < BOARD_ROWS; bottom++) {
        if (!GetQuad(bottom, col, quad)) {
          break;
        }
        mGameBoard[bottom][col] |= 8;
        mGameBoard[bottom + 1][col] |= 8;
      }
    }
  }
}

TBool GGameState::IsGameOver() {
  for (TInt row = 0; row < BOARD_ROWS - 1; row++) {
    for (TInt col = 0; col < BOARD_COLS - 1; col++) {
      if (mGameBoard[row][col] == 255 && mGameBoard[row][col + 1] == 255 && mGameBoard[row + 1][col] == 255 &&
          mGameBoard[row + 1][col + 1] == 255) {
        return EFalse;
      }
    }
  }
  return ETrue;
}

void GGameState::Render() {
  gSoundPlayer.PlayMusic(SONG1_S3M);

  gDisplay.renderBitmap->CopyPixels(mBackground);
  BBitmap *bm = gDisplay.renderBitmap;

  // render the board
  TInt      y   = BOARD_Y;
  for (TInt row = 0; row < VISIBLE_BOARD_ROWS; row++) {
    TInt      x   = BOARD_X;
    for (TInt col = 0; col < VISIBLE_BOARD_COLS; col++) {
      TUint8 v = mGameBoard[mBoardY + row][mBoardX + col];
      if (v != 255) {
        bm->DrawSprite(gViewPort, PLAYER_SLOT, v, x + col * 16, y + row * 16);
      }
#ifdef RENDER_CHECKERBOARD
      else if (row & 1) {
        bm->DrawSprite(gViewPort, PLAYER_SLOT, col & 1 ? IMG_BGTILE1 : IMG_BGTILE2, x + col * 16, y + row * 16);
      } else {
        bm->DrawSprite(gViewPort, PLAYER_SLOT, col & 1 ? IMG_BGTILE2 : IMG_BGTILE1, x + col * 16, y + row * 16);
      }
#endif
    }
  }

#if 0
  // render the red circles/dots at the top
  for (TInt i = 0, j = mBoardX; i < VISIBLE_BOARD_COLS; i++, j++) {
    bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_OFF, BOARD_X + i*16, BOARD_Y - 16);
//    if (j & 1) {
//      bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_ON, BOARD_X + i * 16, SCREEN_HEIGHT - 16);
//      bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_ON, BOARD_X + i * 16, BOARD_Y - 16);
//    } else {
//      bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_OFF, BOARD_X + i * 16, SCREEN_HEIGHT - 16);
//      bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_OFF, BOARD_X + i * 16, BOARD_Y - 16);
//    }
  }
#endif
#if 0
  for (TInt i = 0, j = mBoardY; i < VISIBLE_BOARD_ROWS; i++, j++) {
//    if (j & 1) {
//      bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_ON, BOARD_X - 16, BOARD_Y + i * 16);
//      bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_ON, BOARD_X + VISIBLE_BOARD_COLS * 16, BOARD_Y + i * 16);
//    } else {
//      bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_OFF, BOARD_X - 16, BOARD_Y + i * 16);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_BEAT_OFF, BOARD_X + VISIBLE_BOARD_COLS * 16, BOARD_Y + i * 16);
//    }
  }
#endif
  // Score
//  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE, SCREEN_WIDTH - 40 - 8, 8);
//  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE + 1, SCREEN_WIDTH - 40 + 8, 8);
//  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE + 2, SCREEN_WIDTH - 40 + 24, 8);
//  y = 8 + 16;
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE, 8, 0);
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE + 1, 24, 0);
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_SCORE + 2, 40, 0);
  TInt      x = 56;
  for (TInt i = 0; i < 7; i++) {
    TInt v = (mScore.mValue >> ((7 - i) * 4)) & 0x0f;
//    if (v) {
    bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, 0);
//    }
    x += 8;
  }
  TInt      v = mScore.mValue & 0x0f;
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_NUM0 + v, x, 0);

  // render timer
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_TIME, 16, 14);
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_TIME + 1, 16+16, 14);
  bm->DrawFastHLine(gViewPort, BOARD_X+48, BOARD_Y-20, BOARD_COLS * 12, COLOR_TIMERBORDER);
  bm->DrawFastHLine(gViewPort, BOARD_X+48, BOARD_Y-8, BOARD_COLS * 12, COLOR_TIMERBORDER);

  for (TInt y = 0; y<9; y++) {
    bm->DrawFastHLine(gViewPort, BOARD_X+48, BOARD_Y-18+y, BOARD_COLS*12, COLOR_TIMERINNER);
  }

  if (mGameOver) {
    x = BOARD_X + VISIBLE_BOARD_COLS * 16 + 32;
    bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER, x, BOARD_Y);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER + 1, x + 16, BOARD_Y);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER + 2, x + 32, BOARD_Y);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER + 3, x + 48, BOARD_Y);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2, x, BOARD_Y + 16);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2 + 1, x + 16, BOARD_Y + 16);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2 + 2, x + 32, BOARD_Y + 16);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_GAMEOVER2 + 3, x + 48, BOARD_Y + 16);
  }
}

