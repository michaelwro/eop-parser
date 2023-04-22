#!/bin/bash
# Debug build project
#
# Code By: Michael Wrona
# Created: 22 April 2023

PROJ_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

cmake -B $PROJ_DIR/build/ -DCMAKE_BUILD_TYPE=Debug
cmake --build $PROJ_DIR/build/ -j
