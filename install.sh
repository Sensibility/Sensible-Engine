#!/bin/sh

#Arch
pacman -S cmake
pacman -S mesa
pacman -S glew
pacman -S sdl2 sdl2-ttf sdl2-image
pacman -S freeimage
pacman -S freetype2
#Debian
apt-get update
apt-get install gcc cmake -y
apt-get install mesa-common-dev -y
apt-get install libglew-dev -y
apt-get install libsdl2-dev -y
apt-get install libsdl-ttf2.0-0-dev -y
apt-get install libsdl-image2.0.0-dev -y
apt-get install libfreeimage-dev -y
apt-get install libfreetype6-dev -y

git submodule update --init