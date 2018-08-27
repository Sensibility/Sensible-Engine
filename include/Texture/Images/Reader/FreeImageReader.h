#ifndef _FREE_IMAGE_READER_H_
#define _FREE_IMAGE_READER_H_
#include "ImageReader.h"
#include <algorithm>
#include "FreeImage.h"
#include "../../FontTexture.h"

class FreeImageReader : public ImageReader
{
public:
	FreeImageReader() { FreeImage_Initialise(); }
	~FreeImageReader() { FreeImage_DeInitialise(); }
	Texture* LoadTGA(const char* pFile) override
	{
		auto fif = FIF_UNKNOWN;
		FIBITMAP *dib(0);
		BYTE* bits(0);
		unsigned int width(0), height(0);

		fif = FreeImage_GetFileType(pFile, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(pFile);
		//TARGA==TGA
		if (fif != FIF_TARGA)
			abort();

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, pFile);
		if (!dib)
			abort();

		bits = FreeImage_GetBits(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		if ((bits==0) || (width==0) || (height==0))
			abort();

		auto tex = new Texture(SEGL::GenerateTexture2D(height, width, bits, GL_RGB, GL_RGB, GL_LINEAR, GL_LINEAR));
		FreeImage_Unload(dib);
		return tex;
	};
	bool IsInit() override { return true; };
	std::string Str() override
	{
		return "FreeImage";
	}
};
#endif _FREE_IMAGE_READER_H_
