#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_
#include "../Camera/Camera.h"


class BaseScene
{

public:
    BaseScene() {
        cameras_ = Camera( CameraType::Arc );
        cameras_.cam()->setRadius( 50 );
    }
	virtual ~BaseScene() {}
	virtual void SetUp() = 0;

    virtual void Render() {
        auto cam = cameras_.cam();
        cam->lookAt( vector<float>());
        auto xyz = cam->getXYZ();
        auto dir = cam->getDirXYZ();
        auto up = cam->getUpXYZ();
        gluLookAt( xyz.getX(), xyz.getY(), xyz.getZ(),
                   dir.getX(), dir.getY(), dir.getZ(),
                   up.getX(), up.getY(), up.getZ());
    }

	virtual void RegisterEventLoop() = 0;
	virtual int InputQueue(SDL_Event*) = 0;

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
			auto vec = Point(0, 0, 0);
			switch (e->key.keysym.sym) {
				case SDLK_w:
					vec.setX(1);
					break;
				case SDLK_s:
					vec.setX(-1);
					break;
				case SDLK_d:
					vec.setZ(-1);
					break;
				case SDLK_a:
					vec.setZ(1);
					break;
				case SDLK_r:
					vec.setY(1);
					break;
				case SDLK_f:
					vec.setY(-1);
					break;
				case SDLK_p:
					if (cameras_.getType() == CameraType::Fp)
						cameras_.setType(CameraType::Arc);
					else
						cameras_.setType(CameraType::Fp);
			}
			if (cameras_.getType() == CameraType::Arc)
				cameras_.cam()->incrementDirXYZ(vec);
			else
				cameras_.cam()->incrementXYZ(vec);
		}
	}

protected:
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
    Camera cameras_;
    GLuint displayList;
    bool down = false;
    Sint32 x, y;
};

inline int EventHandler(void* pData, SDL_Event* e)
{
	auto data = static_cast<BaseScene*>(pData);
	return data->InputQueue(e);
}



#endif