#ifndef OPEN_GL_H_
#define OPEN_GL_H_

#ifdef _WIN32
#include <windows.h>
#endif

#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cstdio>

#define GL_GPU_MEM_DED_AVAILABLE_NVX 0x9047
#define GL_GPU_MEM_TOTAL_AVAILABLE_NVX 0x9048
#define GL_GPU_MEM_CURRENT_AVAILABLE_NVX 0x9049

namespace SEGL
{
inline void ErrorCheck(int lineNum, const char* pFile = nullptr) {
	const auto err = glGetError();
	if (err != GL_NO_ERROR)
	{
		auto errStr = gluErrorString(err);
		fprintf( stderr, "ERR: %s, %i %s\n", (char*)errStr, lineNum, pFile );
	}
}

//OpenGl 3+
inline void GenerateMipMap(GLuint pTextureHandle, GLenum pTarget)
{
	glBindTexture(pTarget, pTextureHandle);
	glGenerateMipmap(pTarget);
	ErrorCheck(__LINE__, __FILE__);
}

//Doesnt consider texture residency in high performance specialized hardware
inline bool CanCreateTexture2D(int pHeight, int pWidth, GLenum pColor)
{
	glTexImage2D(GL_PROXY_TEXTURE_2D, 0, pColor, pWidth, pHeight, 0, pColor, GL_UNSIGNED_BYTE, nullptr);
	int width;
	glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);

	return width != 0;
}

//h/w must be powers of 2
template<class T>
inline GLuint GenerateTexture2D(int pHeight, int pWidth, T pPixels,
		GLenum pColor = GL_RGBA,
		GLenum pInternalColor = GL_RGBA,
		GLint pMinFilter = GL_LINEAR,
		GLint pMagFilter = GL_LINEAR,
		GLint pWrapS = GL_REPEAT,
		GLint pWrapT = GL_REPEAT)
{
	bool c = CanCreateTexture2D(pHeight, pWidth, pColor);
	GLuint tex;
	glGenTextures(1, &tex);
	SEGL::ErrorCheck(__LINE__, __FILE__);
	glBindTexture(GL_TEXTURE_2D, tex);
	SEGL::ErrorCheck(__LINE__, __FILE__);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pMagFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, pWrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, pWrapT);
	SEGL::ErrorCheck(__LINE__, __FILE__);
	glTexImage2D(GL_TEXTURE_2D, 0, pInternalColor, pWidth, pHeight, 
		0, pColor, GL_UNSIGNED_BYTE, (T)pPixels);

	SEGL::ErrorCheck(__LINE__, __FILE__);

	return tex;
}
void* SampleTexture2D(int height, int width, bool pSub)
{
	int *tex = (int *)malloc(height * width * 4 * sizeof(int));
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			int c = ((i & (pSub ? 0x4 : 0x8)) == 0 ^ (j & (pSub ? 0x4 : 0x8)) == 0) * 255;
			auto loc = (tex + i * width * 4 + j * 4);
			*(loc) = (GLubyte)c;
			*(loc + 1) = (GLubyte) (pSub ? 0 : c);
			*(loc + 2) = (GLubyte) (pSub ? 0 : c);
			*(loc + 3) = (GLubyte)255;
		}
	}

	return tex;
}

std::vector<std::string*>* BufferDiagnostics()
{
	auto diags = new std::vector<std::string*>();

	std::string* str = new std::string[2];
	char buff[100];
	/*
	GLint r, g, b, a;
	glGetIntegerv(GL_RED_BITS, &r);
	glGetIntegerv(GL_BLUE_BITS, &b);
	glGetIntegerv(GL_GREEN_BITS, &g);
	glGetIntegerv(GL_ALPHA_BITS, &a);
	str[0] = "R G B A";
	snprintf(buff, sizeof(buff), "%i %i %i %i Bits", r, g, b, a);
	str[1] = buff;
	diags->push_back(str);

	str = new string[2];
	glGetIntegerv(GL_ACCUM_RED_BITS, &r);
	glGetIntegerv(GL_ACCUM_BLUE_BITS, &b);
	glGetIntegerv(GL_ACCUM_GREEN_BITS, &g);
	glGetIntegerv(GL_ACCUM_ALPHA_BITS, &a);
	str[0] = "AR AG AB AA";
	snprintf(buff, sizeof(buff), "%i %i %i %i Bits", r, g, b, a);
	str[1] = buff;
	diags->push_back(str);
	*/

	GLboolean stero, doubleBuff; 
	GLint index, depth, stencil;

	glGetBooleanv(GL_STEREO, &stero);
	str = new std::string[2];
	str[0] = "Stereo Buffer?";
	str[1] = stero ? "Y" : "N";
	diags->push_back(str);

	glGetBooleanv(GL_DOUBLEBUFFER, &doubleBuff);
	str = new std::string[2];
	str[0] = "Double Buffer?";
	str[1] = doubleBuff ? "Y" : "N";
	diags->push_back(str);


	glGetIntegerv(GL_DOUBLEBUFFER, &index);
	str = new std::string[2];
	str[0] = "Index Bits";
	snprintf(buff, sizeof(buff), "%i", index);
	str[1] = buff;
	diags->push_back(str);

	glGetIntegerv(GL_DOUBLEBUFFER, &depth);
	str = new std::string[2];
	str[0] = "Depth Bits";
	snprintf(buff, sizeof(buff), "%i", depth);
	str[1] = buff;
	diags->push_back(str);

	/*
	glGetIntegerv(GL_STENCIL_BITS, &stencil);
	str = new string[2];
	str[0] = "Stencil Bits";
	snprintf(buff, sizeof(buff), "%i", stencil);
	str[1] = buff;
	diags->push_back(str);
	*/

	return diags;
}
}
#endif OPEN_GL_H_