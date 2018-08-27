#ifndef _FFP_GL_H_
#define _FFP_GL_H_

#include "GL/glew.h"
#include "../OpenGL.h"

namespace SEGL {
namespace FFP {
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
	ErrorCheck(__LINE__);
}

//3+
bool BlendingEnabledOnBuffer(GLuint pBufferIndex)
{
	return glIsEnabledi(GL_BLEND, pBufferIndex) == GL_TRUE;
}

void EnableBlendingOnBuffer(GLuint pBufferIndex)
{
	glEnablei(GL_BLEND, pBufferIndex);
	ErrorCheck(__LINE__, __FILE__);
}

void DisableBlendingOnBuffer(GLuint pBufferIndex)
{
	glDisablei(GL_BLEND, pBufferIndex);
	ErrorCheck(__LINE__, __FILE__);
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
		ErrorCheck(__LINE__, __FILE__);
	}
}

void DeleteQueryObject(GLuint pId)
{
	if(IsQuery(pId))
	{
		glDeleteQueries(1, &pId);
		ErrorCheck(__LINE__, __FILE__);
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

		ErrorCheck(__LINE__, __FILE__);

		return samples;
	}
	return 0;
}
} }

#endif _FFP_GL_H_