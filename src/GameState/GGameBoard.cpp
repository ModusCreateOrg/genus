#include "Game.h"
#include "GGameBoard.h"

// options
// comment out the undefs to enable the option
#define RENDER_GRID
//#undef RENDER_GRID
#define RENDER_CHECKERBOARD
//#undef RENDER_CHECKERBOARD

GGameBoard::GGameBoard() {
  mBoardX = mBoardY = 0;

  Clear();
}

void GGameBoard::Clear() {
  for (TInt row = 0; row < BOARD_ROWS; row++) {
    for (TInt col = 0; col < BOARD_COLS; col++) {
      mBoard[row][col] = 255;
    }
  }
}

TUint32 GGameBoard::CountScore() {
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
  return accumulated_score;
}

void GGameBoard::Render(TInt aX, TInt aY) {
  // render the board
  TInt      y   = aY;
  for (TInt row = 0; row < VISIBLE_BOARD_ROWS; row++) {
    TInt      x   = aX;
    for (TInt col = 0; col < VISIBLE_BOARD_COLS; col++) {
      TUint8 v = mBoard[mBoardY + row][mBoardX + col];
      if (v != 255) {
        BSprite::DrawSprite(gViewPort, PLAYER_SLOT, v, x + col * 16, y + row * 16);
      }
#ifdef RENDER_CHECKERBOARD
      else {
        BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_BGTILE1, x + col * 16, y + row * 16);
      }
#endif
    }
  }
#ifdef RENDER_CHECKERBOARD
  // render border
  BBitmap *bm = gDisplay.renderBitmap;

  bm->DrawRect(ENull, aX - 1, aY - 1, aX + BOARD_COLS * 16 + 1, aY + BOARD_ROWS * 16 + 1, COLOR_BORDER2);
  bm->DrawRect(ENull, aX - 2, aY - 2, aX + BOARD_COLS * 16 , aY + BOARD_ROWS * 16, COLOR_BORDER1);
#endif
}

// mark a block as matched (e.g. turn from blue/pink to blue/pink with black center
// returns EFalse if the block was already black center
TBool GGameBoard::Mark(TInt aRow, TInt aCol) {
  TUint8 v = mBoard[aRow][aCol];
  mBoard[aRow][aCol] |= 8;
  return mBoard[aRow][aCol] != v;
}

TBool GGameBoard::Combine() {
  TUint8 quad[4];
  TBool  new_combination = EFalse;

  for (TInt row = 0; row < BOARD_ROWS - 1; row++) {
    for (TInt col = 0; col < BOARD_COLS - 1; col++) {
      if (!GetQuad(row, col, quad)) {
        continue;
      }
      if (quad[0] > 1 || quad[1] > 1 || quad[2] > 1 || quad[3] > 1) {
        continue;
      }

      if (Mark(row, col) | Mark(row, col + 1) | Mark(row + 1, col) | Mark(row + 1, col + 1)) {
        new_combination = ETrue;
      }
      // look right
      for (TInt right  = col + 1; right < BOARD_COLS; right++) {
        if (!GetQuad(row, right, quad)) {
          break;
        }
        if (Mark(row, right) | Mark(row + 1, right)) {
          new_combination = ETrue;
        }
      }
      // look down
      for (TInt bottom = row + 1; bottom < BOARD_ROWS; bottom++) {
        if (!GetQuad(bottom, col, quad)) {
          break;
        }
        if (Mark(bottom, col) | Mark(bottom + 1, col)) {
          new_combination = ETrue;
        }
      }
    }
  }
  return new_combination;
}

TBool GGameBoard::IsGameOver() {
  for (TInt row = 0; row < BOARD_ROWS - 1; row++) {
    for (TInt col = 0; col < BOARD_COLS - 1; col++) {
      if (mBoard[row][col] == 255 && mBoard[row][col + 1] == 255 && mBoard[row + 1][col] == 255 &&
          mBoard[row + 1][col + 1] == 255) {
        return EFalse;
      }
    }
  }
  return ETrue;
}


