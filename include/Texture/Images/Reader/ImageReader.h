#ifndef _IMAGE_READER_H_
#define _IMAGE_READER_H_
#include "../../Textures.h"
#include <cstdio>

class ImageReader
{
public:
	virtual Texture* LoadPNG(const char* pFile) { fprintf(stderr, "CANNOT LOAD PNG %s\n", Str().c_str()); return nullptr; };
	virtual Texture* LoadTGA(const char* pFile) { fprintf(stderr, "CANNOT LOAD TGA %s\n", Str().c_str()); return nullptr; };
	virtual Texture* LoadDDS(const char* pFile) { fprintf(stderr, "CANNOT LOAD DDS %s\n", Str().c_str()); return nullptr; };
	virtual bool IsInit() = 0;
	virtual std::string Str() = 0;
};
#endif _IMAGE_READER_H_
