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
// SPRITES.BMP
static const TUint16 IMG_TILE1 = 0;   // pink
static const TUint16 IMG_TILE2 = 16;   // green

static const TUint16 IMG_BGTILE1 = 6; // this is the grid background tile
static const TUint16 IMG_FRAMEL  = 14;
static const TUint16 IMG_FRAMER  = 15;

// COMMON.BMP
static const TUint16 IMG_POWERUP_MODUS_BOMB = 16;  // m bomb
static const TUint16 IMG_POWERUP_COLORSWAP  = 24;

// SPLASH_SPRITES.BMP
static const TUint16 IMG_DROP1 = 0;
static const TUint16 IMG_DROP2 = 4;
static const TUint16 IMG_DROP3 = 8;
static const TUint16 IMG_DROP4 = 16;
static const TUint16 IMG_DROP5 = 24;
static const TUint16 IMG_DROP6 = 32;

// COLOR PALETTE INDEXES
static const TUint8 COLOR_BORDER1 = 153;
static const TUint8 COLOR_BORDER2 = 155;

static const TUint8 COLOR_TIMER_INNER  = 250;
static const TUint8 COLOR_TIMER_BORDER = 251;

// user interface/widgets colors
static const TUint8 COLOR_DIALOG_BG   = 249;
static const TUint8 COLOR_DIALOG_FG   = 250;
static const TUint8 COLOR_MENU_TITLE  = 251;
static const TUint8 COLOR_TEXT        = 252;
static const TUint8 COLOR_TEXT_SHADOW = 253;
static const TUint8 COLOR_TEXT_BG     = 254;
static const TUint8 COLOR_GAMEOVER    = 255;

#endif //GRESOURCES_H
