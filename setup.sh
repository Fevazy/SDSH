#!/bin/bash
mkdir build &&
    cd build &&
    cmake -G Ninja .. &&
    cd .. &&
    ln -sf build/compile_commands.json .
