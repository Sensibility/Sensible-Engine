#!/bin/sh

apt-get update
apt-get install gcc cmake -y
apt-get install mesa-common-dev -y
apt-get install freeglut3-dev -y
apt-get install libglew-dev -y
apt-get install libsdl2-dev -y
apt-get install libsdl-ttf2.0-0-dev -y
apt-get install libsdl-image2.0.0-dev -y

git submodule update --init