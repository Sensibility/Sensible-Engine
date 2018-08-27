//
// Created by steve on 2/10/18.
//

#ifndef MAIN_CAMERA_H
#define MAIN_CAMERA_H


#include "ArcCamera.h"
#include <vector>
#include "TankCamera.h"
#include "FreeCamera.h"

class Camera {

public:
	Camera() {
		_cameras = std::vector<BaseCamera *>();
		_cameras.push_back( new ArcCamera( glm::vec3( 0, 0, 0 )));
		_cameras.push_back( new TankCamera( glm::vec3( 20, 20, 20 )));
		_cameras.push_back(new FreeCamera(glm::vec3(20, 20, 20)));
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
		return nullptr;
	}

	void setType(CameraType pType) {
		_active = pType;
	}
	CameraType getType() {
		return this->_active;
	}
private:
	std::vector<BaseCamera *> _cameras;
	CameraType _active;
};


#endif //MAIN_CAMERA_H
