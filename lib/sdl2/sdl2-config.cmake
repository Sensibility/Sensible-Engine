if(WIN32)
	set(SDL2_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/lib/sdl2/include)

	if(${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(SDL2_DIR ${PROJECT_SOURCE_DIR}/lib/SDL2/lib/x64)
	else ()
		set(SDL2_DIR ${PROJECT_SOURCE_DIR}/lib/SDL2/lib/x86)
	endif()

	set(SDL2_LIBRARIES 
		${SDL2_DIR}/SDL2.lib
		${SDL2_DIR}/SDL2main.lib
		${SDL2_DIR}/SDL2_ttf.lib
		${SDL2_DIR}/SDL2_image.lib )
	set(SDL2_DLLS
		${SDL2_DIR}/SDL2_ttf.dll
		${SDL2_DIR}/SDL2_image.dll
		${SDL2_DIR}/zlib1.dll
		${SDL2_DIR}/libfreetype-6.dll
		${SDL2_DIR}/libjpeg-9.dll
		${SDL2_DIR}/libpng16-16.dll
		${SDL2_DIR}/libtiff-5.dll
		${SDL2_DIR}/libwebp-7.dll
		${SDL2_DIR}/SDL2.dll)

	set(DLLS 
		${DLLS}
		${SDL2_DLLS})

	string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
endif()
