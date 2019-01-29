# Makefile with autodependencies and separate output directories
# - $BUILDDIR/ is used for object and other build files
# - $BINDIR/ is used for native binaries
# - assets/ is used for assets needed when running native binaries
# - $WWWDIR/ is used for emscripten output
#
# For native (Mac OS X) builds, $(BINDIR)/ and assets/ are needed
# For emscripten builds, $(WWWDIR)/ is needed

#MODULES = main glwrappers window atlas font render-sprites render-shapes render-surface render-imgui imgui/imgui imgui/imgui_draw imgui/imgui_widgets imgui/imgui_demo
#ASSETS = assets/red-blob.png imgui/misc/fonts/DroidSans.ttf

ASSETS = src/Resources.bin

MODULES = \
src/GDialogWidget \
src/GGame \
src/GSoundPlayer \
src/TOptions \
src/main \
creative-engine/src/Audio \
creative-engine/src/BAnimSprite \
creative-engine/src/BApplication \
creative-engine/src/BBase \
creative-engine/src/BBitmap \
creative-engine/src/BFont \
creative-engine/src/BGameEngine \
creative-engine/src/BList \
creative-engine/src/BPlayfield \
creative-engine/src/BProcess \
creative-engine/src/BResourceManager \
creative-engine/src/BSoundPlayer \
creative-engine/src/BSprite \
creative-engine/src/BStore \
creative-engine/src/BTypes \
creative-engine/src/BViewPort \
creative-engine/src/Controls \
creative-engine/src/Display \
creative-engine/src/Memory \
creative-engine/src/Panic \
src/CreditsState/GCreditsState \
src/GameOverState/GGameOverHighScoreAnimationProcess \
src/GameOverState/GGameOverPlayfield \
src/GameOverState/GGameOverProcess \
src/GameOverState/GGameOverState \
src/GameState/GGameBoard \
src/GameState/GGameState \
src/GameState/GGameStateGameOverProcess \
src/GameState/GPlayerSprite \
src/HighScoresState/GHighScoreAnimationProcess \
src/HighScoresState/GHighScoreMessageProcess \
src/HighScoresState/GHighScoresState \
src/HighScoresState/THighScoreTable \
src/MainMenuState/GCreditsWidget \
src/MainMenuState/GMainMenuContainer \
src/MainMenuState/GMainMenuPlayfield \
src/MainMenuState/GMainMenuProcess \
src/MainMenuState/GMainMenuState \
src/MainMenuState/GOptionsWidget \
src/MainMenuState/GRulesWidget \
src/MainMenuState/GStartWidget \
src/MainOptionsState/GBrightnessWidget \
src/MainOptionsState/GCancelResetWidget \
src/MainOptionsState/GDifficultyWidget \
src/MainOptionsState/GExitWidget \
src/MainOptionsState/GMainOptionsState \
src/MainOptionsState/GMusicWidget \
src/MainOptionsState/GResetAllWidget \
src/MainOptionsState/GResetHighScoresWidget \
src/MainOptionsState/GResetOptionsState \
src/MainOptionsState/GResetOptionsWidget \
src/MainOptionsState/GResetWidget \
src/MainOptionsState/GSfxWidget \
src/MainOptionsState/GSoundSliderWidget \
src/RulesState/GRulesState \
src/SplashState/GDropProcess \
src/SplashState/GSplashPlayfield \
src/SplashState/GSplashProcess \
src/SplashState/GSplashState \
creative-engine/src/Types/TBCD \
creative-engine/src/Types/TRect \
creative-engine/src/Widgets/BButtonWidget \
creative-engine/src/Widgets/BContainerWidget \
creative-engine/src/Widgets/BDialogWidget \
creative-engine/src/Widgets/BMenuWidget \
creative-engine/src/Widgets/BNumberWidget \
creative-engine/src/Widgets/BSelectWidget \
creative-engine/src/Widgets/BSliderWidget \
creative-engine/src/Widgets/BWidget \
creative-engine/src/Widgets/BWidgetTheme \
src/GameState/Playfields/GLevelCountryside \
src/GameState/Playfields/GLevelCyberpunk \
src/GameState/Playfields/GLevelGlacialMountains \
src/GameState/Playfields/GLevelSpace \
src/GameState/Playfields/GLevelUnderWaterFantasy \
src/GameState/Playfields/GLevelUnderWaterOne \
src/GameState/Playfields/GScrollingLevel \
src/GameState/Powerups/BPowerup \
src/GameState/Powerups/GColorSwapPowerup \
src/GameState/Powerups/GModusBombPowerup \
src/GameState/Powerups/GNoPowerup \
creative-engine/src/libxmp/control \
creative-engine/src/libxmp/dataio \
creative-engine/src/libxmp/effects \
creative-engine/src/libxmp/filter \
creative-engine/src/libxmp/format \
creative-engine/src/libxmp/hio \
creative-engine/src/libxmp/lfo \
creative-engine/src/libxmp/load \
creative-engine/src/libxmp/load_helpers \
creative-engine/src/libxmp/md5 \
creative-engine/src/libxmp/memio \
creative-engine/src/libxmp/mix_all \
creative-engine/src/libxmp/mix_paula \
creative-engine/src/libxmp/mixer \
creative-engine/src/libxmp/period \
creative-engine/src/libxmp/player \
creative-engine/src/libxmp/read_event \
creative-engine/src/libxmp/scan \
creative-engine/src/libxmp/smix \
creative-engine/src/libxmp/tempfile \
creative-engine/src/libxmp/virtual \
creative-engine/src/libxmp/loaders/asif \
creative-engine/src/libxmp/loaders/common \
creative-engine/src/libxmp/loaders/iff \
creative-engine/src/libxmp/loaders/it_load \
creative-engine/src/libxmp/loaders/itsex \
creative-engine/src/libxmp/loaders/mod_load \
creative-engine/src/libxmp/loaders/s3m_load \
creative-engine/src/libxmp/loaders/sample \
creative-engine/src/libxmp/loaders/voltable \
creative-engine/src/libxmp/loaders/xm_load \

#creative-engine/src/libxmp/fnmatch \
#creative-engine/src/libxmp/mkstemp \


UNAME = $(shell uname -s)
BUILDDIR = build
BINDIR = bin
WWWDIR = www
_MKDIRS := $(shell mkdir -p $(BINDIR) $(WWWDIR) $(BUILDDIR))

COMMONFLAGS = -std=c++11 -MMD -MP
LOCALFLAGS = -g -O2 $(COMMONFLAGS)

# Choose the warnings I want, and disable when compiling third party code
NOWARNDIRS = imgui/ stb/
LOCALWARN = -Wall -Wextra -pedantic -Wpointer-arith -Wshadow -Wfloat-conversion -Wfloat-equal -Wno-unused-function -Wno-unused-parameter
# TODO: why doesn't $(NOWARNDIRS:%=--system-header-prefix=%) help? I
# instead put pragmas into the cpp files that include the offending
# headers.
# NOTE: also useful but noisy -Wconversion -Wshorten-64-to-32

LOCALLIBS = $(shell sdl2-config --libs) -lSDL2_image
ifeq ($(UNAME),Darwin)
	LOCALLIBS += -Wl,-dead_strip -framework OpenGL
else
	LOCALLIBS += -lGL
endif

EMXX = em++
EMXXFLAGS = $(COMMONFLAGS) -Oz -s USE_SDL=2 --use-preload-plugins -s USE_SDL_IMAGE=2 -s WASM=1 \
 -I src \
 -I creative-engine/src \
 -I src/CreditsState \
 -I src/GameOverState \
 -I src/GameState \
 -I src/HighScoresState \
 -I src/MainMenuState \
 -I src/MainOptionsState \
 -I src/RulesState \
 -I src/SplashState \
 -I creative-engine/src/Types \
 -I creative-engine/src/Widgets \
 -I src/GameState/Playfields \
 -I src/GameState/Powerups \
 -I creative-engine/src/libxmp \
 -I creative-engine/src/libxmp/loaders

EMCC = emcc
EMCCFLAGS = -DLIBXMP_CORE_PLAYER -Oz -s USE_SDL=2 --use-preload-plugins -s USE_SDL_IMAGE=2 -s WASM=1 \
 -I creative-engine/src/libxmp \
 -I creative-engine/src/libxmp/loaders

# -s SAFE_HEAP=1 -s ASSERTIONS=2 --profiling  -s DEMANGLE_SUPPORT=1
EMXXLINK = -s TOTAL_MEMORY=50331648

all: $(BINDIR)/main

$(WWWDIR): $(WWWDIR)/index.html $(WWWDIR)/_main.js

$(BINDIR)/main: $(MODULES:%=$(BUILDDIR)/%.o) Makefile
	$(CXX) $(LOCALFLAGS) $(filter %.o,$^) $(LOCALLIBS) -o $@

$(WWWDIR)/index.html: emscripten-shell.html
	cp emscripten-shell.html $(dir $@)index.html

$(WWWDIR)/_main.js: $(MODULES:%=$(BUILDDIR)/%.em.o) $(ASSETS) Makefile
	$(EMXX) $(EMXXFLAGS) $(EMXXLINK) $(filter %.o,$^) $(ASSETS:%=--preload-file %) -o $@

$(BUILDDIR)/%.em.o: %.cpp Makefile-www.mk
	@mkdir -p $(dir $@)
	@echo $(EMXX) -c $< -o $@
	@$(EMXX) $(EMXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.em.o: %.c Makefile-www.mk
	@mkdir -p $(dir $@)
	@echo $(EMCC) -c $< -o $@
	@$(EMCC) $(EMCCFLAGS) -c $< -o $@

# The $(if ...) uses my warning flags only in WARNDIRS
$(BUILDDIR)/%.o: %.cpp Makefile-www.mk
	@mkdir -p $(dir $@)
	@echo $(CXX) -c $< -o $@
	@$(CXX) $(LOCALFLAGS) $(if $(filter-out $(NOWARNDIRS),$(dir $<)),$(LOCALWARN)) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)/* $(BINDIR)/* $(WWWDIR)/*

include $(shell find $(BUILDDIR) -name \*.d)
