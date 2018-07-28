#ifndef _SKYBOX_H_
#define _SKYBOX_H_
#include <vector>
#include "Textures.h"

class Skybox
{
public:
	Skybox(string pDir)
	{
		textures_.push_back(LoadTexturePNG(pDir + "\\back.png", GL_RGB));
		textures_.push_back(LoadTexturePNG(pDir + "\\left.png", GL_RGB));
		textures_.push_back(LoadTexturePNG(pDir + "\\front.png", GL_RGB));
		textures_.push_back(LoadTexturePNG(pDir + "\\right.png", GL_RGB));
		textures_.push_back(LoadTexturePNG(pDir + "\\bottom.png", GL_RGB));
		textures_.push_back(LoadTexturePNG(pDir + "\\top.png", GL_RGB));
	}

	void DrawSkybox(int size)
	{
		DrawSkyboxPanel(textures_.at(0)->_Handle(), Point(-1, 0, -size), Vector(1, 0, 0), Vector(0, 1, 0),
		                Vector(0, 0, 1), 1, -1, size); // back
		DrawSkyboxPanel(textures_.at(1)->_Handle(), Point(-size, 0, -1), Vector(0, 0, 1), Vector(0, 1, 0),
		                Vector(1, 0, 0), -1, -1, size); // left
		DrawSkyboxPanel(textures_.at(2)->_Handle(), Point(1, 0, size), Vector(1, 0, 0), Vector(0, 1, 0),
		                Vector(0, 0, -1), -1, -1, size); // front
		DrawSkyboxPanel(textures_.at(3)->_Handle(), Point(size, 0, 1), Vector(0, 0, 1), Vector(0, 1, 0),
		                Vector(-1, 0, 0), 1, -1, size); // right
		DrawSkyboxPanel(textures_.at(4)->_Handle(), Point(0, -size, 0), Vector(1, 0, 0), Vector(0, 0, 1),
		                Vector(0, 1, 0), 1, 1, size); // bottom
		DrawSkyboxPanel(textures_.at(5)->_Handle(), Point(0, size, 0), Vector(1, 0, 0), Vector(0, 0, 1),
		                Vector(0, -1, 0), 1, -1, size); // top
	}

private:
	void DrawSkyboxPanel(GLuint texHandle, Point point, Vector dim1, Vector dim2, Vector normal, int flippingFactor,
	                     int flippingFactor2, int size)
	{
		Point p1 = point + dim1 * -(size + 1) + dim2 * -(size + 1); // LL corner
		Point p2 = point + dim1 * (size + 1) + dim2 * -(size + 1); // LR corner
		Point p3 = point + dim1 * (size + 1) + dim2 * (size + 1); // UR corner
		Point p4 = point + dim1 * -(size + 1) + dim2 * (size + 1); // UL corner

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texHandle);
		glPushMatrix();
		{
			glColor4f(1, 1, 1, 1);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 0);
				normal.glNormal();
				p1.glVertex();

				glTexCoord2f(1 * flippingFactor, 0);
				normal.glNormal();
				p2.glVertex();

				glTexCoord2f(1 * flippingFactor, 1 * flippingFactor2);
				normal.glNormal();
				p3.glVertex();

				glTexCoord2f(0, 1 * flippingFactor2);
				normal.glNormal();
				p4.glVertex();
			};
			glEnd();
		};
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	std::vector<Texture*> textures_ = std::vector<Texture*>();
};

#endif _SKYBOX_H_
