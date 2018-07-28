set(SDL2_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/lib/sdl2/include)

if(${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	set(SDL2_LIBRARIES 
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/SDL2.lib
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/SDL2_ttf.lib
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/SDL2_image.lib
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/SDL2main.lib)
	set(SDL2_DLLS
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/SDL2_ttf.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/SDL2_image.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/zlib1.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/libfreetype-6.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/libjpeg-9.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/libpng16-16.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/libtiff-5.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/libwebp-7.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x64/SDL2.dll)
else ()
	set(SDL2_LIBRARIES 
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/SDL2.lib
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/SDL2_image.lib
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/SDL2_ttf.lib
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/SDL2main.lib)
	set(SDL2_DLLS
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/SDL2.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/SDL2_image.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/zlib1.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/libfreetype-6.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/libjpeg-9.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/libpng16-16.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/libtiff-5.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/libwebp-7.dll
		${PROJECT_SOURCE_DIR}/lib/sdl2/lib/x86/SDL2_ttf.dll )
endif()


string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
