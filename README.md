# Sensible-Engine


## Install
* Make sure your graphics card drivers are up to date.

### Debian
* Run install.sh

### Windows
* Work In Progress - GL HF
* Install the Visual Studio of your choice, make sure to install CMake in the installer.
* Download the devel packages for SDL, GLUT, GLEW and extract them to the lib folder

## Compile

### Debian
* Run `cmake .`
* Run `make`

### Windows
* Open a folder with Visual Studio.
* CMakeLists should automatically be detected and compiled.


## Notes
* windows.h has to be included before gl to work on Windows.