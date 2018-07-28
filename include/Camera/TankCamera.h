//
// Created by steve on 2/10/18.
//

#ifndef _MAIN_FPCAMERA_H
#define _MAIN_FPCAMERA_H


#include "baseCamera.h"

class TankCamera : public BaseCamera {
public:
	TankCamera();
	TankCamera(Point pTarget);
	virtual void handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY);

	virtual void updateCamera(std::vector<float> focus);

	virtual void lookAt(vector<float> vector1);
	virtual void keyPressCall(std::string val) override;

	virtual Point getLookDirection()
	{
		return Point(
			sin(this->getTheta()) * sin(this->getPhi()),
			-cos(this->getPhi()),
			-cos(this->getTheta()) * sin(this->getPhi())
		);
	}
};


#endif //MAIN_FPCAMERA_H
