#ifndef _BENCH_H_
#define _BENCH_H_

#ifdef _WIN32
#include<windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "BaseScene.h"

class Bench : public BaseScene
{
    void SetUp() override
    {
        glClearColor( 0, 0, 0, 0 );
        glViewport( 0, 0, 1150, 650 );
        GLErrorCheck( __LINE__ );

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective( 45.0, 1150 / 650, 0.1, 1024 );
        GLErrorCheck( __LINE__ );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        GLErrorCheck( __LINE__ );

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

        glCullFace( GL_BACK );
        glFrontFace( GL_CCW );
        glEnable( GL_CULL_FACE );

        glEnable( GL_NORMALIZE );
        glShadeModel( GL_FLAT );

        displayList = glGenLists( 1 );
        glNewList( displayList, GL_COMPILE );
        GLErrorCheck( __LINE__ );
        glDisable( GL_LIGHTING );

        glPushMatrix();
        {
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
        GLErrorCheck( __LINE__ );
    }

    void Render() override
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        BaseScene::Render();

        glPushMatrix();
        glCallList( displayList );
        glPopMatrix();

        GLErrorCheck( __LINE__ );

        SdlErrorCheck( __LINE__, true );
    }

    void RegisterEventLoop() override
    {
        SDL_AddEventWatch(EventHandler, this);
    }

	int InputQueue(SDL_Event* e) override
	{
		HandleKey(e);
		return 0;
    }; 
};

#endif