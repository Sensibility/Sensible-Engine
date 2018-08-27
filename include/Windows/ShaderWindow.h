#ifndef SHADER_WINDOW_H_
#define SHADER_WINDOW_H_

#include "CoreWindow.h"

#ifndef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../Renderer/Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include "../RenderObject/ObjectProvider.h"

class ShaderWindow : public CoreWindow {
public:
	ShaderWindow() : CoreWindow() {}

	~ShaderWindow() { }

	void SceneSetUp() override {
		glClearColor(0, 0, 0, 1);

		CoreWindow::SceneSetUp();
		SEGL::ErrorCheck(__LINE__, __FILE__);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);

		obj_ = object_->ReadInOBJ<MultiTexObject>("assets\\suzanne.obj");
		SEGL::ErrorCheck(__LINE__, __FILE__);

		shader_ = ShaderBuilder::CreateShaderStr(v_passthru, f_passthru);
		shader_->Activate();
		matrix_ = shader_->GetHandle("MVP");
		map_ = image_->LoadDDS("assets\\uvmap.DDS");
		tex_ = shader_->GetHandle("tex");
		SEGL::ErrorCheck(__LINE__, __FILE__);
		shader_->Activate();

		obj_->InitBuffers();

		SEGL::ErrorCheck(__LINE__, __FILE__);
	}

	void Render() override {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		CoreWindow::Render();
        SEGL::ErrorCheck( __LINE__ );

		shader_->Activate();

		glm::mat4 mvp = MVP();
		glUniformMatrix4fv(matrix_, 1, GL_FALSE, &mvp[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, map_->_Handle());
		glUniform1i(tex_, 0);
        SEGL::ErrorCheck( __LINE__ );

		obj_->Render();

        SEGL::ErrorCheck( __LINE__ );
        SdlErrorCheck( __LINE__, true );
	}

private:
	Shader* shader_;
	GLuint matrix_;
	Object* obj_;
	Texture* map_;
	GLuint tex_;
};
#endif SHADER_WINDOW_H_