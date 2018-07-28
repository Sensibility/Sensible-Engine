#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_
#include "../Camera/Camera.h"
#include "../Renderer/OpenGL.h"
#include "../Renderer/Textures.h"
#include "../Renderer/SDL.h"
#include "../Renderer/Skybox.h"

int EventHandler(void* pData, SDL_Event* e);

class BaseScene
{

public:
    BaseScene() {
        cameras_ = Camera( CameraType::Free );
        cameras_.cam()->setRadius( 50 );
    }
	virtual ~BaseScene() = default;


	virtual void SetUp()
    {
		skybox_ = new Skybox("assets\\skybox");
		displayList_ = glGenLists(1);
		glNewList(displayList_, GL_COMPILE);
		GLErrorCheck(__LINE__, __FILE__);

		glPushMatrix();
		glLineWidth(3);

		glColor3f(1, 0, 0);
		GLErrorCheck(__LINE__, __FILE__);
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(100, 0, 0);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 100, 0);
		glEnd();

		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 100);
		glEnd();

		glPopMatrix();
		glEndList();

		GLErrorCheck(__LINE__, __FILE__);

    }
	virtual void SdlSetUp() {};
	

    virtual void Render() {
        auto cam = cameras_.cam();
        cam->lookAt( vector<float>());
        Point xyz = cam->getXYZ();
        Point dir = cam->getDirXYZ();
        Point up = cam->getUpXYZ();
        gluLookAt( xyz.getX(), xyz.getY(), xyz.getZ(),
                   dir.getX(), dir.getY(), dir.getZ(),
                   up.getX(), up.getY(), up.getZ());

		GLErrorCheck(__LINE__, __FILE__);

		skybox_->DrawSkybox(200);
		GLErrorCheck(__LINE__, __FILE__);
    }

	virtual void RegisterEventLoop()
	{
		SDL_AddEventWatch(EventHandler, this);
	}

	virtual int InputQueue(SDL_Event* e)
	{
		HandleKey(e);
		return 0;
	}

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
			}
			auto cam = cameras_.cam();
			cam->handleKeyPress(e->key.keysym.sym);
		}
	}

protected:
    Camera cameras_;
    bool down = false;
    Sint32 x, y;
	Skybox* skybox_;
	GLuint displayList_;
};


int EventHandler(void* pData, SDL_Event* e)
{
	auto data = static_cast<BaseScene*>(pData);
	return data->InputQueue(e);
}


#endif