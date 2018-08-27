//:%s/\$HDRNAME\$//g
//:%s/\$NAME\$//g
#ifndef _BENCH_WINDOW_H_
#define _BENCH_WINDOW_H_

#include "CoreWindow.h"

#ifndef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../Shaders/ShaderProvider.h"
#include "../RenderObject/ConsoleObject.h"

class BenchWindow : public CoreWindow {
public:
	BenchWindow() : CoreWindow() {}

	FontFamily* f;

	ConsoleObject::ConsoleObject* obj_;

	void SceneSetUp() override {
		glClearColor(0, 0, 0, 1);

		CoreWindow::SceneSetUp();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		SEGL::ErrorCheck(__LINE__, __FILE__);

		f = font_->OpenFont("assets\\roboto\\Roboto-Black.ttf", "Robo");
		f->InitBuffers();
		auto stats = f->GetMetaData("Greetings", glm::vec2(0, 0), 1);

		obj_ = new ConsoleObject::ConsoleObject("Robo", glm::vec2(0, 0), glm::vec2(stats.Width, stats.Height));
		obj_->InitBuffers();
		SEGL::ErrorCheck(__LINE__, __FILE__);
	}

	void Render() override {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		CoreWindow::Render();
        SEGL::ErrorCheck( __LINE__, __FILE__ );
		auto ortho = glm::ortho(0.f, (GLfloat)width_, 0.f, (GLfloat)height_);

		f->Render("Greetings", ortho, 
			glm::vec2(5, 5), glm::vec3(1, 1, 1), 1);
        SEGL::ErrorCheck( __LINE__, __FILE__ );

		obj_->Render(ortho);
        SEGL::ErrorCheck( __LINE__, __FILE__ );

        SdlErrorCheck( __LINE__, true );
	}
private:
};
#endif _BENCH_WINDOW_H_