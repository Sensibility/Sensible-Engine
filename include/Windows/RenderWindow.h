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
#include <iostream>
#include "../console.h"
#include "../Scene/BaseScene.h"


int t(std::vector<std::string>& pTokens) {
	for(auto& tok: pTokens)
		printf("%s, ", tok.c_str());
	printf("\n");
	return 0;
}

class RenderWindow {
public:
	~RenderWindow() {
		SDL_GL_DeleteContext( context );
		SDL_DestroyWindow( window );

		SDL_Quit();
	}

	void RegisterScene(BaseScene* pScene) {
		active_ = pScene;
	}

	void GLErrorCheck(int lineNum) const {
		auto err = glGetError();
		if (err != GL_NO_ERROR)
			fprintf( stderr, "ERR: %s, %i\n", gluErrorString( err ), lineNum );
	}

	void SdlErrorCheck(int lineNum, bool clear = false) {
		std::string sdlErr = SDL_GetError();
		if (sdlErr != "") {
			std::cout << "ERR: " << sdlErr << ", " << lineNum << std::endl;
			if (clear)
				SDL_ClearError();
		}
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
			std::cout << "Failed to init SDL\n" << std::endl;
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
			std::cout << "Failed to create window" << std::endl;
		context = SDL_GL_CreateContext( window );
		SdlErrorCheck( __LINE__, true );

		//vsync
		if (SDL_GL_SetSwapInterval( 1 ) < 0)
			SdlErrorCheck( __LINE__, true );

		Console::Register("lol", &t);

		active_->SetUp();
		active_->RegisterEventLoop();

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
	BaseScene* active_;
};

#endif //MAIN_RENDERWINDOW_H
