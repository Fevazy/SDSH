#!/bin/bash
rm -rf build
mkdir build &&
    cd build &&
    cmake -G Ninja .. &&
    ninja &&
    cd .. &&
    ln -sf build/compile_commands.json .
