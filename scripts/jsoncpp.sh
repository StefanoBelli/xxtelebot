#!/bin/sh

git clone https://github.com/open-source-parsers/jsoncpp
cd jsoncpp
BUILD_TYPE=release
LIB_TYPE=shared
meson --buildtype ${BUILD_TYPE} --default-library ${LIB_TYPE} . build-${LIB_TYPE}
ninja -v -C build-${LIB_TYPE}
cd build-${LIB_TYPE}
sudo ninja install
