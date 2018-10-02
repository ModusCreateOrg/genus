#!/usr/bin/env bash

######################### Debugging and Directory Scaffolding #########

# Set bash unofficial strict mode http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail
IFS=$'\n\t'

# Enable for enhanced debugging
#set -vx

# Credit to https://stackoverflow.com/a/17805088
# and http://wiki.bash-hackers.org/scripting/debuggingtips
export PS4='+(${BASH_SOURCE}:${LINENO}): ${FUNCNAME[0]:+${FUNCNAME[0]}(): }'

# Credit to Stack Overflow questioner Jiarro and answerer Dave Dopson
# http://stackoverflow.com/questions/59895/can-a-bash-script-tell-what-directory-its-stored-in
# http://stackoverflow.com/a/246128/424301
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BASE_DIR="$DIR/.."
BUILD_DIR="$BASE_DIR/build"
TOP_DIR="$BASE_DIR/.."
CREATIVE_ENGINE_DIR="$TOP_DIR/creative-engine"

######################### Function definitions ########################

function ensure_xcode_installed {
    #Ensure XCode full version is installed and configured, 
    #as xcodebuild gets invoked later in the build, and it will fail otherwise
    if [[ -z "$(which xcodebuild)" ]] || ! xcodebuild --help >/dev/null 2>&1; then
        cat 1>&2 <<EOF
Please install XCode from the App Store.
You will need the full version, not just the command line tools.
If you already have XCode installed, you may need to issue this command
to let the tools find the right developer directory:
    sudo xcode-select -r
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
    sudo apt-get -qq update
    sudo apt-get -qq install build-essential git cmake libsdl2-dev libsdl2-image-dev
}

function ensure_arch_devtools_installed {
    sudo pacman -Sqyyu --noconfirm base-devel libglvnd sdl2 sdl2_image cmake
}

function ensure_creative_engine {
    if [[ ! -d "$CREATIVE_ENGINE_DIR" ]]; then
        git clone https://github.com/ModusCreateOrg/creative-engine.git "$CREATIVE_ENGINE_DIR"
    fi
}

function build {
    cd "$BASE_DIR"
    rm -f creative-engine
    ln -s ../creative-engine . 
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake ..
    make
}

######################### Main build ##################################

# Thanks Stack Overflow https://stackoverflow.com/a/17072017
OS="$(uname)"
if [ "$OS" == "Darwin" ]; then
    ensure_xcode_installed
    ensure_homebrew_installed
    # Install homebrew packages
    cd "$BASE_DIR"
    brew bundle install
elif [ "$(cut -c1-5 <<<"$OS")" == "Linux" ]; then
    # Do something under GNU/Linux platform
    if [[ -n "$(which apt-get 2>/dev/null)" ]]; then
        ensure_debian_devtools_installed
    elif [[ -n "$(which pacman 2>/dev/null)" ]]; then
        ensure_arch_devtools_installed
    else
        echo "Only debian/ubuntu and arch Linux are supported targets, sorry."
        exit 1
    fi
elif [ "$(cut -c1-10 <<<"$OS")" == "MINGW32_NT" ]; then
    echo "32 bit Windows not supported"
    exit 1
elif [ "$(cut -c1-10 <<<"$OS")" == "MINGW64_NT" ]; then
    echo "64 bit Windows not supported"
    exit 1
else
    echo 'Unsupported operating system "'"$OS"'"'
    exit 1
fi

ensure_creative_engine
build
=======
	#Ensure homebrew is installed
	if [[ -z "$(which brew)" ]]; then
	  echo "No homebrew found - installing Homebrew from https://brew.sh"
	  /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	fi
}


cd "$BASE_DIR"

# Thanks Stack Overflow https://stackoverflow.com/a/17072017
if [ "$(uname)" == "Darwin" ]; then
    ensure_xcode_installed
	  ensure_homebrew_installed
    # Install homebrew packages
    brew bundle install
elif [ "$(uname -s | cut -c 5)" == "Linux" ]; then
    # Do something under GNU/Linux platform
	  echo "Linux not supported"
	  exit 1
elif [ "$(uname -s | cut -c 10)" == "MINGW32_NT" ]; then
	  echo "32 bit Windows not supported"
	  exit 1
elif [ "$(uname -s | cut -c 10)" == "MINGW64_NT" ]; then
	  echo "64 bit Windows not supported"
	  exit 1
fi

ln -F -s ../creative-engine . 
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake ..
make
