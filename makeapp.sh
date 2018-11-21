#!/usr/bin/env bash

# A bandaid (helper script) to build & package

rm -rf build/
scripts/build.sh

if [[ -f ./build/genus.tgz ]]; then
    cp ./build/genus.tgz ~/Downloads/
    open ~/Downloads/
fi
