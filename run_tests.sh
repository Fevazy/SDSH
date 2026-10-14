#!/bin/bash
cd build &&
    ctest -j$(nproc)
