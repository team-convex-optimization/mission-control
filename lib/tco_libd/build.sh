#!/bin/bash

mkdir -p build
pushd build

clang \
    -Wall \
    -std=c11 \
    -fPIC \
    -c \
    -I ../code \
    -I ../include \
    ../code/*.c

llvm-ar \
    rc \
    tco_libd.a \
    *.o
popd
