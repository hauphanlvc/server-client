#!/bin/bash

# root_proj_dir=$(git rev-parse --show-toplevel)

# build
build_dir="./build/server"
cd $build_dir || (echo "cd build error" && exit)
cmake ../../scripts/build_server/
make