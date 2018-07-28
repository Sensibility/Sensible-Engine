#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#ifdef _WIN32
#include<windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include "BaseScene.h"
#include "../Renderer/Lighting.h"

class Lighting : public BaseScene
{
	void SetUp() override
	{
		glClearColor(0, 0, 0, 0);
		glViewport(0, 0, 1150, 650);
		GLErrorCheck(__LINE__, __FILE__);

		GLfloat mSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mShiny[] = { 50.0 };
		glShadeModel(GL_SMOOTH);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mShiny);
		GLErrorCheck(__LINE__, __FILE__);

		GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };
		GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
		Lights::SetAmbientLight(mAmbient);
		Lights::SetDirectionalLight(GL_LIGHT0, light_pos, white_light, white_light);

		light_pos[3] = 1.0;
		white_light[0] = .5;
		white_light[1] = .87;
		Lights::SetSpotLight(GL_LIGHT1, light_pos, white_light, white_light, light_pos, 30, 2);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_DEPTH_TEST);
		GLErrorCheck(__LINE__, __FILE__);


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90, 1150 / 650, 0.1, 1024);
		GLErrorCheck(__LINE__, __FILE__);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		GLErrorCheck(__LINE__, __FILE__);
	}

	void Render() override
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		BaseScene::Render();

		glPushMatrix();
		auto c = cameras_.cam()->getXYZ();
		auto camPos = cameras_.cam()->getLookDirection();
		GLfloat pos[] = { c.getX(), c.getY(), c.getZ(), 1 };
		GLfloat pos2[] = {camPos.getX(), camPos.getY(), camPos.getZ(), 0};
		Lights::MoveSpotLight(GL_LIGHT1, pos, pos2);

		glPopMatrix();

		auto quad = gluNewQuadric();
		glPushMatrix();
		glTranslatef(10, 10, 10);
		gluSphere(quad, 4, 3000, 3000);
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
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
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glPopMatrix();
	}

	int InputQueue(SDL_Event* e) override
	{
		
		return BaseScene::InputQueue(e);
	}
};

#endif