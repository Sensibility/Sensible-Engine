#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <memory>
#include <iostream>
#include "drawing.h"
#include "keys.h"
#include "include/camera.h"
#include <time.h>

int windowWidth = 1150, windowHeight = 650;
int windowId;
Camera cam;

GLuint displayList;

int leftMouseButton;

bool init;

int y;

int x;

void timerFunc(int value) {
	glutPostRedisplay();
	glutTimerFunc( 1000 / 60, timerFunc, 0 );
};

float getRand() {
	return rand() / (float) RAND_MAX;
}

void changeSize(int w, int h) {
	windowWidth = w;
	windowHeight = h;

	glViewport( 0, 0, w, h );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0, w / h, 0.1, 100000 );
}

void drawGrid() {
	glDisable( GL_LIGHTING );

	glPushMatrix();
	glBegin( GL_LINES );
	for (int i = -50; i <= 50; ++i) {
		glVertex3f( i, 0, -50 );
		glVertex3f( i, 0, 50 );
	}
	for (int i = -50; i <= 50; ++i) {
		glVertex3f( -50, 0, i );
		glVertex3f( 50, 0, i );
	}
	glEnd();
	glPopMatrix();

	glEnable( GL_LIGHTING );
}

void renderScene() {
	glDrawBuffer( GL_BACK );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	cam.updateCamera( std::vector<float>());
	gluLookAt( cam.getX(), cam.getY(), cam.getZ(),
			   cam.getDirX(), cam.getDirY(), cam.getDirZ(),
			   cam.getUpX(), cam.getUpY(), cam.getUpZ());

	glPushMatrix();
	glTranslatef( cam.getDirX(), cam.getDirY() + 1, cam.getDirZ());
	glutWireTeapot( 2 );
	glPopMatrix();

	glPushMatrix();
	glCallList( displayList );
	glPopMatrix();

/*	glFlush();*/

	glutSwapBuffers();
}

void keyPressCall(unsigned char key, int mouseX, int mouseY) {
	std::string val = handleKey( key, mouseX, mouseY, true );
	if (val == "No Action") return;
	else if (val == "w") {
		cam.incrementDirXYZ( 1, 0, 0 );
	} else if (val == "s") {
		cam.incrementDirXYZ( -1, 0, 0 );
	} else if (val == "a") {
		cam.incrementDirXYZ( 0, 0, 1 );
	} else if (val == "d") {
		cam.incrementDirXYZ( 0, 0, -1 );
	}

	if (val == "ESCAPE") exit( 0 );

}

void keyReleaseCall(unsigned char key, int mouseX, int mouseY) {
	std::string val = handleKey( key, mouseX, mouseY, false );
	if (val == "No Action") return;
}

void mousePressCall(int button, int state, int mouseX, int mouseY) {
	if (button == GLUT_LEFT_BUTTON)
		leftMouseButton = state;
	if (state == GLUT_DOWN && !init) init = true;
}

void mouseMoveCall(int mouseX, int mouseY) {
	cam.handleMouse( leftMouseButton, (glutGetModifiers() == GLUT_ACTIVE_CTRL),
					 x, y, mouseX, mouseY );

	x = mouseX;
	y = mouseY;
	glutPostRedisplay();
}

void close() {
	glutDestroyWindow( windowId );
}

int main(int argc, char *argv[]) {
	cam = Camera( 100, 100, 100,
				  0, 0, 0,
				  0, 1, 0,
				  45, -45, 50,
				  CAMERA_ARC, "" );

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowPosition( 50, 50 );
	glutInitWindowSize( windowWidth, windowHeight + 50 );
	windowId = glutCreateWindow( "main" );

	//#region Diagnostics
	GLenum glewResult = glewInit();
	if (glewResult != GLEW_OK) {
		printf( "[ERROR]: Could not init GLEW\n" );
		return 0;
	}

	GLint maxVertexAttribs = 0;
	glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs );

	GLint maxLights = 0;
	glGetIntegerv( GL_MAX_LIGHTS, &maxLights );

	GLint maxTextures = 0;
	glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures );

	fprintf( stdout, "[INFO]: /--------------------------------------------------------\\\n" );
	fprintf( stdout, "[INFO]: | OpenGL Information                                     |\n" );
	fprintf( stdout, "[INFO]: |--------------------------------------------------------|\n" );
	fprintf( stdout, "[INFO]: |   OpenGL Version:  %35s |\n", glGetString( GL_VERSION ));
	fprintf( stdout, "[INFO]: |   OpenGL Renderer: %35s |\n", glGetString( GL_RENDERER ));
	fprintf( stdout, "[INFO]: |   OpenGL Vendor:   %35s |\n", glGetString( GL_VENDOR ));
	fprintf( stdout, "[INFO]: |   Shading Version: %35s |\n", glGetString( GL_SHADING_LANGUAGE_VERSION ));
	fprintf( stdout, "[INFO]: >--------------------------------------------------------<\n" );
	fprintf( stdout, "[INFO]: |   Max # Vertex Attributes:  %26d |\n", maxVertexAttribs );
	fprintf( stdout, "[INFO]: |   Max # Lights:    %35d |\n", maxLights );
	fprintf( stdout, "[INFO]: |   Max # Textures:  %35d |\n", maxTextures );
	fprintf( stdout, "[INFO]: \\--------------------------------------------------------/\n\n" );
	//#endregion

	glutSetKeyRepeat( GLUT_KEY_REPEAT_ON );
	glutKeyboardFunc( keyPressCall );
	glutKeyboardUpFunc( keyReleaseCall );
	glutMouseFunc( mousePressCall );
	glutDisplayFunc( renderScene );
	glutReshapeFunc( changeSize );
	glutMotionFunc( mouseMoveCall );
	glutTimerFunc((1000 / 60), timerFunc, 0 );

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

/*    glDisable(GL_CULL_FACE);*/
/*    glEnable(GL_NORMALIZE);*/
	glShadeModel( GL_FLAT );


	displayList = glGenLists( 1 );
	glNewList( displayList, GL_COMPILE );
	drawGrid();
	glEndList();


/*	atexit( close );*/

	glutMainLoop();

	return 0;
}
