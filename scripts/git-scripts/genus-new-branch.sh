#!/usr/bin/env bash

source ../env.sh

if [ "$#" -ne 1 ]; then
    echo "The branchname is missing!"
    echo "Usage: genus-new-branch.sh <branchname>"
fi

(cd $GENUS_ROOT; git checkout master)
(cd $GENUS_ROOT; git pull upstream master)
(cd $GENUS_ROOT; git checkout -b $1)
