#!/bin/bash
cd cmake_build &&
    ctest -j$(nproc) $@
