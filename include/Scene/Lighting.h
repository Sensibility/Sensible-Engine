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

class Lighting : public BaseScene
{
	void SetUp() override
	{
		glClearColor(0, 0, 0, 0);
		glViewport(0, 0, 1150, 650);
		GLErrorCheck(__LINE__);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, 1150 / 650, 0.1, 1024);
		GLErrorCheck(__LINE__);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		GLErrorCheck(__LINE__);
	}

	void Render() override
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		BaseScene::Render();
	}

	void RegisterEventLoop() override
	{
		SDL_AddEventWatch(EventHandler, this);
	}

	int InputQueue(SDL_Event* e) override
	{
		HandleKey(e);
		return 0;
	}
};

#endif