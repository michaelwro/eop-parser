#!/bin/bash
# Run clang-tidy analysis
#
# Code By: Michael Wrona
# Created: 22 April 2023

PROJ_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

# build first (to get compile commands)
BUILD_DIR=$PROJ_DIR/build/

if [ ! -d "$BUILD_DIR" ]; then
    echo "Build directory does not exist, building."
    bash $PROJ_DIR/scripts/build-debug.sh
fi

# run analysis
clang-tidy --config="$(cat $PROJ_DIR/.clang-tidy)" \
    -p $BUILD_DIR --quiet \
    $(find $PROJ_DIR/src/ $PROJ_DIR/include/ -type f \( -iname *.cpp -o -iname *.h \))\
