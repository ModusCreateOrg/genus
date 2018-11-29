#!/usr/bin/env bash

# Sets some Bash options to encourage well formed code.
# For example, some of the options here will cause the script to terminate as
# soon as a command fails. Another option will cause an error if an undefined
# variable is used.
# See: https://www.gnu.org/software/bash/manual/html_node/The-Set-Builtin.html

# Any trap on ERR is inherited by shell functions, command substitutions, and
# commands executed in a subshell environment. The ERR trap is normally not
# inherited in such cases.
set -o errtrace

# Any trap on DEBUG and RETURN are inherited by shell functions, command
# substitutions, and commands executed in a subshell environment. The DEBUG and
# RETURN traps are normally not inherited in such cases.
set -o functrace

# Exit if any command exits with a non-zero exit status.
set -o errexit

# Exit if script uses undefined variables.
set -o nounset

# Prevent masking an error in a pipeline.
# Look at the end of the 'Use set -e' section for an excellent explanation.
# see: https://www.davidpashley.com/articles/writing-robust-shell-scripts/
set -o pipefail

# Make debugging easier when you use `set -x`
# See: http://wiki.bash-hackers.org/scripting/debuggingtips#making_xtrace_more_useful
export PS4='+(${BASH_SOURCE}:${LINENO}): ${FUNCNAME[0]:+${FUNCNAME[0]}(): }'

# If using Travis, output is 0, else 1
function using_travis? {
  if [[ "${TRAVIS:-}" == "true" ]]; then
    echo 0
  else
    echo 1
  fi
}

# If using Linux, output is 'linux'
# If using OSX, output is 'osx'
function get_os {
  local -i on_travis
  local os
  on_travis=$(using_travis?)

  if [[ $on_travis -eq 0 ]]; then
    printf "%s" "$TRAVIS_OS_NAME"
  else
    os="$(uname)"
    case "$os" in
      Darwin)
        printf "osx"
        ;;

      Linux)
        printf "linux"
        ;;

      *)
        echo "ERROR: Unsupported platform '$os'"
        set -x && exit 1
        ;;
    esac
  fi
}
