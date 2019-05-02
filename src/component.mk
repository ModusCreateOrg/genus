.PHONY: Resources.bin
	echo "THERE"
	cd ${CREATIVE_ENGINE_PATH}/tools && make
	${CREATIVE_ENGINE_PATH}/tools/rcomp Resources.r

COMPONENT_NAME = Genus

COMPONENT_EMBED_FILES := Resources.bin

#$(info COMPONENT_EMBED_FILES is ${COMPONENT_EMBED_FILES})
