//
// Created by steve on 2/10/18.
//

#ifndef _MAIN_FPCAMERA_H
#define _MAIN_FPCAMERA_H


#include "BaseCamera.h"

class TankCamera : public BaseCamera {
public:
	TankCamera() : BaseCamera()
	{
		this->type = CameraType::Tank;
		this->setTheta( 1 );
		this->setPhi( 1 );
		this->setRadius( 1 );
	};
	TankCamera(glm::vec3 pTarget) : TankCamera()
	{
		this->setXYZ( pTarget );
	};
	virtual void handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY)
	{
		BaseCamera::handleMouse( leftMouseButton, ctrlClick, x, y, mouseX, mouseY );

		this->incrementTheta( 0.005f * (x - mouseX));
		this->incrementPhi( 0.005f * (mouseY - y));
		if (this->getPhi() <= 0)
			this->setPhi( 0.05 );
		if (this->getPhi() >= 3.14)
			this->setPhi( 3.14 - 0.05 );
	};

	virtual void updateCamera()
	{
		BaseCamera::updateCamera();
		auto ptn = getLookDirection();
		ptn *= this->getRadius();

		this->setDirXYZ( ptn + this->getXYZ());
	};

	virtual void keyPressCall(std::string val) override
	{
		auto *vec = new glm::vec3( 0);

		if (val == "w")
			vec->x = ( 1 );
		else if (val == "s")
			vec->x = ( -1 );
		if (val == "a")
			vec->z = ( -1 );
		else if (val == "d")
			vec->z = ( 1 );
		if (val == "r")
			vec->y = ( 1 );
		else if (val == "f")
			vec->y = ( -1 );

		this->incrementXYZ( *vec );

	delete vec;
	};

	virtual glm::vec3 getLookDirection()
	{
		return glm::vec3(
			sin(this->getTheta()) * sin(this->getPhi()),
			-cos(this->getPhi()),
			-cos(this->getTheta()) * sin(this->getPhi())
		);
	}
};


#endif //MAIN_FPCAMERA_H
