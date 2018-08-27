if(WIN32)
	set(FREEIMAGE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/lib/freeimage/include)

	if(${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(FREEIMAGE_FOLDER ${PROJECT_SOURCE_DIR}/lib/freeimage/lib/x64)
	else()
		set(FREEIMAGE_FOLDER ${PROJECT_SOURCE_DIR}/lib/freeimage/lib/x32)
	endif()

	set(FREEIMAGE_LIBRARIES
		${FREEIMAGE_FOLDER}/FreeImage.lib)
	set(FREEIMAGE_DLLS
		${FREEIMAGE_FOLDER}/FreeImage.dll)

	set(DLLS
		${DLLS}
		${FREEIMAGE_DLLS})

endif()