#!/usr/bin/env bash

# This script should be used to install build dependencies.

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# shellcheck source=./.ci/travis/bootstrap.sh
source "$DIR"/bootstrap.sh

declare os
os="$(get_os)"

case "$os" in
  osx)
    brew install shellcheck
    ;;

  *)
    echo "ERROR: Unsupported platform '$os'"
    set -x && exit 1
    ;;
esac

# If you have a highly customized ~/.ssh/config file, you might find setting
# this variable very useful if you want to run this script locally.
#
# For example:
#   $ cat ~/.ssh/config
#
#   Host github.com
#     HostName github.com
#     User git
#     IdentityFile ~/.ssh/id_rsa.pub
#
#   Host github.com-alternative
#     HostName github.com
#     User git
#     IdentityFile ~/.ssh/id_rsa-alternative.pub
#
# You can now do:
#   $ GEN_GITHUB_HOSTNAME=github.com-alternative ./before_install.sh
# That will cause Git to use the '~/.ssh/id_rsa-alternative.pub' key.
if [[ ! -v GEN_GITHUB_HOSTNAME ]]; then
  GEN_GITHUB_HOSTNAME="github.com"
fi
git clone git@"$GEN_GITHUB_HOSTNAME":ModusCreateOrg/creative-engine.git
