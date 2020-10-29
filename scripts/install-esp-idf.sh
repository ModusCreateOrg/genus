#!/usr/bin/env bash

# Prepare the ESP-IDF home directory
cd ~
mkdir ~/esp
cd ~/esp

# Clone the esp-idf repository at version 3.2:
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf || exit 1
git reset --hard ba1ff1692b433e76718a60c3b2cb75e66b383909
git submodule update --init --recursive

cd ..

if [[ `uname` == "Darwin" ]] ; then
    IDF_ELF_FILE="xtensa-esp32-elf-osx-1.22.0-80-g6c4433a-5.2.0.tar"
else
    IDF_ELF_FILE="xtensa-esp32-elf-linux64-1.22.0-80-g6c4433a-5.2.0.tar"
fi

wget https://dl.espressif.com/dl/${IDF_ELF_FILE}.gz
gzip -d ${IDF_ELF_FILE}
tar xfv ${IDF_ELF_FILE}
rm -f ${IDF_ELF_FILE}

echo "Be sure to add the following line to your shell profile"
echo "export IDF_PATH=~/esp/esp-idf"
echo "If you need help, visit this URL:"
echo "https://docs.espressif.com/projects/esp-idf/en/latest/get-started/add-idf_path-to-profile.html#linux-and-macos"
