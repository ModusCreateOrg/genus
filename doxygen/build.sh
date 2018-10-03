#!/usr/bin/env bash

MY_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"
LOGO_IN="$MY_DIR/../images/modus.logo.svg"

if [[ ! -f "$MY_DIR/modus.logo.header.png" ]] && [[ -x "$(command -v convert)" ]]; then
  (cd $MY_DIR && /usr/bin/env convert -resize x55 $LOGO_IN modus.logo.header.png)
fi

(cd $MY_DIR && /usr/bin/env doxygen Doxyfile.in)
