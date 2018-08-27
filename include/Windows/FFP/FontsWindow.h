#ifndef FONTS_WINDOW_H_
#define FONTS_WINDOW_H_

#include "FFPWindow.h"

#ifndef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class FontsWindow : public FFPWindow {
public:
	FontsWindow() : FFPWindow() {}


	void SceneSetUp() override {
		FFPWindow::SceneSetUp();

		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearStencil(0);
		SEGL::ErrorCheck(__LINE__, __FILE__);

		//auto family = font_->GetFont("Robo");
		//tex_ = family->Render("Test");
	}

	void Render() override {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

		glDisable(GL_TEXTURE_2D);
		FFPWindow::Render();
		glEnable(GL_TEXTURE_2D);

		glPushMatrix();
		glRotatef(180, 1, 0, 0);
		glPopMatrix();

        SEGL::ErrorCheck( __LINE__ );
        SdlErrorCheck( __LINE__, true );
	}
private:
	FontTexture* tex_;
};
#endif FONTS_WINDOW_H_