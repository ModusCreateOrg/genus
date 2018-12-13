//
// Created by Jesus Garcia on 10/2/18.
//

#include "Game.h"
#include "GSoundPlayer.h"
#include "GResources.h"
#include "Memory.h"

#define DISABLE_AUDIO
#undef DISABLE_AUDIO


GSoundPlayer gSoundPlayer;


void GSoundPlayer::Init(TUint8 aNumberFxChannels, TUint8 aNumberFxSlots) {
  BSoundPlayer::Init(aNumberFxChannels, aNumberFxSlots);

  mMaxSongs = 9;
  mSongSlots = (SongSlot *)AllocMem(sizeof(SongSlot) * mMaxSongs, MEMF_SLOW);

  const uint16_t allSongs[] = {
    EMPTYSONG_XM,
    UNDER_WATER_XM,
    CYBERPUNK_XM,
    COUNTRYSIDE_XM,
    MAIN_MENU_XM,
    SPAAACE_XM,
    GLACIAL_MOUNTAINS_XM,
    GAMEOVER_XM,
    UNDERWATERFANTASY_XM
  };

  for (uint8_t i = 0; i < mMaxSongs; i++) {
    auto *slot = (SongSlot *)AllocMem(sizeof(SongSlot), MEMF_SLOW);

    slot->mResourceNumber = allSongs[i];
    slot->mSlotNumber = SONG0_SLOT + i;

    gResourceManager.LoadRaw(allSongs[i], slot->mSlotNumber);
    slot->mRaw = gResourceManager.GetRaw(slot->mSlotNumber);

    mSongSlots[i] = *slot;
    FreeMem(slot);
  }


  PlayMusic(EMPTYSONG_XM);
  SetMusicVolume(gOptions->music);
  SetEffectsVolume(gOptions->sfx);
  MuteMusic(gOptions->muted);
}

TBool GSoundPlayer::PlayMusic(TInt16 aResourceId) {
  TBool music = BSoundPlayer::PlayMusic(aResourceId);
//  MuteMusic(gOptions->muted);
  return music;
}

TBool GSoundPlayer::LoadSongSlot(TInt16 aResourceId) {

  for (TUint8 i = 0; i < mMaxSongs; i++) {
    if (mSongSlots[i].mResourceNumber == aResourceId) {
      return LoadSong(mSongSlots[i].mRaw);
    }
  }

  printf("WARNING :: Could not find song %i\n", aResourceId);

  return false;
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
    SFX_EXPLODE_BLOCK_WAV,
    SFX_NEXT_LEVEL_WAV
  };

  for (uint8_t i = 0; i < 9; i++) {
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
void GSoundPlayer::SfxNextStage() {
  gSoundPlayer.PlaySfx(/*SFX_NEXT_LEVEL*/8);
}
