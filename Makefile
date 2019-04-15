# ESP-IDF Makefile for game project
PROJECT_NAME=Genus

GENUS_SRC_PATH=${PROJECT_PATH}/src
ifndef CREATIVE_ENGINE_PATH
CREATIVE_ENGINE_PATH=$(abspath ${PROJECT_PATH}/../creative-engine)
export CREATIVE_ENGINE_PATH
endif

GENUS_STATES=$(GENUS_SRC_PATH)/GameState
GENUS_STATES+=$(GENUS_SRC_PATH)/HighScoreState
GENUS_STATES+=$(GENUS_SRC_PATH)/MainOptionsState
GENUS_STATES+=$(GENUS_SRC_PATH)/SplashState
GENUS_STATES+=$(GENUS_SRC_PATH)/CreditsState
GENUS_STATES+=$(GENUS_SRC_PATH)/MainMenuState
GENUS_STATES+=$(GENUS_SRC_PATH)/GameOverState
GENUS_STATES+=$(GENUS_SRC_PATH)/HighScoresState
GENUS_STATES+=$(GENUS_SRC_PATH)/RulesState

GENUS_POWERUPS=$(GENUS_SRC_PATH)/GameState/Powerups
GENUS_PAUSE=$(GENUS_SRC_PATH)/GameState/PauseModal
GENUS_PLAYFIELDS=$(GENUS_SRC_PATH)/GameState/Playfields

EXTRA_COMPONENT_DIRS=${CREATIVE_ENGINE_PATH} ${PROJECT_PATH}/src $(GENUS_STATES) $(GENUS_POWERUPS) $(GENUS_PAUSE) $(GENUS_PLAYFIELDS)

include $(IDF_PATH)/make/project.mk

# Temporary until RCOMP is folded into the music/sfx workflow
gen_sound_headers: gen_music_headers gen_sfx_headers FORCE

gen_music_headers:
	echo "Generating music headers"
	cd resources/music && ./gen_header.sh

gen_sfx_headers:
	echo "Generating sound effects headers"
	cd resources/sound_effects && ./gen_header.sh

release: FORCE
	./scripts/build.sh && cp ./build/genus.tgz ~/Downloads/

rcomp: FORCE
	echo "Building rcomp"
	cd ${CREATIVE_ENGINE_PATH}/tools && make

resources: rcomp FORCE
	echo "Compiling resources"
	cd src && ${CREATIVE_ENGINE_PATH}/tools/rcomp Resources.r

reset: FORCE
	echo "Resetting high score table (and options)"
	 rm -f cmake-build-debug/genus.app/Contents/MacOS/*.store

FORCE:


