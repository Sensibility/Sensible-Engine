#ifndef _SE_VECTOR_H_
#define _SE_VECTOR_H_
#include <vector>
#include "glm/glm.hpp"

namespace SEVector
{
	template <typename T>
	void ToCArray(std::vector<glm::vec4> pArr, T** res)
	{
		int vec = 4;
		int size = sizeof(T) * vec;
		(*res) = (T*)malloc(pArr.size() * size);
		for(int i = 0; i < pArr.size(); ++i)
		{
			(*res)[i * vec] = pArr[i].x;
			(*res)[i * vec + 1] = pArr[i].y;
			(*res)[i * vec + 2] = pArr[i].z;
			(*res)[i * vec + 3] = pArr[i].w;
		}
	}
}

#endif _SE_VECTOR_H_