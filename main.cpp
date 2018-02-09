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

float getRand() {
   	return rand() / (float)RAND_MAX;
}
void changeSize( int w, int h ) {
    windowWidth = w;
    windowHeight = h;

    // update the projection matrix based on the window size
    // the GL_PROJECTION matrix governs properties of the view;
    // i.e. what gets seen - use an Orthographic projection that ranges
    // from [0, windowWidth] in X and [0, windowHeight] in Y. (0,0) is the lower left.
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, windowWidth, 0, windowHeight + 50 );
    
    // update the viewport as well - tell OpenGL we want to render the whole window
    glViewport( 0, 0, windowWidth, windowHeight + 50 );

    // just as good practice, switch back to GL_MODELVIEW mode; that's the matrix
    // that we want to be changing with glTranslatef(), glScalef(), etc., so
    // just in case we forget to explicitly set it later...
    glMatrixMode( GL_MODELVIEW );
}

void renderScene() {
    // clear whatever was drawn to the screen last time - 
    // set the clear color to black and then signal to clear the RGB buffer.
    glDrawBuffer(GL_BACK);
    glClearColor( 0, 146, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT );

    // switch to GL_MODELVIEW, for when we start using glTranslatef(), glScalef(), etc..
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glFlush();

	glutSwapBuffers();
}

void keyPressCall(unsigned char key, int mouseX, int mouseY){
	std::string val = handleKey(key, mouseX, mouseY, true);
	if(val == "No Action") return;
	if(val == "ESCAPE") exit(0);

}

void keyReleaseCall(unsigned char key, int mouseX, int mouseY){
	std::string val = handleKey(key, mouseX, mouseY, false);
	if(val == "No Action") return;
}

void mousePressCall( int button, int state, int mouseX, int mouseY ){
}

void mouseMoveCall( int mouseX, int mouseY ){
	mouseY = windowHeight - mouseY;
}

void close() {
	glutDestroyWindow(windowId);
}

int main( int argc, char* argv[] ) {
    cam = Camera();

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( windowWidth, windowHeight + 50 );
    windowId = glutCreateWindow( "SQ 1" );

    GLenum glewResult = glewInit();
    if(glewResult != GLEW_OK) {
        printf( "[ERROR]: Could not init GLEW\n");
        return 0;
    }

    GLint maxVertexAttribs = 0;
    glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs );

    GLint maxLights = 0;
    glGetIntegerv( GL_MAX_LIGHTS, &maxLights );

    GLint maxTextures = 0;
    glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures );

    fprintf( stdout, "[INFO]: /--------------------------------------------------------\\\n");
    fprintf( stdout, "[INFO]: | OpenGL Information                                     |\n");
    fprintf( stdout, "[INFO]: |--------------------------------------------------------|\n");
    fprintf( stdout, "[INFO]: |   OpenGL Version:  %35s |\n", glGetString(GL_VERSION) );
    fprintf( stdout, "[INFO]: |   OpenGL Renderer: %35s |\n", glGetString(GL_RENDERER) );
    fprintf( stdout, "[INFO]: |   OpenGL Vendor:   %35s |\n", glGetString(GL_VENDOR) );
    fprintf( stdout, "[INFO]: |   Shading Version: %35s |\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );
    fprintf( stdout, "[INFO]: >--------------------------------------------------------<\n");
    fprintf( stdout, "[INFO]: |   Max # Vertex Attributes:  %26d |\n", maxVertexAttribs );
    fprintf( stdout, "[INFO]: |   Max # Lights:    %35d |\n", maxLights );
    fprintf( stdout, "[INFO]: |   Max # Textures:  %35d |\n", maxTextures );
    fprintf( stdout, "[INFO]: \\--------------------------------------------------------/\n\n");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_LIGHTING);

    glDisable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    glutDisplayFunc( renderScene );
    glutReshapeFunc( changeSize );

	/********** ADD CALLBACKS ***************/
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyPressCall);
    glutKeyboardUpFunc(keyReleaseCall);
    glutMouseFunc(mousePressCall);
    glutPassiveMotionFunc(mouseMoveCall);
/*    glutTimerFunc((1000/60), timerFunc, 0);*/

    atexit(close);

    // begin GLUT loop
    glutMainLoop();    

    return 0;
}
