# ESP-IDF Makefile for game project
PROJECT_NAME = Genus

GENUS_SRC_PATH = $(abspath ${PROJECT_PATH}/src)


ifndef CREATIVE_ENGINE_PATH
CREATIVE_ENGINE_PATH=$(abspath ${PROJECT_PATH}/../creative-engine)
export CREATIVE_ENGINE_PATH
endif


EXTRA_COMPONENT_DIRS = \
  ${CREATIVE_ENGINE_PATH} \
  ${GENUS_SRC_PATH}

COMPONENT_ADD_INCLUDEDIRS = ${EXTRA_COMPONENT_DIRS}

# Speed up compilation by removing components we don't use. 
# It shaved about 20 seconds from fresh builds (6 core i7 8700k)
#EXCLUDE_COMPONENTS := asio fatfs json libsodium secure_boot idf_test bt mqtt   \
#	esp_http_server  esp_https_ota esp_https_server sdmmc protocomm \
#	wear_leveling


# Let's keep this ABOVE the COMPONENT_DIRS var modification.
include $(IDF_PATH)/make/project.mk

# We're not supposed to write to this variable, but for now, let's keep this as/is.
COMPONENT_DIRS := ${EXTRA_COMPONENT_DIRS}


release: FORCE
	./scripts/build.sh docker-build && cp ./build/Genus.tgz ~/Downloads/

rcomp: FORCE
	echo "Building rcomp"
	cd ${CREATIVE_ENGINE_PATH}/tools && make

resources: rcomp FORCE
	echo "Compiling resources"
	cd src && ${CREATIVE_ENGINE_PATH}/tools/rcomp Resources.r

reset: FORCE
	echo "Resetting high score table (and options)"
	 rm -f cmake-build-debug/Genus.app/Contents/MacOS/*.store

FORCE:


