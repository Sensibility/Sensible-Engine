#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "glm/detail/type_vec3.hpp"
#include <utility>
#include <vector>
#include "GL/glew.h"
#include "../Renderer/OpenGL.h"
#include "../Renderer/Shader.h"
#include "../Shaders/ShaderProvider.h"

class Object
{
public:
	Object() {}
	Object(std::string shaderName)
	{
		auto prov = (ShaderProvider*)GetProvider<ShaderProvider>();
		shader_ = prov->Get(shaderName);
	}
	virtual void InitBuffers() = 0;
	virtual void Render() {}
	static bool IsBuffer(GLuint buff) { return glIsBuffer(buff); }
	static bool IsVertexBuffer(GLuint buff) { return glIsVertexArray(buff); }
protected:
	GLuint vertexArray_, vBuff_;
	Shader* shader_;
	Texture* tex_;

	virtual void CreateVertexArray()
	{
		glCreateVertexArrays(1, &vertexArray_);
		glBindVertexArray(vertexArray_);
		SEGL::ErrorCheck(__LINE__, __FILE__);
	}
	virtual void CreateBuffers() {};
};

#endif _OBJECT_H_