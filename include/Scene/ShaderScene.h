#ifndef _SHADER_SCENE_H_
#define _SHADER_SCENE_H_

#include "BaseScene.h"

#ifndef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../Renderer/Shader.h"
#include "../File.h"
#include "../Renderer/Loader.h"

class ShaderScene : public BaseScene {
public:
	ShaderScene(): BaseScene() { }

	Shader* shader_;

	OBJObject* obj_;

	void SetUp() override
	{
		BaseScene::SetUp();

        glClearColor(0, 0, 0, 0);
        glViewport(0, 0, 1150, 650);
        GLErrorCheck(__LINE__, __FILE__);

		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
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
		
		obj_ = new OBJObject("assets/untitled.obj");
		shader_ = ShaderBuilder::CreateShader("assets/shaders/normal.v.glsl", "assets/shaders/normals.f.glsl");
		GLErrorCheck(__LINE__, __FILE__);
	}

	void Render() override
	{
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        BaseScene::Render();

		obj_->Draw();
	}
private:
};

#endif _SHADER_SCENE_H_
