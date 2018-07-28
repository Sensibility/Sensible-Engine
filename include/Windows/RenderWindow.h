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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../console.h"
#include "../Scene/BaseScene.h"
#include "../Renderer/Fonts.h"


class RenderWindow {
public:
	RenderWindow()
	{
	}
	~RenderWindow() {
		Console::DeRegister("lol");
		auto d = SDL_GetWindowID(window);
		SDL_GL_DeleteContext( context );
		SDL_DestroyWindow(window);
	}

	void RegisterScene(BaseScene* pScene) {
		active_ = pScene;
	}

	void Loop() {
		while (true) {
			SDL_Event event;
			while (SDL_PollEvent( &event )) {
				switch (event.type) {
					case SDL_QUIT:
						return;
					case SDL_KEYDOWN:
					{
						switch(event.key.keysym.sym)
						{
							case SDLK_q:
								return;
							case SDLK_o:
								Console::Activate();
								break;
						}
						break;
					}
				}
			}

			active_->Render();
			//auto f = Fonts::RenderToGLTexture("Test", "hello");

			SDL_GL_SwapWindow( window );
			GLErrorCheck(__LINE__, __FILE__);
			SdlErrorCheck(__LINE__, true);
		}
	}

	void Start() {
		Fonts::OpenFont("assets\\roboto\\Roboto-Black.ttf", "Test");
		if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
			fprintf(stderr, "Failed to init SDL\n");
		}


		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
		//Get rid of old defunct OpenGL code
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

		SdlErrorCheck(__LINE__);

		active_->SdlSetUp();

		IMG_Init(IMG_INIT_PNG);

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
			fprintf(stderr, "Failed to create window\n");
		context = SDL_GL_CreateContext( window );
		SdlErrorCheck( __LINE__, true );

		//vsync
		if (SDL_GL_SetSwapInterval( 1 ) < 0)
			SdlErrorCheck( __LINE__, true );
		glewInit();
		Diagnostics();

		GLErrorCheck(__LINE__, __FILE__);
		SdlErrorCheck(__LINE__);

		active_->SetUp();
		active_->RegisterEventLoop();

		GLErrorCheck(__LINE__, __FILE__);
		SdlErrorCheck(__LINE__);

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

		string* diags;
		vector<string*>* diagsGrp;

		fprintf( stdout, "[INFO]: /--------------------------------------------------------\\\n" );
		fprintf( stdout, "[INFO]: | Info	%48s |\n", "");
		fprintf( stdout, "[INFO]: |--------------------------------------------------------|\n" );
		fprintf( stdout, "[INFO]: |   OpenGL Version:  %35s |\n", glGetString( GL_VERSION ));
		fprintf( stdout, "[INFO]: |   OpenGL Renderer: %35s |\n", glGetString( GL_RENDERER ));
		fprintf( stdout, "[INFO]: |   OpenGL Vendor:   %35s |\n", glGetString( GL_VENDOR ));
		fprintf( stdout, "[INFO]: |   Shading Version: %35s |\n", glGetString( GL_SHADING_LANGUAGE_VERSION ));
		fprintf( stdout, "[INFO]: >--------------------------------------------------------<\n" );
		fprintf( stdout, "[INFO]: |   Max # Vertex Attributes:  %26d |\n", maxVertexAttribs );
		fprintf( stdout, "[INFO]: |   Max # Lights:    %35d |\n", maxLights );
		fprintf( stdout, "[INFO]: |   Max # Textures:  %35d |\n", maxTextures );

		diags = Fonts::Diagnostics();
		fprintf( stdout, "[INFO]: |   %14s:  %35s |\n", diags[0].c_str(), diags[1].c_str());

		diagsGrp = BufferDiagnostics();
		for(auto& diag: *diagsGrp)
		{
			fprintf( stdout, "[INFO]: |   %14s:  %35s |\n", diag[0].c_str(), diag[1].c_str());
		}

		fprintf( stdout, "[INFO]: \\--------------------------------------------------------/\n\n" );
	}
	SDL_Window *window;
	SDL_GLContext context;
	BaseScene* active_;
	float drawRefresh_;
	float refresh_;
};

#endif //MAIN_RENDERWINDOW_H
