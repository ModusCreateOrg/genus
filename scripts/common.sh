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
    $SUDO apt-get -qq install build-essential git libsdl2-dev libsdl2-image-dev curl
    # Ubuntu 16.04 has an old cmake (3.9) so install a newer one from binaries from cmake
    # Adapted from https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line
    local version
    local build
    local tmpdir
    version=3.12
    build=3
    tmpdir=$(mktemp -d)
    cd "$tmpdir" || exit 1
    curl -sSO "https://cmake.org/files/v$version/cmake-$version.$build-Linux-x86_64.sh"
    $SUDO mkdir /opt/cmake
    yes | $SUDO sh "cmake-$version.$build-Linux-x86_64.sh" --prefix=/opt/cmake || true # exits 141 on success for some reason
    $SUDO ln -s "/opt/cmake/cmake-$version.$build-Linux-x86_64/bin/cmake" /usr/local/bin/cmake
    rm -rf "$tmpdir"
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
    if [[ ! -d creative-engine ]]; then
        rm -f creative-engine
        ln -s ../creative-engine . 
    fi
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR" || exit 1
    pwd
    ls -l
    ls -l ..
    cmake ..
    make
}

function clean {
    cd "$CREATIVE_ENGINE_DIR" || exit 1
    git clean -fdx
    rm -rf "$BASE_DIR/build"
}

