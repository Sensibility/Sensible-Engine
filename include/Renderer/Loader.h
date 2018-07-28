#ifndef _LOADER_H_
#define _LOADER_H_
#include <cstdio>
#include "../PointBase.h"
#include <vector>
#include "../Pnt.h"
#include "GL/glew.h"

class OBJObject 
{
public:
	using Vec3 = Pnt3<float>;
	OBJObject(const char* pFile)
	{
		FILE* fp = fopen(pFile, "r");

		if(fp != nullptr)
		{
			std::vector<Pnt3<float> > vertices;
			std::vector<Pnt3<float> > normals;
			std::vector<Pnt2<float> > uvs;
			std::vector<unsigned int> vIndicies, uvIndicies, normalIndicies;
			while(1)
			{
				char lineHdr[255];
				int res = fscanf(fp, "%s", lineHdr);
				if (res == EOF)
					break;

				if((lineHdr == "v") == 0)
				{
					float x, y, z;
					fscanf(fp, "%f %f %f\n", &x, &y, &z);
					vertices.push_back(Pnt3<float>(x, y, z));
				}
				else if (lineHdr == "vt" == 0)
				{
					float u, v;
					fscanf(fp, "%f %f\n", &u, &v);
					uvs.push_back(Pnt2<float>(u, v));
				}
				else if (lineHdr == "vn" == 0)
				{
					float x, y, z;
					fscanf(fp, "%f %f %f\n", &x, &y, &z);
					normals.push_back(Pnt3<float>(x, y, z));
				}
				else if (lineHdr == "f" == 0)
				{
					std::string v1, v2, v3;
					unsigned int index[9];

					int matches = fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &index[0], &index[3], &index[6]);
					assert(matches == 9);

					for(int i = 0; i < 9; ++i)
					{
						if (i > 5)
							normalIndicies.push_back(index[i]);
						else if (i > 2)
							uvIndicies.push_back(index[i]);
						else
							vIndicies.push_back(index[i]);
					}
				}
			}

			//objs start at 1 >:
			for(auto& index: vIndicies)
				vertices_.push_back(vertices[index - 1]);
			for(auto& index: uvIndicies)
				uvs_.push_back(uvs[index - 1]);
			for(auto& index: normalIndicies)
				normals_.push_back(normals[index - 1]);

			GenerateBuffer();
		}
		
	}

	void GenerateBuffer()
	{
		glGenBuffers(1, &vBuff_);
		glBindBuffer(GL_ARRAY_BUFFER, vBuff_);
		//glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float) * 3, , GL_STATIC_DRAW);

		glGenBuffers(1, &uvBuff_);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuff_);
		//glBufferData(GL_ARRAY_BUFFER, uvs_.size() * sizeof(float) * 2, &uvs_[0], GL_STATIC_DRAW);
	}

	void Draw()
	{
		glPushMatrix();
		/*
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vBuff_);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuff_);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, vertices_.size());
		*/
		glPopMatrix();
	}

	static bool IsBuffer(GLuint pBuf) { return glIsBuffer(pBuf); }
private:
	GLuint vBuff_, nBuff_, uvBuff_;
	std::vector<Pnt3<float> > vertices_;
	std::vector<Pnt3<float> > normals_;
	std::vector<Pnt2<float> > uvs_;
};

#endif _LOADER_H_