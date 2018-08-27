#ifndef _MULTI_TEX_OBJECT_H_
#define _MULTI_TEX_OBJECT_H_
#include "Object.h"
#include "BasicObject.h"

class MultiTexObject : public BasicObject
{
public:
	MultiTexObject(std::vector<glm::vec3> v, std::vector<glm::vec2> uv, std::vector<glm::vec3> n)
		: normals_(std::move(n)), uvs_(std::move(uv)), BasicObject(TRIS, v)
	{
		CalculateTangents();
	}

	void BindAttributes() override
	{
		BasicObject::BindAttributes();
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuff_);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, nBuff_);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, tanBuff_);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, biTanBuff_);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	void DisableAttributes() override
	{
		BasicObject::DisableAttributes();
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
	}

	void CalculateTangents()
	{
		for(int i = 0; i < vertices_.size(); i+=3)
		{
			glm::vec3 dPos1 = vertices_[i+1] - vertices_[i];
			glm::vec3 dPos2 = vertices_[i + 2] - vertices_[i];

			glm::vec2 dUV1 = uvs_[i + 1] - uvs_[i];
			glm::vec2 dUV2 = uvs_[i + 2] - uvs_[i];

			float r = 1.0f / (dUV1.x * dUV2.y - dUV1.y * dUV2.x);
			glm::vec3 tangent = (dPos1 * dUV2.y - dPos2 * dUV1.y)*r;
			glm::vec3 bitangent = (dPos2 * dUV1.x - dPos1 * dUV2.x)*r;

			for(int j = 0; j < 3; ++j)
			{
				tangents_.push_back(tangent);
				bitangents_.push_back(bitangent);
			}
		}

		for(int i = 0; i < vertices_.size(); i+=1)
		{
			glm::vec3& n = normals_[i];
			glm::vec3& t = tangents_[i];
			glm::vec3& b = bitangents_[i];

			t = glm::normalize(t - n * glm::dot(n, t));
			if(glm::dot(glm::cross(n, t), b) < 0.0f)
			{
				t *= -1.0f;
			}
			tangents_[i] = t;
		}
	}
private:
	GLuint vBuff_, nBuff_, uvBuff_, tanBuff_, biTanBuff_;
	std::vector<glm::vec3 > normals_;
	std::vector<glm::vec2 > uvs_;
	std::vector<glm::vec3 > bitangents_, tangents_;

	void CreateBuffers() override
	{
		BasicObject::CreateBuffers();

		glCreateBuffers(1, &uvBuff_);
		glNamedBufferStorage(uvBuff_, uvs_.size() * sizeof(glm::vec2), &uvs_[0], 0);

		glCreateBuffers(1, &nBuff_);
		glNamedBufferStorage(nBuff_, normals_.size() * sizeof(glm::vec3), &normals_[0], 0);

		glCreateBuffers(1, &tanBuff_);
		glNamedBufferStorage(tanBuff_, normals_.size() * sizeof(glm::vec3), &tangents_[0], 0);

		glCreateBuffers(1, &biTanBuff_);
		glNamedBufferStorage(biTanBuff_, normals_.size() * sizeof(glm::vec3), &bitangents_[0], 0);
		SEGL::ErrorCheck(__LINE__, __FILE__);

	};
};

#endif _MULTI_TEX_OBJECT_H_