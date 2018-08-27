#include <vector>
#include "include/Windows/SDLWindow.h"
#include "include/Windows/ShaderWindow.h"
#include "include/RenderObject/ObjectProvider.h"
#include "include/Windows/LightingWindow.h"
#include "include/Windows/BenchWindow.h"

template<class T> SDLWindow* CreateSDLWindow() { return new T(); }
typedef SDLWindow* (*WindowHandle)();

int ChangeWindow(std::vector<std::string>& pTokens, void* pContext)
{
	auto window = SEMap<std::string, WindowHandle>();
	window.Insert("Shader", &CreateSDLWindow<ShaderWindow>);
	window.Insert("Lighting", &CreateSDLWindow<LightingWindow>);

	SDLWindow* r = static_cast<SDLWindow*>(pContext);
	if (pTokens.size() < 2)
		return 1;
	if (window.Find(pTokens.at(1)))
	{
		r = window[pTokens.at(1)]();
		r->SetUp();
		r->Start();
		return 0;
	}
	return 1;
}

void testBench()
{
	GLuint vao; GLuint vbo; GLuint texture; GLuint uniformSampler;
	SDL_Init(SDL_INIT_VIDEO);
	auto window = SDL_CreateWindow("test", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS);
	auto context = SDL_GL_CreateContext(window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, 640, 480);
	glClearColor(0.0, 0.3, 0.3, 1);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto f = (FontProvider*)GetProvider<FontProvider>();
	auto font = f->OpenFont("assets\\roboto\\Roboto-Black.ttf", "Robo");
	font->InitBuffers();
	SEGL::ErrorCheck(__LINE__);
	SdlErrorCheck(__LINE__);

	while (true) {
		glClear(GL_COLOR_BUFFER_BIT);

		font->Render("HellO", glm::ortho(0.0f, (GLfloat)640, 0.f, (GLfloat)480), glm::vec2(100, 100), glm::vec3(0.5, 0.8, 0.2), 1);
		
		SEGL::ErrorCheck(__LINE__, __FILE__);
		SdlErrorCheck(__LINE__);	
		SDL_GL_SwapWindow(window);
	}
}

int main(int argc, char *argv[]) {
	SDLWindow* w = new BenchWindow();
	Console::Register("Load", Command(&ChangeWindow, w));
	w->SetUp();
	w->Start();

	return 0;
}
