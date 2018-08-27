#ifndef _OBJECT_PROVIDER_H_
#define _OBJECT_PROVIDER_H_
#include "../BaseProvider.h"
#include "Object.h"
#include "MultiTexObject.h"
#include "PassthruObject.h"

class ObjectProvider : public BaseProvider
{
public:
	template<class T>
	T* ReadInOBJ(const char* pFile)
	{
		FILE* fp = fopen(pFile, "r");

		if(fp != nullptr)
		{
			std::vector<glm::vec3 > vertices;
			std::vector<glm::vec3 > normals;
			std::vector<glm::vec2 > uvs;
			std::vector<unsigned int> vIndicies, uvIndicies, normalIndicies;
			while(true)
			{
				char lineHdr[255];
				int res = fscanf(fp, "%s", lineHdr);
				if (res == EOF)
					break;

				if(strcmp(lineHdr, "v") == 0)
				{
					float x, y, z;
					fscanf(fp, "%f %f %f\n", &x, &y, &z);
					vertices.push_back(glm::vec3(x, y, z));
				}
				else if (strcmp(lineHdr, "vt") == 0)
				{
					float u, v;
					fscanf(fp, "%f %f\n", &u, &v);
					//DDS files only
					v = -v;
					uvs.push_back(glm::vec2(u, v));
				}
				else if (strcmp(lineHdr, "vn") == 0)
				{
					float x, y, z;
					fscanf(fp, "%f %f %f\n", &x, &y, &z);
					normals.push_back(glm::vec3(x, y, z));
				}
				else if (strcmp(lineHdr, "f") == 0)
				{
					unsigned int index[9] = {0};

					if(fgets(lineHdr, sizeof(lineHdr), fp) != nullptr)
					{
						int matches = sscanf(lineHdr, " %d/%d/%d %d/%d/%d %d/%d/%d\n", index, index+1, index+2, index+3, index+4, index+5, index+6, index+7, index+8);
						assert(matches == 9);
					}

					for(int i = 0; i < 9; ++i)
					{
						if(index[i])
						{
							if ((i-2) % 3 == 0)
								normalIndicies.push_back(index[i]);
							else if ((i-1) % 3 == 0)
								uvIndicies.push_back(index[i]);
							else
								vIndicies.push_back(index[i]);
						}
					}
				}
			}
			std::vector<glm::vec3> v;
			std::vector<glm::vec2> uv;
			std::vector<glm::vec3> n;
			for (unsigned int vindex : vIndicies)
			{
				if(vindex)
					v.push_back(vertices.at(vindex-1));
			}
			for (unsigned int uvindex : uvIndicies)
			{
				if(uvindex)
					uv.push_back(uvs[uvindex - 1]);
			}
			for (unsigned int nindex : normalIndicies)
			{
				if(nindex)
					n.push_back(normals[nindex - 1]);
			}

			return new T(v, uv, n);
		}
	}

	PassthruObject* CreateObj(std::vector<glm::vec4 > pData, Texture* texture)
	{
		auto obj = new PassthruObject(pData, texture);
		obj->InitBuffers();
		return obj;
	}

	std::string GetKey() override { return GetKeyStatic(); };
	static std::string GetKeyStatic() { return "ObjectProvider"; }
private:
};

#endif _OBJECT_PROVIDER_H_