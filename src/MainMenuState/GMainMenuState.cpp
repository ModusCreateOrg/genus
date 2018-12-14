#include "Game.h"
#include "GMainMenuProcess.h"
#include "GMainMenuPlayfield.h"

GMainMenuState::GMainMenuState() : BGameEngine(gViewPort) {
  mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
  mPlayfield = new GMainMenuPlayfield();
  auto *p = new GMainMenuProcess();

  AddProcess(p);

  gWidgetTheme.Configure(
      WIDGET_TEXT_BG, COLOR_TEXT_BG,
      WIDGET_TITLE_FONT, mFont16,
      WIDGET_TITLE_FG, COLOR_TEXT,
      WIDGET_TITLE_BG, -1,
      WIDGET_WINDOW_BG, gDisplay.renderBitmap->TransparentColor(),
      WIDGET_WINDOW_FG, gDisplay.renderBitmap->TransparentColor(),
      WIDGET_END_TAG);

  gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
  gDisplay.SetColor(COLOR_TEXT_BG, 255, 92, 93);
  gSoundPlayer.PlayMusic(MAIN_MENU_XM);

}

GMainMenuState::~GMainMenuState() {
  delete mPlayfield;
  delete mFont16;
  mPlayfield = ENull;
}

