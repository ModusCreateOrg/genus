#ifndef GRESOURCES_H
#define GRESOURCES_H

#include <BTypes.h>
#include "Resources.h"

// RESOURVE MANAGER

// BBitmap Slots
enum {
  BKG_SLOT,
  BKG2_SLOT,
  BKG3_SLOT,
  BKG4_SLOT,
  BKG5_SLOT,
  BKG6_SLOT,

  PLAYER_SLOT,
  COMMON_SLOT,
// Font Slots
  FONT_8x8_SLOT,
  FONT_16x16_SLOT,
};

// BRaw slots
enum {
  SONG_SLOT,
  SFX1_SLOT,
  SFX2_SLOT,
  SFX3_SLOT,
  SFX4_SLOT,
  SFX5_SLOT,
  SFX6_SLOT,
  SFX7_SLOT,
};

// image numbers on sprite sheets
static const TUint16 IMG_BLOCK1 = 0;
static const TUint16 IMG_BLOCK2 = 1;
static const TUint16 IMG_BLOCK3 = 2;
static const TUint16 IMG_BLOCK4 = 3;

static const TUint16 IMG_BGTILE1 = 6;
static const TUint16 IMG_BGTILE2 = 7;

static const TUint16 IMG_BLOCK1x = 8;
static const TUint16 IMG_BLOCK2x = 9;
static const TUint16 IMG_BLOCK3x = 10;
static const TUint16 IMG_BLOCK4x = 11;

static const TUint16 IMG_GAMEOVER  = 16;
static const TUint16 IMG_GAMEOVER2 = 24;

static const TUint16 IMG_BEAT_OFF = 48;
static const TUint16 IMG_BEAT_ON  = 49;

static const TUint16 IMG_FRAMEL = 56;
static const TUint16 IMG_FRAMER = 57;

static const TUint16 IMG_NUM0  = 64;
static const TUint16 IMG_NUM1  = 65;
static const TUint16 IMG_NUM2  = 66;
static const TUint16 IMG_NUM3  = 67;
static const TUint16 IMG_NUM4  = 68;
static const TUint16 IMG_NUM5  = 69;
static const TUint16 IMG_NUM6  = 70;
static const TUint16 IMG_NUM7  = 71;
static const TUint16 IMG_NUM8  = 72;
static const TUint16 IMG_NUM9  = 73;
static const TUint16 IMG_TIME  = 74; // time is 32 wide
static const TUint16 IMG_SCORE = 76; // score is 48 wide
static const TUint16 IMG_LEVEL = 80; // LEVEL is 32 wide

// COLOR PALETTE INDEXES
static const TUint8 COLOR_BORDER1 = 153;
static const TUint8 COLOR_BORDER2 = 155;

static const TUint8 COLOR_TIMERINNER  = 250;
static const TUint8 COLOR_TIMERBORDER = 251;

// user interface/widgets colors
static const TUint8 COLOR_DIALOG_BG   = 249;
static const TUint8 COLOR_DIALOG_FG   = 250;
static const TUint8 COLOR_MENU_TITLE  = 251;
static const TUint8 COLOR_TEXT        = 252;
static const TUint8 COLOR_TEXT_SHADOW = 253;
static const TUint8 COLOR_TEXT_BG     = 254;
static const TUint8 COLOR_GAMEOVER    = 255;

#endif //GRESOURCES_H
