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
function using_travis {
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
  on_travis=$(using_travis)

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

function get_merge_release_filename {
  shopt -s nocasematch
  local pattern
  pattern="(gen[^0-9]+[0-9]+)[^0-9]*"
  if [[ "${TRAVIS_COMMIT_MESSAGE:-}" =~ $pattern ]]; then
    local jira_ticket_id
    # convert to upper case.
    # NOTE: don't use anything fancy here since osx on Travis uses Bash 3.x so
    #       version 4.x's way of doing this won't work here.
    jira_ticket_id=$(echo "${BASH_REMATCH[1]}" | tr '[:lower:]' '[:upper:]')
    jira_ticket_id="${jira_ticket_id}.app"
    echo "${jira_ticket_id// /-}" # replace spaces with hyphens
  else
    echo "ERROR: Unable to get JIRA branch name from the merge to master."
    set -x && exit 1
  fi
}

function get_release_filename {
  if [[ "${TRAVIS_BRANCH:-}" == "master" ]]; then
    # On merge to 'master', generate [jira_ticket_id].app.tgz release.
    # Ticket name can safely be assumed based on the regexp /(gen[^0-9]+[0-9]+)/i.
    printf "%s" "$(get_merge_release_filename)"
  elif [[ -n "${TRAVIS_TAG:-}" ]]; then
    # On tag, generate [GIT_TAG].tgz release
    printf "%s" "${TRAVIS_TAG}"
  fi
}
