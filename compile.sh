set -v
BUILD_DIR=build_arm

# comple
mkdir -p  $BUILD_DIR && cd $BUILD_DIR
cmake -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=Release  ..
make -j6 && make install
