#ifndef _MULTISAMPLE_H_
#define _MULTISAMPLE_H_
#include "BaseScene.h"

#ifndef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

 class Multisample : public BaseScene
{
public:
		static int change(std::vector<std::string>& pStrs, void* pContext)
		{
			auto s = *static_cast<Multisample*>(pContext);
			if (pStrs.size() == 1)
				s.Toggle();

			printf("Multisampling: %s", s.render_ ? "true" : "false");
			if (s.render_)
				s.GetSamples();
			return 0;
		}

		void GetSamples()
		{
			GLint buf, sbuf;
			glGetIntegerv(GL_SAMPLE_BUFFERS, &buf);
			printf("sample buffers %d\n", buf);
			glGetIntegerv(GL_SAMPLES, &sbuf);
			printf("samples  %d\n", sbuf);
		}
		void SdlSetUp() override
		{
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, this->buffers);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, this->samples);
			SdlErrorCheck(__LINE__);
		}
		void SetUp() override
		{
			glClearColor(0, 0, 0, 0);
			glViewport(0, 0, 1150, 650);
			GLErrorCheck(__LINE__, __FILE__);

			glEnable(GL_DEPTH_TEST);
			Toggle();
			glEnable(GL_POLYGON_SMOOTH);
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

			GetSamples();
			Console::Register("sample", Command(&change, this));
		}

		void Render() override
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			BaseScene::Render();

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
		}

		int InputQueue(SDL_Event* e) override {
			if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_m)
				Toggle();
			return BaseScene::InputQueue(e);
		}

    void Toggle()
	{
		this->render_ = !this->render_;
		if (this->render_)
			glEnable(GL_MULTISAMPLE);
		else
			glDisable(GL_MULTISAMPLE);
	}
	bool render_ = false;
	const int buffers = 1;
	int samples = 8;
};

#endif _MULTISAMPLE_H_