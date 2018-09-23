.PHONY: Resources.bin
	echo "THERE"
	cd ../creative-engine/tools && make
	../creative-engine/tools/rcomp Resources.r

COMPONENT_NAME = Genus

#ADD_COMPONENT_INCLUDEDIRS=./src ./src/foo
COMPONENT_ADD_INCLUDEDIRS=src 
#ADD_COMPONENT_INCLUDEDIRS=foo
COMPONENT_PRIV_INCLUDEDIRS=../creative-engine/src
#COMPONENT_SRCDIRS:=./creative-engine/src .

COMPONENT_EMBED_FILES := Resources.bin


WAVFILES = $(shell ls ${PROJECT_PATH}/resources/sound_effects/*.wav)
# $(info    WAVFILES is ${WAVFILES})
COMPONENT_EMBED_FILES += ${WAVFILES}

SFXFILES = $(shell ls ${PROJECT_PATH}/resources/music/*.xm)
COMPONENT_EMBED_FILES += ${SFXFILES}

$(info COMPONENT_EMBED_FILES is ${COMPONENT_EMBED_FILES})
