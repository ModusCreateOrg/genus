#!/usr/bin/env bash


set -euo pipefail

# Set DEBUG to true for enhanced debugging: run prefixed with "DEBUG=true"
${DEBUG:-false} && set -vx
# Credit to https://stackoverflow.com/a/17805088
# and http://wiki.bash-hackers.org/scripting/debuggingtips
export PS4='+(${BASH_SOURCE}:${LINENO}): ${FUNCNAME[0]:+${FUNCNAME[0]}(): }'

VERBOSE=0
DEPLOY_IPK=0

# https://stackoverflow.com/questions/192249/how-do-i-parse-command-line-arguments-in-bash
POSITIONAL=()
while [[ $# -gt 0 ]] ;do
  key="$1"

  case $key in
      -v|--verbose)
      VERBOSE=1
      shift # past argument
      ;;

      -d|--deploy-ipk)
      set DEPLOY_IPK=1
      shift # past argument
      ;;
      
      *)    # unknown option
      POSITIONAL+=("$1") # save it in an array for later
      shift # past argument
      ;;
  esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters



SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

. ${SCRIPT_DIR}/ldk_scripts_common.sh

cd ${WORKING_DIR}




echo "Compiling"
mkdir -p build/ldk/

make cleanall

md5=''

if [[ ${VERBOSE} -eq 1 ]]; then
  make -j `nproc` ipk
  md5=`md5sum build/ldk/modite-adventure.dge | awk '{print $1}'`
  md5=${md5: -6}
else
  make -j `nproc` ipk >/dev/null 2>&1
  md5=`md5sum build/ldk/modite-adventure.dge | awk '{print $1}'`
  md5=${md5: -6}
fi


me=`whoami`


ping 169.254.1.1 -c 1 -W 1 -i 200
# RC=$?

# if [[ $RC -gt 0 ]]; then
#   PRINT_YELLOW "WARNING: LDK_IP not connected!"
#   echo "Connect LDK_IP and "

#   while true; do
#     echo "Checking for ${LDK_IP} `date`"

#     ping 169.254.1.1  -c 1 -W 0 -i 200 >/dev/null 2>&1
#     RC=$?

#     if [[ $RC -eq 0 ]]; then
#       break;
#     fi
#   done

#   PRINT_GREEN "Found LDK_IP. Deploying..."
# fi





function deploy_binary_via_ftp {

ftp -n -v $LDK_IP << EOT
user $USER
prompt
passive
lcd build/ldk
cd /home/retrofw/games
mkdir modite-adventure
cd modite-adventure
bin
put modite-adventure.dge
quit
EOT

  echo "Deployed latest binary ${md5} to ${ALREADY_DEPLOYED_DIR}"
}


function deploy_ipk_via_ftp {
ftp -n -v $LDK_IP << EOT
user $USER
prompt
passive
lcd build/ldk
cd /home/retrofw/
mkdir tmp
cd tmp/
bin
put modite-adventure.ipk
quit
EOT

  echo ""
  echo "Deployed latest IPK to ${LDK_DEVICE_DIR}"
  echo ""
  PRINT_GREEN "Next Steps:"
  echo " - Launch Explorer on device"
  echo " - Navigate to /home/retrofw/tmp"
  echo " - Install 'modite-adventure.ipk'"
  echo "Further invocations of this script should not require \"deploy-ipk\" argument."
}


if [[ $DEPLOY_IPK == true ]]; then
  deploy_ipk_via_ftp
else
  deploy_binary_via_ftp
fi




echo " "

echo -e "Ready to test build" "${GREEN}${md5}${COLOR_RESET}"
# echo "Reboot LDK_IP Game and enable CHARGER mode"

echo " "
