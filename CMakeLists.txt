cmake_minimum_required(VERSION 3.1)

project(main C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
option(DEBUG "output debug information")
option(TESTS "run unit tests")


IF(WIN32)
    set(SDL2_DIR lib/sdl2)
	set(FREEIMAGE_DIR lib/freeimage)
	set(FREETYPE_DIR lib/freetype)
	list(APPEND CMAKE_PREFIX_PATH lib/glew)
	set(GLEW_INCLUDE_DIR lib/glew/include)
ENDIF()


set(GLM_INCLUDE_DIR lib/glm)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(FREEIMAGE REQUIRED)
find_package(FREETYPE REQUIRED
	HINTS ${FREETYPE_DIR})

if(DEBUG)
	get_cmake_property(_variableNames VARIABLES)
	list (SORT _variableNames)
	foreach (_variableName ${_variableNames})
		message(STATUS "${_variableName}=${${_variableName}}")
	endforeach()
endif()

set(PACKAGE_DIRS
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIRS}
		${TEST_INCLUDE_DIR}
		${GLM_INCLUDE_DIR}
		${FREEIMAGE_INCLUDE_DIRS}
		${FREETYPE_INCLUDE_DIRS}
        )
set(PACKAGE_LIBS
        ${OPENGL_LIBRARY}
        ${GLEW_LIBRARY}
        ${SDL2_LIBRARIES}
		${FREEIMAGE_LIBRARIES}
		${FREETYPE_LIBRARY}
        )
				
include_directories(${PACKAGE_DIRS})
set(SRC_HDR_FILES ${CMAKE_SOURCE_DIR}/include/**/*.h ${CMAKE_SOURCE_DIR}/lib/tinyxml2/tinyxml2.h)
set(SRC_CPP_FILES lib/tinyxml2/tinyxml2.cpp)

file(GLOB_RECURSE SRC_HDR ${SRC_HDR_FILES})
file(GLOB_RECURSE SRC_CPP ${SRC_CPP_FILES})

add_executable(main main.cpp ${SRC_HDR}
        ${SRC_CPP})
target_link_libraries(main ${PACKAGE_LIBS})

IF(WIN32)
	foreach( dll ${DLLS})
		add_custom_command(TARGET main PRE_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
				${dll}
				$<TARGET_FILE_DIR:main>)
	endforeach(dll )
endif()

add_custom_command(TARGET main POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:main>/assets)
