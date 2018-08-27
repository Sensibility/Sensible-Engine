//
// Created by steve on 2/10/18.
//

#ifndef MAIN_ARCCAMERA_H
#define MAIN_ARCCAMERA_H


#include "BaseCamera.h"

class ArcCamera : public BaseCamera {
public:
	ArcCamera();
	explicit ArcCamera(glm::vec3 pTarget) : BaseCamera()
	{
		this->type = CameraType::Arc;
		this->setTheta( -3.14 / 3.f );
		this->setPhi( 3.14 / 1.8f );
		this->setRadius( 50 );
	};
	virtual void handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY)
	{
		if (ctrlClick) {
			this->incrementRadius( 0.01 * (mouseY - y));
			if (this->getRadius() < 1) this->setRadius( 1 );
		} else {

			this->incrementTheta( 0.005 * (x - mouseX));
			if (this->getTheta() <= -3.14 * 2)
				this->setTheta(fmod(this->getTheta(), -3.14 * 2));
			if (this->getTheta() >= 3.14 * 2)
				this->setTheta(fmod(this->getTheta(), 3.14 * 2));
			this->incrementPhi( 0.005 * (mouseY - y));
			if (this->getPhi() <= 0)
				this->setPhi( 0.05 );
			if (this->getPhi() >= 3.14)
				this->setPhi( 3.14 - 0.05 );
		}
	};

	virtual void updateCamera()
	{
		auto xyz = this->getDirXYZ();
		float cameraX = xyz.x + (this->getRadius()) * sin( this->getTheta()) * sin( this->getPhi());
		float cameraY = xyz.y + (this->getRadius()) * -cos( this->getPhi());
		float cameraZ = xyz.z + (this->getRadius()) * -cos( this->getTheta()) * sin( this->getPhi());

		this->setXYZ( glm::vec3( cameraX, cameraY, cameraZ ));
	};

	virtual void keyPressCall(std::string val)
	{
		auto *vec = new glm::vec3( 0 );
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

		this->incrementDirXYZ( *vec );

		delete vec;
	};

	virtual glm::vec3 getLookDirection() override
	{
		return glm::vec3(0);
	};
};


#endif //MAIN_ARCCAMERA_H
