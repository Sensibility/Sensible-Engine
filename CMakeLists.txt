cmake_minimum_required(VERSION 3.1)

project(main C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
option(DEBUG "output debug information")


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

if(DEBUG)
	get_cmake_property(_variableNames VARIABLES)
	list (SORT _variableNames)
	foreach (_variableName ${_variableNames})
		message(STATUS "${_variableName}=${${_variableName}}")
	endforeach()
endif()

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
file(GLOB_RECURSE SRC_HDR include/*.h include/Windows/*.h include/Scene/*.h include/Renderer/*.h include/Camera/*.h lib/tinyxml2/tinyxml2.h, lib/glm/glm/**/**.hpp)
file(GLOB_RECURSE SRC_CPP src/*.cpp src/Camera/*.cpp src/Scene/*.cpp lib/tinyxml2/tinyxml2.cpp)
add_executable(main main.cpp ${SRC_HDR}
        ${SRC_CPP})
target_link_libraries(main ${PACKAGE_LIBS})

IF(WIN32)
	foreach( dll ${SDL2_DLLS})
		add_custom_command(TARGET main POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
				${dll}
				$<TARGET_FILE_DIR:main>)
	endforeach(dll )

endif()

add_custom_command(TARGET main POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:main>/assets)
