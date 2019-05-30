#!/usr/bin/env bash

# this scripts assumes you have png2ico, sips and iconutil (mac) installed!



outputDir="resources/desktop-icon"
sourcePNG="${outputDir}/GenusIcon.png"
tempDir="Genus.iconset"

rm -rf ${tempDir} 2>/dev/null


### Mac specific
function scale_image_mac() {

  if [ -z ${2} ]; then
    outFile="${tempDir}/icon_${1}x${1}.png"
  else
    outFile="${tempDir}/icon_${2}.png"
  fi

  sips -z $1 $1 "${sourcePNG}" --out ${outFile} >/dev/null
}

mkdir -p ${tempDir}


scale_image_mac 16
scale_image_mac 32 "16x16@2x"
scale_image_mac 32 
scale_image_mac 64 "32x32@2x"
scale_image_mac 64 
scale_image_mac 128 "64x64@2x"
scale_image_mac 128
scale_image_mac 256 "128x128@2x"
scale_image_mac 256 
scale_image_mac 512 "256x256@2x"
scale_image_mac 512
scale_image_mac 1024 "512x512@2x"

iconutil -c icns "${tempDir}"
mv Genus.icns ${outputDir}

echo "Created mac icon at ${outputDir}/Genus.icns"

rm -R ${tempDir}



# Linux Specific

mkdir ${tempDir}

function scale_image_linux() {
  outFile="${tempDir}/icon_${1}x${1}.png"
  sips -z $1 $1 "${sourcePNG}" --out ${outFile} >/dev/null
}

scale_image_linux 16
scale_image_linux 24
scale_image_linux 32
scale_image_linux 48
scale_image_linux 64
scale_image_linux 96
scale_image_linux 128


png2ico ${outputDir}/Genus.ico ${tempDir}/*.png >/dev/null
echo "Created Linux icon at ${outputDir}/Genus.ico"

rm -R ${tempDir}

