#ifndef BENCH_WINDOW_H_
#define BENCH_WINDOW_H_

#include "FFPWindow.h"

#ifndef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>

class BenchWindow : public FFPWindow {
public:
	BenchWindow() : FFPWindow() {}

	void SceneSetUp() override
	{
		FFPWindow::SceneSetUp();

        glEnable( GL_DEPTH_TEST );
        float lightCol[4] = {1, 1, 1, 1};
        float ambientCol[4] = {0.0, 0.0, 0.0, 1.0};
        float lPosition[4] = {10, 10, 10, 1};
        glLightfv( GL_LIGHT0, GL_POSITION, lPosition );
        glLightfv( GL_LIGHT0, GL_DIFFUSE, lightCol );
        glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol );
        glEnable( GL_LIGHTING );
        glEnable( GL_LIGHT0 );

        glEnable( GL_COLOR_MATERIAL );
        glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

        glEnable( GL_NORMALIZE );
        glShadeModel( GL_SMOOTH );

        displayList = glGenLists( 1 );
        glNewList( displayList, GL_COMPILE );
        SEGL::ErrorCheck( __LINE__ );
        glDisable( GL_LIGHTING );

        glPushMatrix();
        {
			glLineWidth(1);
			glColor3f(1, 1, 1);
            glBegin( GL_LINES );
            int size = 100;
            for (int i = -size; i <= size; i+=5) {
                glVertex3f( i, 0, -size );
                glVertex3f( i, 0, size );
                glVertex3f( -size, 0, i );
                glVertex3f( size, 0, i );
            }
            glEnd();
        }
        glPopMatrix();

        glEnable( GL_LIGHTING );
        glEndList();
        SEGL::ErrorCheck( __LINE__ );
	}

	void Render() override
	{
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

		FFPWindow::Render();

        glPushMatrix();
        glCallList( displayList );
        glPopMatrix();
        SEGL::ErrorCheck( __LINE__ );
        SdlErrorCheck( __LINE__, true );
	}
private:
	GLuint displayList;
};

#endif BENCH_WINDOW_H_