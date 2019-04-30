.PHONY: Resources.bin
	echo "THERE"
	cd ${CREATIVE_ENGINE_PATH}/tools && make
	${CREATIVE_ENGINE_PATH}/tools/rcomp Resources.r

COMPONENT_NAME = Genus
COMPONENT_EXTRA_INCLUDES=${CREATIVE_ENGINE_PATH}/src \
    ${CREATIVE_ENGINE_PATH}/src/Display \
    ${CREATIVE_ENGINE_PATH}/src/Widgets \
    ${PROJECT_PATH}/src/GameState \
    ${PROJECT_PATH}/src/GameState/Powerups \
    ${PROJECT_PATH}/src


COMPONENT_EMBED_FILES := Resources.bin

#$(info COMPONENT_EMBED_FILES is ${COMPONENT_EMBED_FILES})
