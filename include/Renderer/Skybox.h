#ifndef _SKYBOX_H_
#define _SKYBOX_H_
#include <vector>
#include "glm/detail/type_vec3.hpp"
#include "../Texture/Images/ImageProvder.h"


class Skybox
{
public:
	Skybox(std::string pDir, ImageProvider* pImage)
	{
		textures_.push_back(pImage->LoadPNG(pDir + "\\back.png"));
		textures_.push_back(pImage->LoadPNG(pDir + "\\left.png"));
		textures_.push_back(pImage->LoadPNG(pDir + "\\front.png"));
		textures_.push_back(pImage->LoadPNG(pDir + "\\right.png"));
		textures_.push_back(pImage->LoadPNG(pDir + "\\bottom.png"));
		textures_.push_back(pImage->LoadPNG(pDir + "\\top.png"));
	}

	void DrawSkybox(int size)
	{
		DrawSkyboxPanel(textures_.at(0)->_Handle(), glm::vec3(-1, 0, -size), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0),
		                glm::vec3(0, 0, 1), 1, -1, size); // back
		DrawSkyboxPanel(textures_.at(1)->_Handle(), glm::vec3(-size, 0, -1), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0),
		                glm::vec3(1, 0, 0), -1, -1, size); // left
		DrawSkyboxPanel(textures_.at(2)->_Handle(), glm::vec3(1, 0, size), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0),
		                glm::vec3(0, 0, -1), -1, -1, size); // front
		DrawSkyboxPanel(textures_.at(3)->_Handle(), glm::vec3(size, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0),
		                glm::vec3(-1, 0, 0), 1, -1, size); // right
		DrawSkyboxPanel(textures_.at(4)->_Handle(), glm::vec3(0, -size, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 1),
		                glm::vec3(0, 1, 0), 1, 1, size); // bottom
		DrawSkyboxPanel(textures_.at(5)->_Handle(), glm::vec3(0, size, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 1),
		                glm::vec3(0, -1, 0), 1, -1, size); // top
	}

private:
	void DrawSkyboxPanel(GLuint texHandle, glm::vec3 point, glm::vec3 dim1, glm::vec3 dim2, glm::vec3 normal, float flippingFactor,
	                     float flippingFactor2, float size)
	{

		glm::vec3 p1 = point + dim1 * -(size + 1) + dim2 * -(size + 1); // LL corner
		glm::vec3 p2 = point + dim1 * (size + 1) + dim2 * -(size + 1); // LR corner
		glm::vec3 p3 = point + dim1 * (size + 1) + dim2 * (size + 1); // UR corner
		glm::vec3 p4 = point + dim1 * -(size + 1) + dim2 * (size + 1); // UL corner

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texHandle);
		glPushMatrix();
		{
			glColor4f(1, 1, 1, 1);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 0);
				glNormal3f(normal.x, normal.y, normal.z);
				glVertex3f(p1.x, p1.y, p1.z);

				glTexCoord2f(1 * flippingFactor, 0);
				glNormal3f(normal.x, normal.y, normal.z);
				glVertex3f(p2.x, p2.y, p2.z);

				glTexCoord2f(1 * flippingFactor, 1 * flippingFactor2);
				glNormal3f(normal.x, normal.y, normal.z);
				glVertex3f(p3.x, p3.y, p3.z);

				glTexCoord2f(0, 1 * flippingFactor2);
				glNormal3f(normal.x, normal.y, normal.z);
				glVertex3f(p4.x, p4.y, p4.z);
			};
			glEnd();
		};
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	std::vector<Texture*> textures_ = std::vector<Texture*>();
};

#endif _SKYBOX_H_
