#!/bin/bash

mkdir -p build

pushd lib/tco_libd
./build.sh
mv -f build/tco_libd.a ../../build
popd

pushd build
clang \
    -Wall \
    -std=c11 \
    -D _DEFAULT_SOURCE \
    -I /usr/include \
    -I ../lib/tco_libd/include \
    ../code/*.c \
    tco_libd.a \
    -o tco_mission_control.bin \
    -O 
popd

