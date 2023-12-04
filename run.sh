#!/bin/bash

# Build target
./build.sh

# Run executable if build is successful
if [ $? -eq 0 ]
then
    clear
    time ./build/DuckDnsClient
fi
