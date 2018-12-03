#!/usr/bin/env bash

# This script should be used to make preparations to run the 'script' lifecycle.

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# shellcheck source=./.ci/travis/bootstrap.sh
source "$DIR"/bootstrap.sh

if [[ "${TRAVIS_BRANCH:-}" != "master" ]] && [[ -z "${TRAVIS_TAG:-}" ]]; then
  echo "ERROR: This is not being merged into master and no tag is present."
  exit 1
fi

declare release_filename
release_filename=$(get_release_filename)

mv "${TRAVIS_BUILD_DIR}/build/release.tgz"  "${TRAVIS_BUILD_DIR}/build/${release_filename}.tgz"
