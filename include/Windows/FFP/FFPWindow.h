#ifndef _DEFUNCT_WINDOW_H_
#define _DEFUNCT_WINDOW_H_
#include "../SDLWindow.h"

class FFPWindow : public SDLWindow
{
public:
	void InitView(glm::vec3 xyz, glm::vec3 dir, glm::vec3 up) override
	{
        gluLookAt( xyz.x, xyz.y, xyz.z,
                   dir.x, dir.y, dir.z,
                   up.x, up.y, up.z);
	}

	void GLSetUp() override
	{
		SDLWindow::GLSetUp();
		//skybox_ = new Skybox("assets\\skybox", image_);
	}

	void SDLGLSetUp() override
	{
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	}

	void DrawAxis(int pSize, glm::vec3 pHome) override
	{
		//skybox_->DrawSkybox(200);
		SEGL::ErrorCheck(__LINE__, __FILE__);

		glPushMatrix();
		glLineWidth(3);

		glColor3f(1, 0, 0);
		SEGL::ErrorCheck(__LINE__, __FILE__);
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(100, 0, 0);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 100, 0);
		glEnd();

		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 100);
		glEnd();

		glPopMatrix();

		SEGL::ErrorCheck(__LINE__, __FILE__);
	}

	void InitProjection() override
	{
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective( 45.0, width_ / height_, 0.1, 1024 );
        SEGL::ErrorCheck( __LINE__, __FILE__ );
	}

	void InitModel() override
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}
};

#endif _DEFUNCT_WINDOW_H_