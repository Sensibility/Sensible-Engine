#ifndef OPEN_GL_H_
#define OPEN_GL_H_

#ifdef _WIN32
#include <windows.h>
#endif

#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>


inline void GLErrorCheck(int lineNum, const char* pFile = nullptr) {
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
	GLErrorCheck(__LINE__, __FILE__);
}

inline void DrawFog()
{
	glEnable(GL_FOG);
	GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1 };
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.1);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, 40.0);
	glFogf(GL_FOG_END, 600.0);
	GLErrorCheck(__LINE__);
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
inline GLuint GenerateTexture2D(int pHeight, int pWidth, void* pPixels,
		GLenum pColor = GL_RGBA,
		GLint pMinFilter = GL_LINEAR,
		GLint pMagFilter = GL_LINEAR,
		GLint pWrapS = GL_REPEAT,
		GLint pWrapT = GL_REPEAT)
{
	glEnable(GL_TEXTURE_2D);
	bool c = CanCreateTexture2D(pHeight, pWidth, pColor);
	GLuint tex = 0;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pMagFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, pWrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, pWrapT);
	glTexImage2D(GL_TEXTURE_2D, 0, pColor, pWidth, pHeight, 
		0, pColor, GL_UNSIGNED_BYTE, pPixels);

	glDisable(GL_TEXTURE_2D);
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

//3+
bool BlendingEnabledOnBuffer(GLuint pBufferIndex)
{
	return glIsEnabledi(GL_BLEND, pBufferIndex) == GL_TRUE;
}

void EnableBlendingOnBuffer(GLuint pBufferIndex)
{
	glEnablei(GL_BLEND, pBufferIndex);
	GLErrorCheck(__LINE__, __FILE__);
}

void DisableBlendingOnBuffer(GLuint pBufferIndex)
{
	glDisablei(GL_BLEND, pBufferIndex);
	GLErrorCheck(__LINE__, __FILE__);
}

//1.5+
GLuint GenerateQueryObject() {
	GLuint id;
	glGenQueries(1, &id);

	return id;
}

bool IsQuery(GLuint pId) { return glIsQuery(pId) == GL_TRUE; }

void BeginQueryObject(GLuint pId)
{
	if(IsQuery(pId))
	{
		glBeginQuery(GL_SAMPLES_PASSED, pId);
		GLErrorCheck(__LINE__, __FILE__);
	}
}

void DeleteQueryObject(GLuint pId)
{
	if(IsQuery(pId))
	{
		glDeleteQueries(1, &pId);
		GLErrorCheck(__LINE__, __FILE__);
	}
}

GLuint CloseQueryObject(GLuint* pId)
{
	if(IsQuery(*pId))
	{
		glEndQuery(GL_SAMPLES_PASSED);

		int count = 100, samples = 0;
		GLint queryReady = false;
		while(!queryReady && count--)
		{
			glGetQueryObjectiv(*pId, GL_QUERY_RESULT_AVAILABLE, &queryReady);
		}

		if(queryReady == GL_TRUE)
		{
			glGetQueryObjectiv(*pId, GL_QUERY_RESULT, &samples);
		}
		else
		{
			samples = 1;
			fprintf(stderr, "Unable to get query results for %i\n", *pId);
		}
		glDeleteQueries(1, pId);
		pId = nullptr;

		GLErrorCheck(__LINE__, __FILE__);

		return samples;
	}
	return 0;
}



vector<string*>* BufferDiagnostics()
{
	auto diags = new vector<string*>();

	string* str = new string[2];
	GLint r, g, b, a;
	glGetIntegerv(GL_RED_BITS, &r);
	glGetIntegerv(GL_BLUE_BITS, &b);
	glGetIntegerv(GL_GREEN_BITS, &g);
	glGetIntegerv(GL_ALPHA_BITS, &a);
	str[0] = "R G B A";
	char buff[100];
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

	GLboolean stero, doubleBuff; 
	GLint index, depth, stencil;

	glGetBooleanv(GL_STEREO, &stero);
	str = new string[2];
	str[0] = "Stereo Buffer?";
	str[1] = stero ? "Y" : "N";
	diags->push_back(str);

	glGetBooleanv(GL_DOUBLEBUFFER, &doubleBuff);
	str = new string[2];
	str[0] = "Double Buffer?";
	str[1] = doubleBuff ? "Y" : "N";
	diags->push_back(str);


	glGetIntegerv(GL_DOUBLEBUFFER, &index);
	str = new string[2];
	str[0] = "Index Bits";
	snprintf(buff, sizeof(buff), "%i", index);
	str[1] = buff;
	diags->push_back(str);

	glGetIntegerv(GL_DOUBLEBUFFER, &depth);
	str = new string[2];
	str[0] = "Depth Bits";
	snprintf(buff, sizeof(buff), "%i", depth);
	str[1] = buff;
	diags->push_back(str);

	glGetIntegerv(GL_STENCIL_BITS, &stencil);
	str = new string[2];
	str[0] = "Stencil Bits";
	snprintf(buff, sizeof(buff), "%i", stencil);
	str[1] = buff;
	diags->push_back(str);

	return diags;
}
#endif OPEN_GL_H_