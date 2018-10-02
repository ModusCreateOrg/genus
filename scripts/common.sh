#!/usr/bin/env bash

######################### Function definitions ########################

SUDO=${SUDO:-}

function ensure_xcode_installed {
    #Ensure XCode full version is installed and configured, 
    #as xcodebuild gets invoked later in the build, and it will fail otherwise
    if [[ -z "$(which xcodebuild)" ]] || ! xcodebuild --help >/dev/null 2>&1; then
        cat 1>&2 <<EOF
Please install XCode from the App Store.
You will need the full version, not just the command line tools.
If you already have XCode installed, you may need to issue this command
to let the tools find the right developer directory:
    "$SUDO" xcode-select -r
See https://github.com/nodejs/node-gyp/issues/569
EOF
        exit 1
    fi
}

function ensure_homebrew_installed {
    #Ensure homebrew is installed
    if [[ -z "$(which brew)" ]]; then
      echo "No homebrew found - installing Homebrew from https://brew.sh"
      /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    fi
}

function ensure_debian_devtools_installed {
    $SUDO apt-get -qq update
    $SUDO apt-get -qq install build-essential git cmake libsdl2-dev libsdl2-image-dev
}

function ensure_arch_devtools_installed {
    $SUDO pacman -Sqyyu --noconfirm base-devel libglvnd sdl2 sdl2_image cmake
}

function ensure_creative_engine {
    if [[ ! -d "$CREATIVE_ENGINE_DIR" ]]; then
        git clone https://github.com/ModusCreateOrg/creative-engine.git "$CREATIVE_ENGINE_DIR"
    fi
}

function build {
    cd "$BASE_DIR" || exit 1
    rm -f creative-engine
    ln -s ../creative-engine . 
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR" || exit 1
    cmake ..
    make
}

function clean {
    cd "$CREATIVE_ENGINE_DIR" || exit 1
    git clean -fdx
    rm -rf "$BASE_DIR/build"
}

