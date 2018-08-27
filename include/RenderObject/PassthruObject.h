#ifndef _PASSTHRU_OBJECT_H_
#define _PASSTHRU_OBJECT_H_
#include "Object.h"
#include "../SEVector.h"

class ObjectProvider;

class PassthruObject : public Object
{
	friend ObjectProvider;
public:
	PassthruObject(std::vector<glm::vec4> pData, Texture* tex) : Object() 
	{
		tex_ = tex;
		size_ = sizeof(GLfloat) * 4;
		count_ = pData.size();
		SEVector::ToCArray<GLfloat>(pData, &v_);
	}
	~PassthruObject()
	{
		free(v_);
	}
	void InitBuffers() override
	{
		CreateVertexArray();
		CreateBuffers();
		BindDefault();
		SEGL::ErrorCheck(__LINE__, __FILE__);
	}
	virtual void BeginRender()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindVertexArray(vertexArray_);
		glBindBuffer(GL_ARRAY_BUFFER, vBuff_);
		glActiveTexture(GL_TEXTURE0);

		glBufferData(GL_ARRAY_BUFFER, count_ * size_, 0, GL_DYNAMIC_DRAW);
	}
	void Render() override
	{
		glBindTexture(GL_TEXTURE_2D, tex_->_Handle());
		glBufferSubData(GL_ARRAY_BUFFER, 0, count_ * size_, v_);
		glDrawArrays(GL_TRIANGLES, 0, count_);
	}
	virtual void EndRender()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
protected:
	void CreateBuffers() override
	{
		assert(IsVertexBuffer(vertexArray_));
		assert(size_ > 0 && count_ > 0);

		glCreateBuffers(1, &vBuff_);
		glBindVertexArray(vertexArray_);
		glBindBuffer(GL_ARRAY_BUFFER, vBuff_);
		glBufferData(GL_ARRAY_BUFFER, size_ * count_, nullptr, GL_DYNAMIC_DRAW);
	}

	virtual void BindDefault()
	{
		assert(IsBuffer(vBuff_));
		assert(size_ > 0);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, size_, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	int size_;
	int count_;
	GLfloat* v_;
};

#endif _PASSTHRU_OBJECT_H_