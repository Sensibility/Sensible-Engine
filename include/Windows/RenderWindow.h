//
// Created by steve on 2/13/18.
//

#ifndef MAIN_RENDERWINDOW_H
#define MAIN_RENDERWINDOW_H

#ifdef _WIN32
	#include<windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../Camera/baseCamera.h"
#include "../Camera/Camera.h"
#include <SDL2/SDL.h>

class RenderWindow {
public:
	RenderWindow() {
		cameras = Camera( CameraType::Arc );
		cameras.cam()->setRadius( 50 );
	}
	~RenderWindow() {
		SDL_GL_DeleteContext( context );
		SDL_DestroyWindow( window );

		SDL_Quit();
	}

	void RenderSetup(float pWidth, float pHeight) {
		glClearColor( 0, 0, 0, 0 );
		glViewport( 0, 0, pWidth, pHeight );
		GLErrorCheck( __LINE__ );

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( 45.0, pWidth / pHeight, 0.1, 1024 );
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

	void Render() {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		auto cam = cameras.cam();
		cam->lookAt( vector<float>());
		auto xyz = cam->getXYZ();
		auto dir = cam->getDirXYZ();
		auto up = cam->getUpXYZ();
		gluLookAt( xyz.getX(), xyz.getY(), xyz.getZ(),
				   dir.getX(), dir.getY(), dir.getZ(),
				   up.getX(), up.getY(), up.getZ());

		glPushMatrix();
		glCallList( displayList );
		glPopMatrix();

		GLErrorCheck( __LINE__ );

		SdlErrorCheck( __LINE__, true );
	}
	void GLErrorCheck(int lineNum) const {
		auto err = glGetError();
		if (err != GL_NO_ERROR)
			fprintf( stderr, "ERR: %s, %i\n", gluErrorString( err ), lineNum );
	}

	void SdlErrorCheck(int lineNum, bool clear = false) {
		string sdlErr = SDL_GetError();
		if (sdlErr != "") {
			cout << "ERR: " << sdlErr << ", " << lineNum << endl;
			if (clear)
				SDL_ClearError();
		}
	}

	void Update() { }

	void Loop() {
		while (true) {
			SDL_Event event;
			while (SDL_PollEvent( &event )) {
				if (event.type == SDL_QUIT)
					return;
				else if (event.type == SDL_MOUSEBUTTONDOWN) {
					x = event.motion.x;
					y = event.motion.y;
					down = true;
				} else if (event.type == SDL_MOUSEBUTTONUP) {
					down = false;
				} else if (event.type == SDL_MOUSEMOTION) {
					if (down)
						cameras.cam()->handleMouse( 0, false, x, y, event.motion.x, event.motion.y );
					x = event.motion.x;
					y = event.motion.y;
				} else if (event.type == SDL_KEYDOWN) {
					auto vec = Point( 0, 0, 0 );
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							return;
						case SDLK_w:
							vec.setX( 1 );
							break;
						case SDLK_s:
							vec.setX( -1 );
							break;
						case SDLK_d:
							vec.setZ( -1 );
							break;
						case SDLK_a:
							vec.setZ( 1 );
							break;
						case SDLK_r:
							vec.setY( 1 );
							break;
						case SDLK_f:
							vec.setY( -1 );
							break;
						case SDLK_p:
							if (cameras.getType() == CameraType::Fp)
								cameras.setType( CameraType::Arc );
							else
								cameras.setType(CameraType::Fp );
						default:
							cout << event.key.keysym.sym << endl;
							break;
					}
					if (cameras.getType() == CameraType::Arc)
						cameras.cam()->incrementDirXYZ( vec );
					else
						cameras.cam()->incrementXYZ( vec );
				}
			}
			Update();
			Render();
			SDL_GL_SwapWindow( window );
		}
	}

	void Start() {
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

		if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
			cout << "Failed to init SDL\n" << endl;
		}

		auto windowWidth = 1150;
		auto windowHeight = 650;

		window = SDL_CreateWindow(
				"Main",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				windowWidth, windowHeight,
				SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
		);


		if (!window)
			cout << "Failed to create window" << endl;
		context = SDL_GL_CreateContext( window );
		SdlErrorCheck( __LINE__, true );

		//vsync
		if (SDL_GL_SetSwapInterval( 1 ) < 0)
			SdlErrorCheck( __LINE__, true );

		RenderSetup( windowWidth, windowHeight );

		Diagnostics();

		Loop();
	}
private:
	void Diagnostics() {
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
	}
	SDL_Window *window;
	SDL_GLContext context;
	Camera cameras;
	GLuint displayList;
	bool down = false;
	Sint32 x;
	Sint32 y;
};

#endif //MAIN_RENDERWINDOW_H
