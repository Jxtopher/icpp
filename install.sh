#!/bin/bash

for cmd in "git" "cmake" "make" "g++"
do
    if ! command -v $cmd &> /dev/null
    then
        echo "$cmd could not be found"
        exit
    fi
done

cd /tmp || exit
pushd .

git clone https://github.com/jxtopher/icpp
mkdir -p icpp/build
cd icpp/build || exit
cmake ..
make
sudo make install

popd || exit
rm -rf icpp
