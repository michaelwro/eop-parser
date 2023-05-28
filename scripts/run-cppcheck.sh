#!/bin/bash
# Run cppcheck static analyzer
#
# Code By: Michael Wrona
# Created: 22 April 2023

# get project base directory
PROJ_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

# find project files and run cppcheck
find $PROJ_DIR/src/ $PROJ_DIR/include/ -type f \( -iname *.cpp -o -iname *.h \) | \
    cppcheck --file-list=- \
        --enable=style,warning \
        --language=c++ \
        --std=c++20 \
        --platform=unix64 \
        -I $PROJ_DIR/include/ \
        -i $PROJ_DIR/build/