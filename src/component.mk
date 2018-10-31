.PHONY: Resources.bin
	echo "THERE"
	cd ${CREATIVE_ENGINE_PATH}/tools && make
	${CREATIVE_ENGINE_PATH}/tools/rcomp Resources.r

COMPONENT_NAME = Genus
COMPONENT_PRIV_INCLUDEDIRS=../src/GameState ../src
COMPONENT_EXTRA_INCLUDES=${CREATIVE_ENGINE_PATH}/src ${CREATIVE_ENGINE_PATH}/src/Widgets
COMPONENT_EMBED_FILES := Resources.bin

#WAVFILES = $(shell ls ${PROJECT_PATH}/resources/sound_effects/*.wav)
# $(info    WAVFILES is ${WAVFILES})
#COMPONENT_EMBED_FILES += ${WAVFILES}

#SFXFILES = $(shell ls ${PROJECT_PATH}/resources/music/*.xm)
#COMPONENT_EMBED_FILES += ${SFXFILES}

#$(info COMPONENT_EMBED_FILES is ${COMPONENT_EMBED_FILES})
