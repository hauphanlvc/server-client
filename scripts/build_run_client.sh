#!/bin/bash

root_proj_dir=$(git rev-parse --show-toplevel)

# build
build_dir="$root_proj_dir/build"
mkdir -p $build_dir
cd $build_dir || (echo "cd build error" && exit)
cmake ../ 1>/dev/null
make 1>/dev/null && cd $root_proj_dir && export SERVER_IP=$1 SERVER_PORT=$2 && $build_dir/client