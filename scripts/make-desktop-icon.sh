#!/usr/bin/env bash

outputFolder="resources"
sourcePNG="${outputFolder}/desktop-icon/GenusIcon.png"
tempFolder="Genus.iconset"

mkdir -p ${tempFolder}

function write_scaled_image() {

  if [ -z ${2} ]; then
    outFile="${tempFolder}/icon_${1}x${1}.png"
  else
    outFile="${tempFolder}/icon_${2}.png"
  fi

  sips -z $1 $1 "${sourcePNG}" --out ${outFile} >/dev/null
}

write_scaled_image 16
write_scaled_image 32 "16x16@2x"
write_scaled_image 32 
write_scaled_image 64 "32x32@2x"
write_scaled_image 64 
write_scaled_image 128 "64x64@2x"
write_scaled_image 128
write_scaled_image 256 "128x128@2x"
write_scaled_image 256 
write_scaled_image 512 "256x256@2x"
write_scaled_image 512
write_scaled_image 1024 "512x512@2x"

iconutil -c icns "${tempFolder}"
mv Genus.icns ${outputFolder}/desktop-icon/

echo "Created ${outputFolder}/desktop-icon/Genus.icns"

rm -R ${tempFolder}