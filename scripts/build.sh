#!/usr/bin/env bash

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

