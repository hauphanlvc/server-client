#!/bin/bash

# install clang-format if not exist
CLANG="clang-format"
IS_CLANG_INSTALLED=$(dpkg-query -W --showformat='${Status}\n' $CLANG | grep "install ok installed")
if [ "" = "$IS_CLANG_INSTALLED" ]; then
    sudo apt-get update
    sudo apt-get --yes install $CLANG
fi

# project folder
root_project=$(git rev-parse --show-toplevel)

# format file .cpp and .h
echo Formatting...
find "$root_project" | grep "\.cpp$\|\.h$" | xargs clang-format -style=Google -i
echo Done

# show files still have error
find "$root_project" | grep "\.cpp$\|\.h$" | xargs cpplint | grep -v "^Done processing"

# remove merge backup files
find "$root_project" | grep "\.orig$" | xargs rm -f
