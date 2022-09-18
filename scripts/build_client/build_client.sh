#!/bin/bash

# building client


build_dir="/home/build/client"
cd $build_dir || (echo "cd build error" && exit)
cmake /home/scripts/build_client/
make