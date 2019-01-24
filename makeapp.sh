#!/usr/bin/env bash

# A bandaid (helper script) to build & package

rm -rf build/
scripts/build.sh



function makeTgz() {
  if [[ -f ./build/genus.tgz ]]; then
    cp ./build/genus.tgz ~/Downloads/
    open ~/Downloads/
  fi
}

function openApp() {
  open build/genus.app
}

for i in "$@"
do
  case $i in 
    -t|--maketgz)
      makeTgz
      shift # past argument=value
      ;;

    -o|--open)
      openApp
      shift
      ;;
  esac
done
