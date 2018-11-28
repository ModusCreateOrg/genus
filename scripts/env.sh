#!/usr/bin/env bash

declare GENUS_ROOT
declare ENGINE_ROOT

if [[ -z "${GENUS_ROOT:-}" ]]; then
  GENUS_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}")/.." && pwd )"
  export GENUS_ROOT
fi

if [[ -z "${ENGINE_ROOT:-}" ]]; then
  ENGINE_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}")/../creative-engine" && pwd )"
  export ENGINE_ROOT
fi
