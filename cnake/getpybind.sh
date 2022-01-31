#!/bin/bash
wget https://github.com/pybind/pybind11/archive/master.zip
sudo apt-get install unzip -y
unzip master.zip
mkdir -p pybind11-master/build
cd pybind11-master/build
cmake ..
make check -j 4
sudo make install