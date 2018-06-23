
#include "../../include/Camera/baseCamera.h"

BaseCamera::BaseCamera() {
	this->setUpXYZ( Point( 0, 1, 0 ));
	this->setDirXYZ( Point( 0, 0, 0 ));
	this->setXYZ( Point( 0, 0, 0 ));

	this->setTheta( 0 );
	this->setPhi( 0 );
	this->setRadius( 1 );
}

void BaseCamera::lookAt(vector<float> vector) {
	this->updateCamera( vector );
}
