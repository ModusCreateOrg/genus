#!/usr/bin/env bash

### LDK SCRIPTS COMMON


set -euo pipefail

# Set DEBUG to true for enhanced debugging: run prefixed with "DEBUG=true"
${DEBUG:-false} && set -vx
# Credit to https://stackoverflow.com/a/17805088
# and http://wiki.bash-hackers.org/scripting/debuggingtips
export PS4='+(${BASH_SOURCE}:${LINENO}): ${FUNCNAME[0]:+${FUNCNAME[0]}(): }'


export LDK_IP=169.254.1.1

# Set DEBUG to true for enhanced debugging: run pre
# fixed with "DEBUG=true"
${DEBUG:-false} && set -vx

export BLUE="\e[34m"
export RED="\e[31m"
export GREEN="\e[32m"
export CYAN="\e[36m"
export COLOR_RESET="\e[0m"
export YELLOW="\e[33m"

function PRINT_RED {
	echo -e "${RED}${1}${COLOR_RESET}"
}

function PRINT_GREEN {
	echo -e "${GREEN}${1}${COLOR_RESET}"
}

function PRINT_BLUE {
	echo -e "${BLUE}${1}${COLOR_RESET}"
}

function PRINT_YELLOW {
	echo -e "${YELLOW}${1}${COLOR_RESET}"
}

function PRINT_CYAN {
	echo -e "${CYAN}${1}${COLOR_RESET}"
}


export WORKING_DIR=${SCRIPT_DIR}/..


export me=`whoami`
export DEPLOY_MOUNT=/media/${me}/RETROFW
export LDK_DEVICE_DIR=${DEPLOY_MOUNT}/test



export BUILD_DIR=${WORKING_DIR}/build/ldk
export CREATIVE_ENGINE_PATH=${WORKING_DIR}/creative-engine
export CREATIVE_ENGINE_SOURCE_DIR=${CREATIVE_ENGINE_PATH}/src

export TARGET=${BUILD_DIR}/genus.dge

export IPK_WORKING_DIR=${BUILD_DIR}/ipk
export IPK_EXEC_DIR=${IPK_WORKING_DIR}/home/retrofw/games/genus
export LDK_FILES_DIR=${WORKING_DIR}/resources/ldk-files
export LNK_DESTINATION_DIR=${IPK_WORKING_DIR}/home/retrofw/apps/gmenu2x/sections/games/

export ALREADY_DEPLOYED_DIR=/home/retrofw/games/genus