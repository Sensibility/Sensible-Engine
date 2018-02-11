set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 2.9)

project(main C CXX)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -g -std=c++17 -pthread")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_library(SOIL SOIL REQUIRED)

set(PACKAGE_DIRS
        ${OPENGL_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR})
set(PACKAGE_LIBS
        ${OPENGL_LIBRARY}
        ${GLUT_LIBRARY}
        ${GLEW_LIBRARY})

FILE(GLOB HDRS *.h include/Camera/*.h include/*.h)

include_directories(${PACKAGE_DIRS})
add_executable(main main.cpp ${HDRS} src/Camera/baseCamera.cpp src/matrix.cpp src/vector.cpp src/point.cpp src/pointbase.cpp src/console.cpp src/Camera/arcCamera.cpp src/Camera/fpCamera.cpp src/Camera/Camera.cpp include/Camera/Camera.h)
target_link_libraries(main ${PACKAGE_LIBS} ${SOIL})

