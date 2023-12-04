#!/bin/bash

# Update CMake cache and make
./update.sh
cd build
time make -j6
