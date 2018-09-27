#!/usr/bin/env bash

source ../env.sh

(cd $GENUS_ROOT; git checkout master)
(cd $GENUS_ROOT; git pull upstream master)

(cd $ENGINE_ROOT; git checkout master)
(cd $ENGINE_ROOT; git pull upstream master)

