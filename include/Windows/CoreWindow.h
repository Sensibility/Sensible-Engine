#ifndef _CORE_WINDOW_H_
#define _CORE_WINDOW_H_
#include "SDLWindow.h"

std::string v_passthru =  (std::string)
"#version 450 core\n" +
"layout(location = 0) in vec3 vPos_M;\n" +
"layout(location = 1) in vec2 vUV;\n" +
"layout(location = 2) in vec3 vNorm_M;\n" +
"out vec2 UV;\n" +
"uniform mat4 MVP;\n" +
"void main() { \n" +
	"gl_Position = MVP * vec4(vPos_M, 1.0);\n" +
	"UV = vUV;\n" + 
"}\n" ;
std::string f_passthru = (std::string)
"#version 450 core\n" +
"in vec2 UV;\n"+
"out vec3 color;\n"+
"uniform sampler2D tex;\n"+
"void main() { \n"+
	"color = texture(tex, UV).rgb;\n"+
"}\n" ;

class CoreWindow;

int PolygonMode(std::vector<std::string>& pStrs, void* pContext)
{
	auto ctx = (CoreWindow*)pContext;

	if(pStrs.size() == 2)
	{
		if (pStrs.at(1) == "point")
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		else if(pStrs.at(1) == "line")
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else if(pStrs.at(1) == "fill" || pStrs.at(1) == "default")
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	return 0;
}

class CoreWindow : public SDLWindow
{
public:
	CoreWindow() : SDLWindow()
	{
		Console::Register("Mode", &PolygonMode);
	}

	~CoreWindow() { Console::DeRegister("Mode"); }

	void SDLGLSetUp() override
	{
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 5 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	}

	void InitView(glm::vec3 xyz, glm::vec3 dir, glm::vec3 up) override
	{
		view_ = glm::lookAt(xyz, dir, up);
        SEGL::ErrorCheck( __LINE__, __FILE__ );
	}

	void DrawAxis(int pSize, glm::vec3 pHome) override
	{
		SEGL::ErrorCheck(__LINE__, __FILE__);
	}

	void InitProjection() override
	{
		proj_ = glm::perspective(45.f, (float)width_ / (float)height_, 0.1f, 100.f);
        SEGL::ErrorCheck( __LINE__, __FILE__ );
	}

	void InitModel() override
	{
		model_ = ident_;
	}

	void GLSetUp() override
	{
		SDLWindow::GLSetUp();
	}

	glm::mat4 MVP()
	{
		return proj_ * view_ * model_;
	}
protected:
	glm::mat4 proj_, view_, model_;
	glm::mat4 ident_ = glm::mat4(1.f);
};

#endif _CORE_WINDOW_H_