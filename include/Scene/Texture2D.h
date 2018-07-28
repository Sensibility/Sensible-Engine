#ifndef TEXTURE_2D_H_
#define TEXTURE_2D_H_

#include "BaseScene.h"

#ifndef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Texture2D : public BaseScene {
public:
	Texture2D(): BaseScene() { }


	GLuint tex3_;

	void SetUp() override
	{
        glClearColor(0, 0, 0, 0);
        glViewport(0, 0, 1150, 650);
        GLErrorCheck(__LINE__, __FILE__);

		glShadeModel(GL_FLAT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		GLErrorCheck(__LINE__, __FILE__);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90, 1150 / 650, 0.1, 1024);
        GLErrorCheck(__LINE__, __FILE__);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        GLErrorCheck(__LINE__, __FILE__);

		void* pixelData = SampleTexture2D(64, 64, false);
		tex2_ = GenerateTexture2D(64, 64, pixelData);
		GenerateMipMap(tex2_, GL_TEXTURE_2D);

		tex_ = LoadTexturePNG(R"(assets\sn.png)");

        GLErrorCheck(__LINE__, __FILE__);
	}

	void Render() override
	{
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

		GLErrorCheck(__LINE__, __FILE__);

        BaseScene::Render();

		tex_->Render();

		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			glColor4f(1, 1, 0, 1);
			glBindTexture(GL_TEXTURE_2D, tex2_);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0); 
					glVertex3f(64, 64, 0);
				glTexCoord2i(0, 1); 
					glVertex3f(0, 64, 0 );
				glTexCoord2i(1, 1); 
					glVertex3f(0, 0, 0);
				glTexCoord2i(1, 0); 
					glVertex3f(64, 0, 0);
			glEnd();
			glEnable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		GLErrorCheck(__LINE__, __FILE__);
	}
private:
	GLuint tex2_;
	Texture *tex_;
};

#endif TEXTURE_2D_H_
