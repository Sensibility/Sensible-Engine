//
// Created by steve on 2/10/18.
//

#include "../../include/Camera/ArcCamera.h"

void ArcCamera::handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY) {
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
}

void ArcCamera::updateCamera(std::vector<float> focus) {
	auto xyz = this->getDirXYZ();
	float cameraX = xyz.getX() + (this->getRadius()) * sin( this->getTheta()) * sin( this->getPhi());
	float cameraY = xyz.getY() + (this->getRadius()) * -cos( this->getPhi());
	float cameraZ = xyz.getZ() + (this->getRadius()) * -cos( this->getTheta()) * sin( this->getPhi());

	this->setXYZ( Point( cameraX, cameraY, cameraZ ));
}
ArcCamera::ArcCamera() : BaseCamera() {
	this->type = CameraType::Arc;
	this->setTheta( -3.14 / 3.f );
	this->setPhi( 3.14 / 1.8f );
	this->setRadius( 50 );
}

ArcCamera::ArcCamera(Point pTarget) : ArcCamera() {
	this->setDirXYZ( pTarget );
	this->setXYZ( Point( pTarget.getX() + 60, pTarget.getY() + 60, pTarget.getZ() + 60 ));
}
void ArcCamera::lookAt(vector<float> vector) {
	BaseCamera::lookAt( vector );
}
void ArcCamera::keyPressCall(std::string val) {
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

	this->incrementDirXYZ( *vec );

	delete vec;
}
