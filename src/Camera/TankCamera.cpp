//
// Created by steve on 2/10/18.
//

#include "../../include/Camera/TankCamera.h"

TankCamera::TankCamera() : BaseCamera() {
	this->type = CameraType::Tank;
	this->setTheta( 0 );
	this->setPhi( 0 );
	this->setRadius( 1 );
}
TankCamera::TankCamera(Point pTarget) : TankCamera() {
	this->setXYZ( pTarget );
}

void TankCamera::handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY) {
	BaseCamera::handleMouse( leftMouseButton, ctrlClick, x, y, mouseX, mouseY );

	this->incrementTheta( 0.005f * (x - mouseX));
	this->incrementPhi( 0.005f * (mouseY - y));
	if (this->getPhi() <= 0)
		this->setPhi( 0.05 );
	if (this->getPhi() >= 3.14)
		this->setPhi( 3.14 - 0.05 );
}
void TankCamera::updateCamera(std::vector<float> focus) {
	BaseCamera::updateCamera( focus );
	auto ptn = getLookDirection();
	ptn *= this->getRadius();

	this->setDirXYZ( ptn + this->getXYZ());
}
void TankCamera::lookAt(vector<float> vector1) {
	BaseCamera::lookAt( vector1 );
}
void TankCamera::keyPressCall(std::string val) {
	auto *vec = new Point( 0, 0, 0 );

	if (val == "w")
		vec->setX( 1 );
	else if (val == "s")
		vec->setX( -1 );
	if (val == "a")
		vec->setZ( -1 );
	else if (val == "d")
		vec->setZ( 1 );
	if (val == "r")
		vec->setY( 1 );
	else if (val == "f")
		vec->setY( -1 );

	this->incrementXYZ( *vec );

	delete vec;
}
