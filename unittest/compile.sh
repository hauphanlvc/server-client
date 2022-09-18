#!/bin/bash

pushd ../build || exit 1
cmake ../ && make
popd || exit 1
