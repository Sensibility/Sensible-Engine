set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 3.1)

project(main C CXX)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -g -std=c++17 -pthread")


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_library(SOIL SOIL REQUIRED)
find_library(SDL2_LIBRARY REQUIRED)


set(PACKAGE_DIRS
        ${OPENGL_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIRS}
        )
set(PACKAGE_LIBS
        ${OPENGL_LIBRARY}
        ${GLUT_LIBRARY}
        ${GLEW_LIBRARY}
        ${SDL2_LIBRARIES}
        ${SOIL}
        )

FILE(GLOB HDRS *.h include/*.h include/Camera/*.h include/Windows/*.h)

include_directories(${PACKAGE_DIRS})
add_executable(main main.cpp ${HDRS}
        src/console.cpp src/pointbase.cpp src/point.cpp src/vector.cpp src/matrix.cpp src/Camera/arcCamera.cpp src/Camera/fpCamera.cpp src/Camera/Camera.cpp src/Camera/baseCamera.cpp)
target_link_libraries(main ${PACKAGE_LIBS})

