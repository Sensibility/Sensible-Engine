#ifndef _BASIC_OBJECT_H_
#define _BASIC_OBJECT_H_
#include "Object.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

std::string v_pass = SEString::Join(std::vector<std::string>{
	"#version 450 core",
	"layout(location = 0) in vec4 vPos_M;",
	"uniform mat4 MVP;",
	"void main() {",
	"gl_Position = MVP * vPos_M;",
"}"}, '\n');
std::string f_pass = SEString::Join(std::vector<std::string>{
	"#version 450 core",
	"uniform vec4 iColor;",
	"out vec4 color;",
	"void main() {",
	"color = iColor;",
"}"}, '\n');

enum DrawType {
	LINES,
	TRIS
};
class BasicObject : public Object
{
public:
	GLuint color_, mvp_;

	BasicObject() : BasicObject(TRIS) { }
	BasicObject(DrawType pType) : type_(pType){}
	BasicObject(DrawType pType, std::vector<glm::vec3> v) : vertices_(std::move(v)), type_(pType) {}
	void InitBuffers() override
	{
		auto shader = (ShaderProvider*)GetProvider<ShaderProvider>();
		shader->Register("BasicObject", ShaderBuilder::CreateShaderStr(v_pass, f_pass));
		shader_ = shader->Get("BasicObject");
		mvp_ = shader_->GetHandle("MVP");
		color_ = shader_->GetHandle("iColor");

		CreateVertexArray();
		CreateBuffers();
	}
	void Render() override {}
	void Render(glm::mat4 pMVP, glm::vec4 pColor)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		shader_->Activate();
		SEGL::ErrorCheck(__LINE__, __FILE__);
		BindAttributes();
		SEGL::ErrorCheck(__LINE__, __FILE__);
		glUniform4f(color_, pColor.x, pColor.y, pColor.z, pColor.w);
		glUniformMatrix4fv(mvp_, 1, GL_FALSE, glm::value_ptr(pMVP));
		SEGL::ErrorCheck(__LINE__, __FILE__);
		DrawBuffers();
		SEGL::ErrorCheck(__LINE__, __FILE__);
		DisableAttributes();
		SEGL::ErrorCheck(__LINE__, __FILE__);
	}
protected:
	DrawType type_;
	std::vector<glm::vec3 > vertices_;
	virtual void BindAttributes()
	{
		glBindVertexArray(vertexArray_);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vBuff_);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	virtual void DrawBuffers() 
	{
		glDrawArrays(GL_TRIANGLES, 0, vertices_.size());
		//glMultiDrawArrays
	}
	virtual void DisableAttributes() 
	{
		glDisableVertexAttribArray(0);
	}
	void CreateBuffers() override
	{
		glCreateBuffers(1, &vBuff_);
		glNamedBufferStorage(vBuff_, vertices_.size() * sizeof(glm::vec3), &vertices_[0], 0);
		SEGL::ErrorCheck(__LINE__, __FILE__);
	}
};

#endif _BASIC_OBJECT_H_