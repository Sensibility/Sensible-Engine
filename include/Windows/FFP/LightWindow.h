#ifndef _LIGHT_WINDOW_H_
#define _LIGHT_WINDOW_H_

#include "FFPWindow.h"

#ifndef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../../Renderer/FFP/Lighting.h"

class LightWindow : public FFPWindow {
public:
	LightWindow() : FFPWindow() {}

	void SceneSetUp() override {
		FFPWindow::SceneSetUp();

		GLfloat spec[] = { 1,1,1,1 };
		GLfloat shiny[] = { 50 };
		GLfloat pos[] = { 1,1,1,0 };
		GLfloat ambient[] = { .3,.3,.3,1 };
		GLfloat color[] = { .5, .87, 1, 1 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT, GL_SHININESS, shiny);

		Lights::SetAmbientLight(ambient);
		Lights::SetDirectionalLight(GL_LIGHT0, pos, spec, spec);
		Lights::SetSpotLight(GL_LIGHT1, spec, color, color, spec, 30, 2);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
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

		auto c = cameras_.cam()->getXYZ();
		auto camPos = cameras_.cam()->getLookDirection();
		GLfloat pos[] = { c.x, c.y, c.z, 1 };
		GLfloat pos2[] = {camPos.x, camPos.y, camPos.z, 0};
		Lights::MoveSpotLight(GL_LIGHT1, pos, pos2);

		auto quad = gluNewQuadric();
		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glTranslatef(10, 10, 10);
		gluSphere(quad, 4, 3000, 3000);
		for(int i = 0; i < 50; i+=5)
		{
			for(int j = 0; j < 50; j+= 5)
			{
				for(int k = 0; k < 50; k += 5)
				{
					
				glPushMatrix();
					auto quad = gluNewQuadric();
					glTranslatef(i, j, k);
					glColor4f(1, 1, 1, 0.5);
					gluSphere(quad, 0.2, 20, 16);
				glPopMatrix();
				}
			}
		}
		glPopMatrix();

        SEGL::ErrorCheck( __LINE__ );
        SdlErrorCheck( __LINE__, true );
	}
private:
};
#endif _LIGHT_WINDOW_H_