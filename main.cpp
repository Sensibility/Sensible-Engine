#include <GL/glew.h>
#include <GL/glut.h>


#include <stdio.h>
#include <math.h>
#include <string>
#include <memory>
#include <iostream>
#include "keys.h"
#include "include/Camera/baseCamera.h"
#include "include/console.h"
#include "include/Camera/arcCamera.h"
#include "include/Camera/fpCamera.h"
#include "include/Camera/Camera.h"

int windowWidth = 1150, windowHeight = 650;
int windowId;
Camera cameras;

GLuint displayList;

int leftMouseButton;
bool init;
int y;
int x;
Console console;

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
	{
		glBegin( GL_LINES );
		for (int i = -50; i <= 50; ++i) {
			glVertex3f( i, 0, -50 );
			glVertex3f( i, 0, 50 );
			glVertex3f( -50, 0, i );
			glVertex3f( 50, 0, i );
		}
		glEnd();
	}
	glPopMatrix();

	glEnable( GL_LIGHTING );
}

void renderScene() {
	glDrawBuffer( GL_BACK );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	cameras.cam()->lookAt( std::vector<float>());

	if (cameras.getType() != Fp) {
		glPushMatrix();
		auto target = cameras.cam()->getDirXYZ();
		glTranslatef( target.getX(), target.getY() + 1, target.getZ());
		glutSolidTeapot( 2 );
		glPopMatrix();
	}

	glPushMatrix();
	glCallList( displayList );
	glPopMatrix();

	glFlush();

	glutSwapBuffers();
}

void keyPressCall(unsigned char key, int mouseX, int mouseY) {
	std::string val = handleKey( key, mouseX, mouseY, true );
	cameras.cam()->keyPressCall( val );

	if (val == "p") {
		if (cameras.getType() == Fp)
			cameras.setType( Arc );
		else
			cameras.setType( Fp );
	}
	if (val == "ESCAPE" || val == "Q")
		exit( 0 );

}

void keyReleaseCall(unsigned char key, int mouseX, int mouseY) {
	std::string val = handleKey( key, mouseX, mouseY, false );
	if (val == "No Action") return;
}

void mousePressCall(int button, int state, int mouseX, int mouseY) {
	if (button == GLUT_LEFT_BUTTON) {
		leftMouseButton = state;
		x = mouseX;
		y = mouseY;
	}
	if (state == GLUT_DOWN && !init) init = true;
}

void mouseMoveCall(int mouseX, int mouseY) {
	cameras.cam()->handleMouse( leftMouseButton, (glutGetModifiers() == GLUT_ACTIVE_CTRL),
								x, y, mouseX, mouseY );

	x = mouseX;
	y = mouseY;
	glutPostRedisplay();
}

void close() {
	console.cancel();
	glutDestroyWindow( windowId );
}

void initalize() {
	cameras = Camera( Fp );

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowPosition( 50, 50 );
	glutInitWindowSize( windowWidth, windowHeight + 50 );
	windowId = glutCreateWindow( "main" );

	glutSetKeyRepeat( GLUT_KEY_REPEAT_ON );
	glutKeyboardFunc( keyPressCall );
	glutKeyboardUpFunc( keyReleaseCall );
	glutMouseFunc( mousePressCall );
	glutDisplayFunc( renderScene );
	glutReshapeFunc( changeSize );
	glutMotionFunc( mouseMoveCall );
	glutTimerFunc((1000 / 60), timerFunc, 0 );
}

GLenum diagnostics() {
	GLenum result = glewInit();

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

	return result;
}

void initalizeScene() {
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
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	initalize();

	GLenum glewResult = diagnostics();
	if (glewResult != GLEW_OK) {
		printf( "[ERROR]: Could not init GLEW\n" );
		return 0;
	}

	initalizeScene();
	console.start();

	atexit( close );
	glutMainLoop();

	return 0;
}
