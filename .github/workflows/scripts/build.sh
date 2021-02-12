#!/bin/sh

echo "Install wget"
apt-get update
apt-get install -y wget

echo "Upgrade to newer CMake"
new_cmake_dir="$HOME/tmp_cmake"
mkdir $new_cmake_dir
cd $new_cmake_dir
wget -q https://cmake.org/files/v3.19/cmake-3.19.2-Linux-x86_64.tar.gz
tar -xzf cmake-3.19.2-Linux-x86_64.tar.gz
export PATH="$new_cmake_dir/cmake-3.19.2-Linux-x86_64/bin:$PATH"

echo "Test CMake installation"
cd ~
cmake --version

echo "Build ROM"
cd /github/workspace
mkdir cmake-build
cd cmake-build
cmake .. -DCMAKE_BUILD_TYPE=Release -DGBDK_ROOT=/opt/gbdk
make
