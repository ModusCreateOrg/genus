#!/usr/bin/env bash

set -euo pipefail

# Credit to Stack Overflow questioner Jiarro and answerer Dave Dopson
# http://stackoverflow.com/questions/59895/can-a-bash-script-tell-what-directory-its-stored-in
# http://stackoverflow.com/a/246128/424301
MY_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"
LOGO_IN="$MY_DIR/../images/modus.logo.svg"

cd "$MY_DIR"
if [[ ! -f "$MY_DIR/modus.logo.header.png" ]] && [[ -x "$(command -v convert)" ]]; then
  /usr/bin/env convert -resize x55 "$LOGO_IN" modus.logo.header.png
fi

/usr/bin/env doxygen Doxyfile.in
