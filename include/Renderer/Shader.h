#ifndef _SHADER_H
#define _SHADER_H

#ifdef _WIN32
	#include<windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
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
	virtual GLuint GetHandle(const char* pStr)
	{
		return glGetUniformLocation(program_, pStr);
	}

	virtual void CreateVertex(const char* pVertexShader)
	{
		vShader_ = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShader_, 1, &pVertexShader, nullptr);
		glCompileShader(vShader_);

		GLint compiled;
		glGetShaderiv(vShader_, GL_COMPILE_STATUS, &compiled);
		if(!compiled)
			GLSLGetShaderLog(vShader_);
	}

	virtual void CreateFragment(const char* pFragmentShader)
	{
		fShader_ = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShader_, 1, &pFragmentShader, nullptr);
		glCompileShader(fShader_);

		GLint compiled;
		glGetShaderiv(fShader_, GL_COMPILE_STATUS, &compiled);
		if(!compiled)
			GLSLGetShaderLog(fShader_);
	}

	virtual void CreateProgram()
	{
		program_ = glCreateProgram();
		SEGL::ErrorCheck(__LINE__, __FILE__);
		if(IsShader(vShader_))
			glAttachShader(program_, vShader_);
		if(IsShader(fShader_))
			glAttachShader(program_, fShader_);
		SEGL::ErrorCheck(__LINE__, __FILE__);

		glLinkProgram(program_);
		SEGL::ErrorCheck(__LINE__, __FILE__);

		GLint linked;
		glGetProgramiv(program_, GL_LINK_STATUS, &linked);
		if (!linked)
			GLSLGetProgramLog(program_);

		SEGL::ErrorCheck(__LINE__, __FILE__);
	}

	virtual void Activate()
	{
		glUseProgram(program_);
		SEGL::ErrorCheck(__LINE__, __FILE__);
	}
	virtual void Deactivate()
	{
		glUseProgram(0);
		SEGL::ErrorCheck(__LINE__, __FILE__);
	}

	virtual bool Validate()
	{
		glValidateProgram(program_);
		GLint status;
		glGetProgramiv(program_, GL_VALIDATE_STATUS, &status);

		return status;
	}

	virtual void SetDefaults()
	{
		//glVertexAttrib1v();
	}

	static bool IsShader(GLuint pShader) { return glIsShader(pShader); }
	static bool IsProgram(GLuint pProgram) { return glIsProgram(pProgram); }
protected:
	GLuint fShader_, vShader_, program_;
};

namespace ShaderBuilder
{
	Shader* CreateShaderStr(std::string pVertex, std::string pFragment)
	{
		auto shader = new Shader();
		shader->CreateVertex(pVertex.c_str());
		SEGL::ErrorCheck(__LINE__, __FILE__);
		shader->CreateFragment(pFragment.c_str());
		SEGL::ErrorCheck(__LINE__, __FILE__);
		shader->CreateProgram();
		SEGL::ErrorCheck(__LINE__, __FILE__);
		return shader;
	}
	Shader* CreateShader(const char* pVertexFile, const char* pFragmentFile)
	{
		return CreateShaderStr(File::ReadFileToStr(pVertexFile), File::ReadFileToStr(pFragmentFile));
	}

	Shader* CreateShaderFolder(std::string pFolder)
	{
		return CreateShader((pFolder + ".v.glsl").c_str(), (pFolder + ".f.glsl").c_str());
	}
}
#endif _SHADER_H
