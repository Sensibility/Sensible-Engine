//
// Created by steve on 2/10/18.
//

#include "../../include/Camera/fpCamera.h"

FpCamera::FpCamera() : BaseCamera() {
	this->type = Fp;
	this->setTheta( 0 );
	this->setPhi( 0 );
	this->setRadius( 1 );
}
FpCamera::FpCamera(Point pTarget) : FpCamera() {
	this->setXYZ( pTarget );
}

void FpCamera::handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY) {
	BaseCamera::handleMouse( leftMouseButton, ctrlClick, x, y, mouseX, mouseY );

	this->incrementTheta( 0.005 * (x - mouseX));
	this->incrementPhi( 0.005 * (mouseY - y));
	if (this->getPhi() <= 0)
		this->setPhi( 0.05 );
	if (this->getPhi() >= M_PI)
		this->setPhi( M_PI - 0.05 );
}
void FpCamera::updateCamera(std::vector<float> focus) {
	BaseCamera::updateCamera( focus );
	auto xCalc = sin( this->getTheta()) * sin( this->getPhi());
	auto yCalc = -cos( this->getPhi());
	auto zCalc = -cos( this->getTheta()) * sin( this->getPhi());
	auto ptn = Point( xCalc, yCalc, zCalc );
	ptn *= this->getRadius();

	this->setDirXYZ( ptn + this->getXYZ());
}
void FpCamera::lookAt(vector<float> vector1) {
	BaseCamera::lookAt( vector1 );
}
void FpCamera::keyPressCall(std::string val) {
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
