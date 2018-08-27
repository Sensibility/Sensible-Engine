#ifndef _SE_IMAGE_READER_H_
#define _SE_IMAGE_READER_H_
#include "ImageReader.h"
#include <cstdlib>
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

class SEImageReader : public ImageReader
{
public:
	Texture* LoadDDS(const char* pFile) override
	{
		unsigned char hdr[1024];
		FILE *fp;

		fp = fopen(pFile, "rb");
		if (fp == 0)
			return nullptr;

		char code[4];
		fread(code, 1, 4, fp);
		if(strncmp(code, "DDS ", 4) != 0)
		{
			fclose(fp);
			return nullptr;
		}

		fread(&hdr, 124, 1, fp);
		unsigned int height = *(unsigned int*)&(hdr[8]);
		unsigned int width = *(unsigned int*)&(hdr[12]);
		unsigned int linearSize = *(unsigned int*)&(hdr[16]);
		unsigned int mipMapCount = *(unsigned int*)&(hdr[24]);
		unsigned int fourCC = *(unsigned int*)&(hdr[80]);

		unsigned char * buffer;
		unsigned int bufsize;
		bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
		fread(buffer, 1, bufsize, fp);
		fclose(fp);

		unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
		unsigned int format;
		switch (fourCC)
		{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			free(buffer);
			return 0;
		}

		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int offset = 0;

		for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
		{
			unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
				0, size, buffer + offset);

			offset += size;
			width /= 2;
			height /= 2;
		}
		free(buffer);

		auto texture = new Texture(tex);

		return texture;
	};
	bool IsInit() override { return true; }
	std::string Str() override
	{
		return "SensibleEngine";
	}
};
#endif _SE_IMAGE_READER_H_