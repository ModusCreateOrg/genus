#!/usr/bin/env bash

# This script should be used to make preparations to run the 'script' lifecycle.

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# shellcheck source=./.ci/travis/bootstrap.sh
source "$DIR"/bootstrap.sh

shellcheck --version

# Running in a subshell to avoid cd'ing back and forth.
(
  pushd "$DIR/../../" > /dev/null
  # Look for all files with a '.sh' extension, excluding the 'creative-engine'
  # dir. Run shellcheck against those files
  find \
    . \
    -path ./creative-engine \
    -prune -o \
    -name '*.sh' \
    -exec \
      bash -c \
        'shellcheck --external-sources "$1"' \
    -- {} \;
)
