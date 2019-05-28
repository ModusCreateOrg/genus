#!/usr/bin/env bash

######################### Function definitions ########################

SUDO=${SUDO:-}

function ensure_xcode_installed {
    #Ensure XCode full version is installed and configured,
    #as xcodebuild gets invoked later in the build, and it will fail otherwise
    if ! command -v xcodebuild >/dev/null 2>&1; then
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
    if ! command -v brew >/dev/null 2>&1; then
      echo "No homebrew found - installing Homebrew from https://brew.sh"
      /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    fi
}

function ensure_cmake {
    # Adapted from https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line
    if [[ -x /usr/local/bin/cmake ]]; then
        return
    fi
    local version
    local -i build
    local tmpdir
    local cmake
    version=3.12
    build=3
    arch=$(arch)
    uname=$(uname -s)
    tmpdir=$(mktemp -d)
    cmake="cmake-$version.$build-$uname-$arch"
    cd "$tmpdir" || exit 1
    if curl -fsSO "https://cmake.org/files/v$version/$cmake.sh"; then
        # Install binary package if we could retrieve it
        $SUDO mkdir -p /opt/cmake
        yes | $SUDO sh "$cmake.sh" --prefix=/opt/cmake || true # exits 141 on success for some reason
        $SUDO rm -f /usr/local/bin/cmake
        $SUDO ln -s "/opt/cmake/$cmake/bin/cmake" /usr/local/bin/cmake
    else

        # Install from source (on Raspberry Pi with Rasbian 9.6 (stretch) for example.
        cmake="cmake-$version.$build"
        curl -fsSO "https://cmake.org/files/v$version/$cmake.tar.gz"
        tar xfz "$cmake.tar.gz"
        cd "$cmake" || exit 1
        ./configure
        make
        $SUDO make install
    fi
    cd - || exit 1
    rm -rf "$tmpdir"
}

function ensure_debian_devtools_installed {
    $SUDO apt-get -qq update
    $SUDO apt-get -qq install --no-install-recommends build-essential git libsdl2-dev libsdl2-image-dev curl doxygen imagemagick ca-certificates openssl
    # Ubuntu 18.04 has an old cmake (3.9) so install a newer one from binaries from cmake
    ensure_cmake
}

function ensure_arch_devtools_installed {
    $SUDO pacman -Sqyyu --noconfirm base-devel git libglvnd sdl2 sdl2_image curl doxygen imagemagick
    # Use same version of cmake as for ubuntu
    ensure_cmake
}

function ensure_creative_engine {
    if [[ ! -d "$CREATIVE_ENGINE_DIR" ]]; then
        git clone git@github.com:ModusCreateOrg/creative-engine.git "$CREATIVE_ENGINE_DIR"
    fi
}

function build {
    cd "$BASE_DIR" || exit 1
    if [[ ! -d $CREATIVE_ENGINE_DIR ]]; then
        # rm -f creative-engine
        ln -sf $CREATIVE_ENGINE_DIR .
    fi
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR" || exit 1
    cmake ..
    make -j 8
}

function ensure_esp_idf {
    if [[ -n "${IDF_PATH:-}" ]]; then
        echo "XTENSA is already installed, nothing to do."
        return
    fi

    echo "Attempting to install XTENSA on: $OS"

    cd "$BASE_DIR" || exit 1
    OS="$(uname)"
    if [[ "$OS" == "Darwin" ]]; then
        cp sdkconfig.osx sdkconfig
        mkdir esp
        cd esp || exit 1
        git clone --recursive https://github.com/espressif/esp-idf.git
        cd esp-idf || exit 1
        git reset --hard SUPPORTED_ESP_IDF_VERSION
        git submodule update --init --recursive
        export IDF_PATH="$BASE_DIR/esp/esp-idf"
        python -m pip install --user -r "$IDF_PATH/requirements.txt"
    else
        echo "Can't install XTENSA on: $OS"
    fi
}

function build_xtensa {
    if [[ ! "$OS" == "Darwin" ]]; then
        echo "Can't build XTENSA target on: $OS"
        return
    fi
    ensure_esp_idf
    if [[ -z "$IDF_PATH" ]]; then
        Echo "ESP_IDF is not installed!"
        return
    fi

    cd "$BASE_DIR" || exit 1

    if [[ ! -d $CREATIVE_ENGINE_DIR ]]; then
        rm -f creative-engine
        ln -s $CREATIVE_ENGINE_DIR .
    fi
    mkdir -p "$BUILD_DIR"
    make -j 10
}

function clean {
    cd "$CREATIVE_ENGINE_DIR" || exit 1
    git clean -fdx
    rm -rf "$BASE_DIR/build"
}

# TODO: Use otool -L and some foo to find the dependencies
#        The sentinel is "/usr/local/opt"
function copy_sdl2_libs_to_app {
    if [[ "$OS" == "Darwin" ]]; then
        export APP_DIR="$BASE_DIR/build/genus.app"
        export APP_CNT_DIR="$APP_DIR/Contents"
        export APP_RES_DIR="$APP_CNT_DIR/Resources"
        export APP_MACOSX_DIR="$APP_CNT_DIR/MacOS"
        if [[ -d "$APP_DIR" ]]; then
            rm -rf "$APP_MACOSX_DIR/libs"
            mkdir -p "$APP_MACOSX_DIR/libs"

            cp /usr/local/opt/sdl2/lib/libSDL2.dylib "$APP_MACOSX_DIR/libs/"
            cp /usr/local/opt/sdl2_image/lib/libSDL2_image.dylib "$APP_MACOSX_DIR/libs/"
            cp /usr/local/opt/libpng/lib/libpng.dylib "$APP_MACOSX_DIR/libs/"
            cp /usr/local/opt/jpeg/lib/libjpeg.dylib "$APP_MACOSX_DIR/libs/"
            cp /usr/local/opt/libtiff/lib/libtiff.dylib "$APP_MACOSX_DIR/libs/"
            cp /usr/local/opt/webp/lib/libwebp.dylib "$APP_MACOSX_DIR/libs/"
            chmod 0755 "$APP_MACOSX_DIR"/libs/*

            # FIX Genus
            install_name_tool -change \
                /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib \
                 ./libs/libSDL2.dylib \
                 "$APP_MACOSX_DIR/genus"
            install_name_tool -change \
                /usr/local/opt/sdl2_image/lib/libSDL2_image-2.0.0.dylib \
                ./libs/libSDL2_image.dylib \
                "$APP_MACOSX_DIR/genus"

            # FIX SDL2_image
            install_name_tool -change \
                /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib \
                ./libs/libSDL2.dylib \
                "$APP_MACOSX_DIR/libs/libSDL2_image.dylib"
            install_name_tool -change \
                /usr/local/opt/libpng/lib/libpng16.16.dylib \
                ./libs/libpng.dylib \
                "$APP_MACOSX_DIR/libs/libSDL2_image.dylib"
               install_name_tool -change \
                /usr/local/opt/jpeg/lib/libjpeg.9.dylib \
                ./libs/libjpeg.dylib \
                "$APP_MACOSX_DIR/libs/libSDL2_image.dylib"
            install_name_tool -change \
                /usr/local/opt/libtiff/lib/libtiff.5.dylib \
                ./libs/libtiff.dylib \
                "$APP_MACOSX_DIR/libs/libSDL2_image.dylib"
            install_name_tool -change \
                /usr/local/opt/webp/lib/libwebp.7.dylib \
                ./libs/libwebp.dylib \
                "$APP_MACOSX_DIR/libs/libSDL2_image.dylib"

            # FIX TIFF
            install_name_tool -change \
                /usr/local/opt/jpeg/lib/libjpeg.9.dylib \
                ./libs/libjpeg.dylib \
                "$APP_MACOSX_DIR/libs/libtiff.dylib"

            # CREATE WRAPPER
            mv "$APP_MACOSX_DIR/genus" "$APP_MACOSX_DIR/genus.bin"
            tee "$APP_MACOSX_DIR/genus" <<-"EOF"
		#!/usr/bin/env bash
		MY_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"
		(cd $MY_DIR && ./genus.bin)
		EOF
            chmod 0755 "$BASE_DIR/build/genus.app/Contents/MacOS/genus"

            # INSTALL APP.PLIST & ETC
            cp "$BASE_DIR/resources/info.plist" "$APP_CNT_DIR"
            mkdir -p "$APP_RES_DIR"
            cp "$BASE_DIR/resources/GenusIcon.icns" "$APP_RES_DIR"

        fi
    fi
}

function checkout_creative_engine_branch {
    DEFAULT_BRANCH="master"
    GENUS_BRANCH=$(git rev-parse --abbrev-ref HEAD)
    cd "$BASE_DIR" || exit 1
    echo "The current genus branch is: $GENUS_BRANCH"
    if (cd "$CREATIVE_ENGINE_DIR" && git checkout "$GENUS_BRANCH"); then
        echo "Checked out creatine-engine branch: $GENUS_BRANCH"
    elif (cd "$CREATIVE_ENGINE_DIR" && git checkout "$DEFAULT_BRANCH"); then
        echo "Checked out creatine-engine branch: $DEFAULT_BRANCH"
    else
        echo "Faied to checkout a branch for creatine-engine!"
        exit 1
    fi
    cd - || exit 1
}


function archive_app {
    if [[ "$OS" == "Darwin" ]]; then
        echo "Archiving app"
        cd "$BUILD_DIR" || exit 1
        # tar czvfp genus.tgz genus-docs genus.app Genus.bin Genus.elf Genus.map
        tar czvfp genus.tgz genus.app
        # ls -l
        cd - || exit 1
    fi
}
