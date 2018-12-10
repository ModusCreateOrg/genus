//
// Created by Jesus Garcia on 10/2/18.
//

#include "Game.h"
#include "GSoundPlayer.h"
#include "GResources.h"

#define DISABLE_AUDIO
#undef DISABLE_AUDIO


GSoundPlayer gSoundPlayer;

void GSoundPlayer::Init(TUint8 aNumberFxChannels, TUint8 aNumberFxSlots) {
  BSoundPlayer::Init(aNumberFxChannels, aNumberFxSlots);

  PlayMusic(EMPTYSONG_XM);
  SetMusicVolume(gOptions->music);
  SetEffectsVolume(gOptions->sfx);
  MuteMusic(gOptions->muted);
}

TBool GSoundPlayer::PlayMusic(TInt16 aResourceId) {
  TBool music = BSoundPlayer::PlayMusic(aResourceId);
  MuteMusic(gOptions->muted);
  return music;
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
    SFX_SCORE_COMBO_WAV,
    SFX_OPTION_SELECT_WAV,
    SFX_EXPLODE_BLOCK_WAV
  };

  for (uint8_t i = 0; i < 8; i++) {
    LoadEffect(mEffectsList[i], i);
  }
  return ETrue;
}

BRaw *GSoundPlayer::LoadEffectResource(TUint16 aResourceId, TInt16 aSlotNumber) {
  gResourceManager.LoadRaw(aResourceId, SFX1_SLOT + aSlotNumber);
  return gResourceManager.GetRaw(SFX1_SLOT + aSlotNumber);
}



void GSoundPlayer::SfxGoodDrop() {
  PlaySfx(/*SFX_GOOD_DROP_BLOCK_WAV*/0);
}

void GSoundPlayer::SfxRotateRight() {
  PlaySfx(/*SFX_ROTATE_BLOCK_RIGHT_WAV*/4);
}

void GSoundPlayer::SfxRotateLeft() {
  PlaySfx(/*SFX_ROTATE_BLOCK_LEFT_WAV*/3);
}

void GSoundPlayer::SfxBadDrop() {
  gSoundPlayer.PlaySfx(/*SFX_BAD_DROP_BLOCK_WAV*/1);
}

void GSoundPlayer::SfxCombo() {
  PlaySfx(/*SFX_SCORE_COMBO_WAV*/5);
}

void GSoundPlayer::SfxMoveBlock() {
  PlaySfx(/*SFX_GOOD_DROP_BLOCK_WAV*/2);
}

void GSoundPlayer::SfxExplodeBlock() {
  PlaySfx(/*SFX_EXPLODE_BLOCK_WAV*/7);
}

void GSoundPlayer::SfxOptionSelect() {
  PlaySfx(/*SFX_OPTION_SELECT_WAV*/6);
}

void GSoundPlayer::SfxMenuNavUp() {
  PlaySfx(/*SFX_ROTATE_BLOCK_LEFT_WAV*/3);
}

void GSoundPlayer::SfxMenuNavDown() {
  PlaySfx(/*SFX_ROTATE_BLOCK_RIGHT_WAV*/4);
}

void GSoundPlayer::SfxMenuAccept() {
  gSoundPlayer.PlaySfx(/*SFX_BAD_DROP_BLOCK_WAV*/1);
}

void GSoundPlayer::SfxMenuCancel() {
  gSoundPlayer.PlaySfx(/*SFX_GOOD_DROP_BLOCK_WAV*/0);
}
