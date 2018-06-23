set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 3.1)

project(main C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


IF(WIN32)
    set(SDL2_DIR lib/sdl2)
	list(APPEND CMAKE_PREFIX_PATH lib/glew)
	list(APPEND CMAKE_PREFIX_PATH lib/glut)
    set(GLUT_INCLUDE_DIR lib/glut/include)
	set(GLEW_INCLUDE_DIR lib/glew/include)
ENDIF()


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
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
        )

include_directories(${PACKAGE_DIRS})
add_executable(main main.cpp 
        src/pointbase.cpp src/point.cpp src/vector.cpp src/matrix.cpp src/Camera/arcCamera.cpp src/Camera/fpCamera.cpp src/Camera/Camera.cpp src/Camera/baseCamera.cpp include/math.h)
target_link_libraries(main ${PACKAGE_LIBS})

IF(WIN32)
	add_custom_command(TARGET main POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${SDL2_DLL}"
			$<TARGET_FILE_DIR:main>)

endif()