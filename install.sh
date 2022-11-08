#!/bin/bash

for cmd in "git" "cmake" "make" "g++"
do
    if ! $(command -v $cmd &> /dev/null)
    then
        echo "$cmd could not be found"
        exit
    fi
done

pushd .
cd /tmp || exit


git clone https://github.com/jxtopher/icpp
mkdir -p icpp/build
cd icpp/build || exit
cmake ..
make

if [ "$EUID" -ne 0 ]
  then sudo make install
  else make install
fi


popd || exit
rm -rf icpp
