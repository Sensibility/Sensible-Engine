#ifndef MAIN_FONTS_H
#define MAIN_FONTS_H
#include "BaseScene.h"

#ifndef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>


class FontsScene : public BaseScene {
public:
	FontsScene(): BaseScene()
	{
		
	}

    void SetUp() override
    {
        glClearColor(0, 0, 0, 0);
        glViewport(0, 0, 1150, 650);
        GLErrorCheck(__LINE__, __FILE__);

		glShadeModel(GL_FLAT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearStencil(0);
		GLErrorCheck(__LINE__, __FILE__);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90, 1150 / 650, 0.1, 1024);
        GLErrorCheck(__LINE__, __FILE__);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        GLErrorCheck(__LINE__, __FILE__);

		currentFont_ = Fonts::OpenFont("assets\\roboto\\Roboto-Black.ttf", "Test");
		tex_ = currentFont_->ToTexture();
    }

    void Render() override
    {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

		glDisable(GL_TEXTURE_2D);
        BaseScene::Render();
		glEnable(GL_TEXTURE_2D);

		glPushMatrix();
			glColor4f(1, 1, 1, 1);
			glBindTexture(GL_TEXTURE_2D, tex_);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0); glVertex2f(0, 0);
				glTexCoord2i(0, 1); glVertex2f(0, currentFont_->Height());
				glTexCoord2i(1, 1); glVertex2f(currentFont_->Width(), currentFont_->Height());
				glTexCoord2i(1, 0); glVertex2f(currentFont_->Width(), 0);
			glEnd();
		glPopMatrix();


		GLErrorCheck(__LINE__, __FILE__);
		SdlErrorCheck(__LINE__, true);
    }
private:
	TrueTypeFont* currentFont_;
	GLuint tex_;
};
#endif //MAIN_FONTS_H
