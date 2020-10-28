
#  ------------ DINGUX UCLIBC STUFF -----------
CHAINPREFIX = ~/ldk/mipsel-linux-uclibc
CROSS_COMPILE = $(CHAINPREFIX)/usr/bin/mipsel-linux
LD_COMMAND = $(CHAINPREFIX)/mipsel-buildroot-linux-uclibc/bin/ld


# ----------- SETUP VARS FOR SOURCES --------------

ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
BUILD_DIR = $(ROOT_DIR)/build/ldk
GAME_SOURCE_DIR = $(ROOT_DIR)/src
LDK_SOURCE_DIR = $(ROOT_DIR)/src/LDK
CREATIVE_ENGINE_PATH = $(ROOT_DIR)/creative-engine
CREATIVE_ENGINE_SOURCE_DIR = $(CREATIVE_ENGINE_PATH)/src


TARGET = $(BUILD_DIR)/modite-adventure.dge

SOURCES = $(shell find ${GAME_SOURCE_DIR} -type f -name '*.cpp')
SOURCES += $(shell find $(CREATIVE_ENGINE_SOURCE_DIR) -type f -name '*.c*')

RESOURCES_BIN = $(GAME_SOURCE_DIR)/Resources.bin
RESOURCES_BIN_O = $(BUILD_DIR)/Resources.bin


$(shell mkdir -p $(BUILD_DIR))


# $(shell ${LD_COMMAND} -r -b binary -o $(RESOURCES_BIN_O) $(RESOURCES_BIN))



INCLUDE = -I $(CREATIVE_ENGINE_SOURCE_DIR) \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/BStore \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/BStore/DesktopStore \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/Audio \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/Audio/mixer \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/Display \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/Display/LDKDisplay \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/Controls \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/Controls/DesktopControls \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/Controls/LDKControls \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/Widgets \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/Types \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/libxmp \
          -I $(CREATIVE_ENGINE_SOURCE_DIR)/libxmp/loaders \
          -I $(GAME_SOURCE_DIR)/CreditsState \
          -I $(GAME_SOURCE_DIR)/GameMenuState \
          -I $(GAME_SOURCE_DIR)/MainOptionsState \
          -I $(GAME_SOURCE_DIR)/SplashState \
          -I $(GAME_SOURCE_DIR)/MainMenuState \
          -I $(GAME_SOURCE_DIR)/GameState \
          -I $(GAME_SOURCE_DIR)/GameState/enemies \
          -I $(GAME_SOURCE_DIR)/GameState/environment \
          -I $(GAME_SOURCE_DIR)/GameState/inventory \
          -I $(GAME_SOURCE_DIR)/GameState/final-boss \
          -I $(GAME_SOURCE_DIR)/GameState/mid-bosses \
          -I $(GAME_SOURCE_DIR)/GameState/wizard \
          -I $(GAME_SOURCE_DIR)/GameState/player \
          -I $(GAME_SOURCE_DIR)/GameState/status \
          -I $(GAME_SOURCE_DIR)/ResetState \
          -I $(GAME_SOURCE_DIR)/MainOptionsState \
          -I $(GAME_SOURCE_DIR)/LoadGameState \
          -I $(GAME_SOURCE_DIR)/DebugMenuState \
          -I $(GAME_SOURCE_DIR)/VictoryState \
          -I $(GAME_SOURCE_DIR)/



CPP_OBJS = $(SOURCES:.cpp=.o)
OBJS += $(CPP_OBJS:.c=.o)


CXX = $(CROSS_COMPILE)-g++
CC  = $(CROSS_COMPILE)-cc
STRIP =  $(CROSS_COMPILE)-strip
RC  =  $(CROSS_COMPILE)-windres

SYSROOT = $(shell $(CC) --print-sysroot)
SDL_CFLAGS = $(shell $(SYSROOT)/usr/bin/sdl-config --cflags)
SDL_LIBS = $(shell $(SYSROOT)/usr/bin/sdl-config --libs)


CFLAGS = $(INCLUDE) -DLIBXMP_CORE_PLAYER -DRC_OPTIMIZED -DGCW_ZERO -D__DINGUX__ -DFOREVER_16_BIT -DLIBXMP_CORE_PLAYER $(SDL_CFLAGS)
CFLAGS += -O3 -fdata-sections -ffunction-sections -mips32 -march=mips32 -mno-mips16 -fomit-frame-pointer -fno-builtin
CFLAGS += -fno-common -Wno-write-strings -Wno-sign-compare -ffast-math -ftree-vectorize
CFLAGS += -funswitch-loops -fno-strict-aliasing
CFLAGS += -DMIPS_XBURST -DFAST_LSB_WORD_ACCESS
CFLAGS += -fprofile-use -fprofile-dir=./profile -DNO_ROM_BROWSER

CXXFLAGS = $(CFLAGS) -std=gnu++14 -fno-exceptions -fno-rtti -fno-math-errno -fno-threadsafe-statics
LDFLAGS = $(SDL_LIBS) -lSDL_mixer -lSDL_image -lSDL_gfx -flto  -s

#test 123

DEPLOY_TMP = /tmp/.modus-ipk/root/home/retrofw/test

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CMD)$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@


ipk: $(TARGET)
	@echo "Packaging..."
	${ROOT_DIR}/scripts/package.sh
.PHONY: ipk


clean:
	#rm -f $(TARGET); find -L . -name "*.o" -exec rm {} \;
	@rm -f $(TARGET); find ${ROOT_DIR} -name "*.o" -exec rm {} \;

.PHONY: clean


cleanall: cleanobjects
	@rm -f $(TARGET);
.PHONY: cleanall


cleanobjects:
	find -L ${ROOT_DIR} -name "*.o" -exec rm {} \;
.PHONY: cleanobjects


rcomp: FORCE
	echo "Building rcomp"
	cd ${CREATIVE_ENGINE_PATH}/tools/rcomp-src && make clean && make -j 4
	rm ${CREATIVE_ENGINE_PATH}/tools/rcomp-src/rcomp

resources: rcomp FORCE
	echo "Compiling resources"
	cd src && ${CREATIVE_ENGINE_PATH}/tools/rcomp Resources.r



reset: FORCE
	echo "Resetting high score table (and options)"
	rm -f ~/.modus

FORCE:
