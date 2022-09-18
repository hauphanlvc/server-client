#!/bin/bash

pushd build || exit 1
cmake ../ && make
./ut_client_sendName_test
./ut_client_clientTest_test
popd
