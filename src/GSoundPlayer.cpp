//
// Created by Jesus Garcia on 10/2/18.
//

#include "GSoundPlayer.h"
#include "GResources.h"

#define DISABLE_AUDIO
#undef DISABLE_AUDIO


GSoundPlayer gSoundPlayer;

void GSoundPlayer::Init(TUint8 aNumberFxChannels, TUint8 aNumberFxSlots) {

  BSoundPlayer::Init(aNumberFxChannels, aNumberFxSlots);

  PlayMusic(EMPTYSONG_XM);
}


TBool GSoundPlayer::LoadSongSlot(TInt16 aResourceId) {


  gResourceManager.ReleaseRawSlot(SONG_SLOT);

  gResourceManager.LoadRaw(aResourceId, SONG_SLOT);
  BRaw *song = gResourceManager.GetRaw(SONG_SLOT);

  return LoadSong(song);
}

TBool GSoundPlayer::LoadEffects() {
  // Load effects
  const uint16_t mEffectsList[] = {
    SFX_GOOD_DROP_BLOCK_WAV,
    SFX_BAD_DROP_BLOCK_WAV,
    SFX_MOVE_BLOCK_WAV,
    SFX_ROTATE_BLOCK_LEFT_WAV,
    SFX_ROTATE_BLOCK_RIGHT_WAV,
    SFX_SCORE_COMBO_WAV
  };

  for (uint8_t i = 0; i < 6; i++) {
//    printf("loadEffect(%i)\n", i);
    LoadEffect(mEffectsList[i], i);
  }
  return ETrue;
}

BRaw *GSoundPlayer::LoadEffectResource(TUint16 aResourceId, TInt16 aSlotNumber) {
  gResourceManager.LoadRaw(aResourceId, SFX1_SLOT + aSlotNumber);
  return gResourceManager.GetRaw(SFX1_SLOT + aSlotNumber);
}