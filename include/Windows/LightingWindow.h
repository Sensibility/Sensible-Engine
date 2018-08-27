#ifndef _LIGHTING_WINDOW_H_
#define _LIGHTING_WINDOW_H_

#include "CoreWindow.h"

#ifndef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../Renderer/Shader.h"
#include "../RenderObject/ObjectProvider.h"
#include "../Texture/TextureProvider.h"

class LightingWindow : public CoreWindow {
public:
	LightingWindow() : CoreWindow() {}

	GLuint normTexture_;
	GLuint specTexture_;
	GLuint diffTexture_;
	Texture* specTex_;
	Texture* diffTex_;

	void SceneSetUp() override {
		CoreWindow::SceneSetUp();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);

		/*
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		*/

		shader_ = ShaderBuilder::CreateShaderFolder("assets\\shaders\\lighting");
		obj_ = object_->ReadInOBJ<MultiTexObject>("assets\\cylinder.obj");

		tex_ = image_->LoadTGA("assets\\normal.tga");
		specTex_ = image_->LoadDDS("assets\\specular.DDS");
		diffTex_ = image_->LoadDDS("assets\\diffuse.DDS");

		shader_->Activate();
		mvp_ = shader_->GetHandle("MVP");
		v_ = shader_->GetHandle("V");
		m_ = shader_->GetHandle("M");
		lightPos_ = shader_->GetHandle("lPos_W");

		normTexture_ = shader_->GetHandle("normSample");
		specTexture_ = shader_->GetHandle("specSample");
		diffTexture_ = shader_->GetHandle("diffSample");

		obj_->InitBuffers();

		SEGL::ErrorCheck(__LINE__, __FILE__);
	}

	void Render() override {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		CoreWindow::Render();
        SEGL::ErrorCheck( __LINE__, __FILE__ );

		glm::mat4 mvp = MVP();
		glUniformMatrix4fv(mvp_, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(v_, 1, GL_FALSE, &view_[0][0]);
		glUniformMatrix4fv(m_, 1, GL_FALSE, &model_[0][0]);

		auto lPos = cameras_.cam()->getXYZ();
		glUniform3f(lightPos_, lPos.x, lPos.y, lPos.z);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_->_Handle());
		glUniform1i(normTexture_, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, diffTex_->_Handle());
		glUniform1i(diffTexture_, 1);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, specTex_->_Handle());
		glUniform1i(specTexture_, 2);

		obj_->Render();
        SEGL::ErrorCheck( __LINE__, __FILE__ );
        SdlErrorCheck( __LINE__, true );
	}
private:
	Shader* shader_;

	Object* obj_;

	GLuint mvp_, v_, m_, lightPos_;

	Texture* tex_;
};
#endif _LIGHTING_WINDOW_H_