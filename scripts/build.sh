#!/usr/bin/env bash

######################### Debugging and Directory Scaffolding #########

# Set bash unofficial strict mode http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail
# our traps need access to some vars to do their job properly.
set -o errtrace
set -o functrace
IFS=$'\n\t'

# Enable for enhanced debugging
${DEBUG:-false} && set -vx

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
CREATIVE_ENGINE_DIR="${CREATIVE_ENGINE_PATH:-$TOP_DIR/creative-engine}"
export DIR BUILD_DIR TOP_DIR CREATIVE_ENGINE_DIR
# shellcheck source=scripts/common.sh
source "$DIR/common.sh"

######################### Main build ##################################

export SUPPORTED_ESP_IDF_VERSION="ba1ff1692b433e76718a60c3b2cb75e66b383909"

op=${1:-}
SKIP_TOOLS_INSTALL=false
SUDO="sudo"
export SUDO

# This remains a case for future expansion.
case "$op" in
    clean)
        #clean Moved below installs because ArchLinux needs git installed first
        ;;
    docker-build)
        SKIP_TOOLS_INSTALL=true
        ;;
esac

# Thanks Stack Overflow https://stackoverflow.com/a/17072017
OS="$(uname)"
if "$SKIP_TOOLS_INSTALL"; then
    echo "Skipping tools install"
elif [ "$OS" == "Darwin" ]; then
    ensure_xcode_installed
    ensure_homebrew_installed
    # Install homebrew packages
    cd "$BASE_DIR"
    brew bundle install
    # Travis has an older brew version of cmake, be sure we have the latest or this will not build
    brew upgrade cmake || true
elif [ "$(cut -c1-5 <<<"$OS")" == "Linux" ]; then
    # Do something under GNU/Linux platform
    if command -v apt-get >/dev/null 2>&1; then
        ensure_debian_devtools_installed
    elif command -v pacman >/dev/null 2>&1; then
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
    echo "Unsupported operating system '$OS'"
    exit 1
fi

# This remains a case for future expansion.
case "$op" in
    clean)
        clean
        ;;
    docker-build)
        clean
        ;;
esac

# Prepare dependencies
ensure_creative_engine
checkout_creative_engine_branch

# Build the software and documentation
build
# build_xtensa #GEN-275
if [ "$OS" == "Darwin" ]; then
    patch_mac_build
elif [ "$OS" == "Linux" ]; then
    patch_linux_build
fi


# "$BASE_DIR/doxygen/build.sh" #GEN-275

# Archive the artifacts
archive_app
