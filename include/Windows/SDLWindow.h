#ifndef _SDL_WINDOW_H_
#define _SDL_WINDOW_H_

#ifdef _WIN32
#include<windows.h>
#endif

#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <sdl2/sdl.h>
#include "../Renderer/OpenGL.h"
#include "../console.h"
#include "../BaseProvider.h"
#include "../Renderer/Skybox.h"
#include "../Camera/Camera.h"
#include "../../lib/glm/glm/gtc/matrix_transform.hpp"
#include "../Renderer/SDL.h"
#include "../Texture/Images/ImageProvder.h"
#include "../Texture/TextureProvider.h"
#include "../Texture/Text/FontProvider.h"
#include "../Shaders/ShaderProvider.h"
#include "../RenderObject/ObjectProvider.h"

int EventHandle(void* pData, SDL_Event* e);
class SDLWindow
{
public:
	SDLWindow()
	{
        cameras_ = Camera( CameraType::Free );
        cameras_.cam()->setRadius( 50 );
	}
	virtual ~SDLWindow()
	{
		WindowTearDown();
		SDLExtTearDown();

		SDL_Quit();
	};
	virtual void WindowTearDown()
	{
		if (window_)
			SDL_DestroyWindow(window_);
		if (context_)
			SDL_GL_DeleteContext(context_);
	}
	virtual void SDLExtTearDown()
	{
	}

	virtual void Start()
	{
		while (true) {
			Loop();
		}
	}

	virtual void Loop()
	{
		GetUserInput();
		SdlErrorCheck(__LINE__, true);

		Render();
		SEGL::ErrorCheck(__LINE__, __FILE__);

		SDL_GL_SwapWindow(window_);
		SEGL::ErrorCheck(__LINE__, __FILE__);
		SdlErrorCheck(__LINE__, true);
	}

	virtual void InitView(glm::vec3 xyz, glm::vec3 dir, glm::vec3 up) = 0;

	virtual void Render()
	{
        auto cam = cameras_.cam();
        cam->lookAt();
        glm::vec3 xyz = cam->getXYZ();
        glm::vec3 dir = cam->getDirXYZ();
        glm::vec3 up = cam->getUpXYZ();
		InitView(xyz, dir, up);

		SEGL::ErrorCheck(__LINE__, __FILE__);

		DrawAxis(NULL, glm::vec3(0));
	}

	virtual void DrawAxis(int pSize, glm::vec3 pHome) = 0;

	virtual void GetUserInput()
	{
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
		}
	}

	void SetUp()
	{
		if (SDL_Init(SDLFlags()) < 0)
			fprintf(stderr, "Failed to init SDL\n");

		SDLGLSetUp();
		SdlErrorCheck(__LINE__);

		SDLExtSetUp();
		SdlErrorCheck(__LINE__);

		WindowSetUp();
		SdlErrorCheck(__LINE__);

		GLExtSetUp();
		SEGL::ErrorCheck(__LINE__, __FILE__);

		SDL_GL_SetSwapInterval(1);
		Diagnostics();

		GLSetUp();

		SEGL::ErrorCheck(__LINE__, __FILE__);
		SdlErrorCheck(__LINE__);
	}

	virtual void SDLGLSetUp() = 0;

	TextureProvider* texture_;
	ShaderProvider* shaders_;

	ObjectProvider* object_;

	virtual void SDLExtSetUp()
	{
		image_ = (ImageProvider*) GetProvider<ImageProvider>();
		font_ = (FontProvider*) GetProvider<FontProvider>();
		texture_ = (TextureProvider*)GetProvider<TextureProvider>();
		object_ = (ObjectProvider*)GetProvider<ObjectProvider>();
	}

	virtual void WindowSetUp()
	{
		width_ = 1150;
		height_ = 650;
		window_ = SDL_CreateWindow(Name(), 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width_, height_, WindowFlags());
		if (!window_)
			fprintf(stderr, "Failed to create window\n");

		ContextSetUp();
	}
	
	virtual void ContextSetUp()
	{
		context_ = SDL_GL_CreateContext(window_);
		if (!context_)
			fprintf(stderr, "Failed to create context\n");
	}

	virtual void GLExtSetUp()
	{
		if (glewInit() != GLEW_OK)
			fprintf(stderr, "GLEW error\n");
	}

	virtual void GLSetUp()
	{
		shaders_ = (ShaderProvider*)GetProvider<ShaderProvider>();
		font_->OpenFont(R"(assets\roboto\Roboto-Black.ttf)", "Robo");
        SEGL::ErrorCheck( __LINE__, __FILE__ );

		SceneSetUp();
		RegisterEventLoop();
	}

	virtual void SceneSetUp()
	{
        glClearColor( 0, 0, 0.3, 0 );
        SEGL::ErrorCheck( __LINE__, __FILE__ );
        glViewport( 0, 0, width_, height_ );
        SEGL::ErrorCheck( __LINE__, __FILE__ );

		InitProjection();

		InitModel();
	}

	virtual void InitModel() = 0;
	virtual void InitProjection() = 0;

	virtual void RegisterEventLoop()
	{
		SDL_AddEventWatch(EventHandle, this);
	}

	virtual int InputQueue(SDL_Event* e)
	{
		HandleKey(e);
		return 0;
	}

	static const char* Name() { return "Main"; }
protected:
	Sint32 x = 0, y = 0;
	bool down = false;
	Camera cameras_;
	FontProvider* font_;
	SDL_Window * window_;
	SDL_GLContext context_;
	Skybox* skybox_;
	int height_, width_;
	ImageProvider* image_;

	void HandleKey(SDL_Event* e)
	{
		if (e->type == SDL_MOUSEBUTTONDOWN) {
			x = e->motion.x;
			y = e->motion.y;
			down = true;
		} else if (e->type == SDL_MOUSEBUTTONUP) {
			down = false;
		} else if (e->type == SDL_MOUSEMOTION) {
			if (down)
				cameras_.cam()->handleMouse( 0, false, x, y, e->motion.x, e->motion.y );
			x = e->motion.x;
			y = e->motion.y;
		} else if (e->type == SDL_KEYDOWN) {
			switch (e->key.keysym.sym) {
				case SDLK_p:
					if (cameras_.getType() == CameraType::Tank)
						cameras_.setType(CameraType::Arc);
					else if (cameras_.getType() == CameraType::Arc)
						cameras_.setType(CameraType::Free);
					else
						cameras_.setType(CameraType::Tank);
				case SDLK_q:
					exit(0);
				case SDLK_o:
					Console::Activate();
					return;
					
			}
			auto cam = cameras_.cam();
			cam->handleKeyPress(e->key.keysym.sym);
		}
	}

	void Diagnostics() {
		GLint maxVertexAttribs = 0;
		glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs );

		GLint maxLights = 0;
		glGetIntegerv( GL_MAX_LIGHTS, &maxLights );

		GLint maxTextures = 0;
		glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures );

		std::string* diags;
		std::vector<std::string*>* diagsGrp;

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

		diagsGrp = SEGL::BufferDiagnostics();
		for(auto& diag: *diagsGrp)
		{
			fprintf( stdout, "[INFO]: |   %14s:  %35s |\n", diag[0].c_str(), diag[1].c_str());
		}

		GLint totalMemKB, availMemKB, dedMemKB;
		glGetIntegerv(GL_GPU_MEM_TOTAL_AVAILABLE_NVX, &totalMemKB);
		glGetIntegerv(GL_GPU_MEM_CURRENT_AVAILABLE_NVX, &availMemKB);
		glGetIntegerv(GL_GPU_MEM_DED_AVAILABLE_NVX, &dedMemKB);
		fprintf(stdout, "[INFO]: |  Total Memory MB:  %35i |\n", totalMemKB/(1024));
		fprintf(stdout, "[INFO]: |  Avail Memory MB:  %35i |\n", availMemKB/1024);
		fprintf(stdout, "[INFO]: |  Dedic Memory MB:  %35i |\n", dedMemKB/1024);
		fprintf( stdout, "[INFO]: \\--------------------------------------------------------/\n\n" );
	}

	virtual Uint32 SDLFlags() { return SDL_INIT_VIDEO; }
	virtual Uint32 WindowFlags() { return SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN; }
};

int EventHandle(void* pData, SDL_Event* e)
{
	auto data = static_cast<SDLWindow*>(pData);
	return data->InputQueue(e);
}

#endif _SDL_WINDOW_H_