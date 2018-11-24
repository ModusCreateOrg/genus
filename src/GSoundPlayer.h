//
// Created by Jesus Garcia on 10/2/18.
//
#ifndef GSOUNDPLAYER_H
#define GSOUNDPLAYER_H

#include "BSoundPlayer.h"

#include "Resources.h"


class GSoundPlayer : public BSoundPlayer {



public:
  void Init(TUint8 aNumberFxChannels, TUint8 aNumberFxSlots);

  TBool LoadSongSlot(TInt16 aResourceId) override;
  TBool LoadEffects() override;
  BRaw* LoadEffectResource(TUint16 aResourceId, TInt16 aSlotNumber) override;
  TBool PlayMusic(TInt16 aResourceId);

  // SFX Methods //
  void SfxGoodDrop();
  void SfxRotateRight();
  void SfxRotateLeft();
  void SfxBadDrop();
  void SfxCombo();
  void SfxMoveBlock();
  void SfxExplodeBlock();
  void SfxOptionSelect();
};


extern GSoundPlayer gSoundPlayer;

#endif //GSOUNDPLAYER_H
