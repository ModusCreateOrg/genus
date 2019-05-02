cd creative-engine/tools; make clean; make; cd -
rm -rf build
mkdir -p build
cd build
cmake ..
echo "Go to build/"
