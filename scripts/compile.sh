#!/usr/bin/env bash
# Use clang++ when available, otherwise gcc
if command -v clang++ >/dev/null 2>&1 ; then
    exec clang++ "$@"
else
    exec gcc "$@"
fi
