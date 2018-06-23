set(SDL2_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/lib/sdl2/include)

if(${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	set(SDL2_LIBRARIES 
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/SDL2.lib
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/SDL2main.lib)
	set(SDL2_DLL
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/SDL2.dll)
else ()
	set(SDL2_LIBRARIES 
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/SDL2.lib
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/SDL2main.lib)
	set(SDL2_DLL
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/SDL2.dll)
endif()


string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
