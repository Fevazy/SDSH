#!/bin/bash
cd cmake_build &&
    ninja &&
    cd .. &&
    ln -sf cmake_build/compile_commands.json .
