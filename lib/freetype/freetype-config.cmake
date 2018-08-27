IF(WIN32)
	set(FREETYPE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/lib/freetype/include)
	if(${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(FREETYPE_FOLDER ${PROJECT_SOURCE_DIR}/lib/freetype/win64)
	else()
		set(FREETYPE_FOLDER ${PROJECT_SOURCE_DIR}/lib/freetype/win32)
	endif()

	set(FREETYPE_LIBRARY
		${FREETYPE_FOLDER}/freetype.lib)
	set(FREETYPE_DLLS
		${FREETYPE_FOLDER}/freetype.dll)

	message(STATUS ${FREETYPE_LIBRARY})

	set(DLLS
		${DLLS}
		${FREETYPE_DLLS})
ENDIF()