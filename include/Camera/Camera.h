//
// Created by steve on 2/10/18.
//

#ifndef MAIN_CAMERA_H
#define MAIN_CAMERA_H


#include "arcCamera.h"
#include "fpCamera.h"
#include "../console.h"

class Camera : ConsoleCommand {

public:
	Camera() {
		_cameras = vector<BaseCamera *>();
		_cameras.push_back( new ArcCamera( Point( 0, 0, 0 )));
		_cameras.push_back( new FpCamera( Point( 20, 20, 20 )));
	}
	Camera(CameraType pType) : Camera() {
		this->setType( pType );
	}

	BaseCamera *cam() {
		return this->getActive();
	}

	BaseCamera *getActive() {
		for (auto it = _cameras.begin(); it != _cameras.end(); ++it) {
			if ((*it)->type == this->_active)
				return *it;
		}
		return NULL;
	}

	void setType(CameraType pType) {
		_active = pType;
	}
	CameraType getType() {
		return this->_active;
	}

	std::vector<Command *> getCommands() {
		auto cmds = vector<Command *>();

		string prefix = "cam.";



		return cmds;
	};
private:
	std::vector<BaseCamera *> _cameras;
	CameraType _active;
};


#endif //MAIN_CAMERA_H
