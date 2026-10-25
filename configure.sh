#!/bin/bash
rm -rf cmake_build
mkdir cmake_build &&
    cd cmake_build &&
    cmake -G Ninja .. &&
    cd .. &&
    ln -sf cmake_build/compile_commands.json .
