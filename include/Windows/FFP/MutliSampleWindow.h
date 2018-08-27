#ifndef MULTI_SAMPLE_H_
#define MULTI_SAMPLE_H_

#include "../SDLWindow.h"

#ifndef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "FFPWindow.h"

class MultiSampleWindow : public FFPWindow {
public:
	MultiSampleWindow() : FFPWindow() {}

	void SDLGLSetUp() override
	{
		FFPWindow::SDLGLSetUp();
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
	}

	void SceneSetUp() override {
		FFPWindow::SceneSetUp();

		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearStencil(0);
		SEGL::ErrorCheck(__LINE__, __FILE__);
	}

	void Render() override {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

		FFPWindow::Render();
		
		glPushMatrix();
		for(int z = 0; z < 2; ++z)
		{
			if(z == 1)
				glColor4f(1, 0, 0, 0.5);
			else
				glColor4f(0, 1, 0, 0.75);
			glBegin(GL_TRIANGLES);
			for(int i = 0; i < 50; i+=2)
			{
				for(int j = 0; j < 99; j+=2)
				{
					glVertex3f(i, j, z*-10);
					glVertex3f(i + 2, j + 1, z*-10);
					glVertex3f(i, j + 2, z*-10);
				}
			}
			glEnd();

		}
		glPopMatrix();

        SEGL::ErrorCheck( __LINE__ );
        SdlErrorCheck( __LINE__, true );
	}
private:
};
#endif MULTI_SAMPLE_H_