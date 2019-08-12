#!/bin/bash

# this script builds everything and runs the correctness test of your sort

mkdir -p build

cd build

cmake .. -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_DOWNLOAD_DEPENDENCIES=OFF

make

make test ARGS=-V
