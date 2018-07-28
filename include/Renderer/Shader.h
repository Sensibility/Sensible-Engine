#ifndef _SHADER_H
#define _SHADER_H

#include "GL/glew.h"
#include "OpenGL.h"
#include <cassert>
#include "../File.h"

void GLSLGetShaderLog(GLuint pShader)
{
		GLint length;
		glGetShaderiv(pShader, GL_INFO_LOG_LENGTH, &length);
		auto log = (GLchar*)malloc(length);
		glGetShaderInfoLog(pShader, length, &length, log);
		fprintf(stderr, "shader error %s\n", log);
		free(log);
}
void GLSLGetProgramLog(GLuint pShader)
{
		GLint length;
		glGetProgramiv(pShader, GL_INFO_LOG_LENGTH, &length);
		auto log = (GLchar*)malloc(length);
		glGetProgramInfoLog(pShader, length, &length, log);
		fprintf(stderr, "program error %s\n", log);
		free(log);
}

class Shader
{
public:

	void CreateAndCompile(GLenum pType, const char* pSrc)
	{
		assert(pType == GL_VERTEX_SHADER || pType == GL_FRAGMENT_SHADER);
		vShader_ = glCreateShader(pType);
		glShaderSource(vShader_, 1, &pSrc, nullptr);
		glCompileShader(vShader_);

		GLint compiled;
		glGetShaderiv(vShader_, GL_COMPILE_STATUS, &compiled);
		if(!compiled)
			GLSLGetShaderLog(vShader_);

	}

	void CreateVertex(const char* pVertexShader)
	{
		vShader_ = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShader_, 1, &pVertexShader, nullptr);
		glCompileShader(vShader_);

		GLint compiled;
		glGetShaderiv(vShader_, GL_COMPILE_STATUS, &compiled);
		if(!compiled)
			GLSLGetShaderLog(vShader_);
	}

	void CreateFragment(const char* pFragmentShader)
	{
		fShader_ = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShader_, 1, &pFragmentShader, nullptr);
		glCompileShader(fShader_);

		GLint compiled;
		glGetShaderiv(fShader_, GL_COMPILE_STATUS, &compiled);
		if(!compiled)
			GLSLGetShaderLog(fShader_);
	}

	void CreateProgram()
	{
		program_ = glCreateProgram();
		if(IsShader(vShader_))
			glAttachShader(program_, vShader_);
		if(IsShader(fShader_))
			glAttachShader(program_, fShader_);

		glLinkProgram(program_);

		GLint linked;
		glGetProgramiv(program_, GL_LINK_STATUS, &linked);
		if (!linked)
			GLSLGetProgramLog(program_);

		GLErrorCheck(__LINE__, __FILE__);
	}

	void Activate()
	{
		glUseProgram(program_);
		GLErrorCheck(__LINE__, __FILE__);
	}
	void Deactivate()
	{
		glUseProgram(0);
		GLErrorCheck(__LINE__, __FILE__);
	}

	bool Validate()
	{
		glValidateProgram(program_);
		GLint status;
		glGetProgramiv(program_, GL_VALIDATE_STATUS, &status);

		return status;
	}

	static bool IsShader(GLuint pShader) { return glIsShader(pShader); }
	static bool IsProgram(GLuint pProgram) { return glIsProgram(pProgram); }
private:
	GLuint fShader_, vShader_, program_;
};

namespace ShaderBuilder
{
	Shader* CreateShader(const char* pVertexFile, const char* pFragmentFile)
	{
		auto shader = new Shader();
		shader->CreateVertex(File::ReadFileToStr(pVertexFile).c_str());
		shader->CreateFragment(File::ReadFileToStr(pFragmentFile).c_str());
		shader->CreateProgram();
		return shader;
	}
}
#endif _SHADER_H
