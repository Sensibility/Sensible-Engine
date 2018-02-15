
#include "../../include/Camera/baseCamera.h"
/*
void BaseCamera::initArc(std::vector<float> focus) {
	this->setXYZ( 60 + focus[0], 60 + focus[1], 60 + focus[2] );
	this->setDirXYZ( focus[0], focus[1], focus[2] );
	this->setTheta( -M_PI / 3.0f );
	this->setPhi( M_PI / 1.8f );
	this->setRadius( 1 );
}

void BaseCamera::initFree(std::vector<float> focus) {
	this->setXYZ( 60 + focus[0], 40 + focus[1], 30 + focus[2] )
	this->setTheta( -M_PI / 3.0f );
	this->setPhi( M_PI / 2.8f );
	this->setRadius( 0.0f );
	this->updateCamera( focus );
}

void BaseCamera::initFP(std::vector<float> focus) {
	this->setXYZ( focus[0], focus[1], focus[2] );
	this->updateCamera( focus );
}*/

/*std::vector<float> BaseCamera::setLookAt(std::vector<float> focus) {

	std::vector<float> ret;
	if (this->type == CAMERA_FREE) {
		ret.push_back( this->getX() + this->getDirX() * this->getRadius());
		ret.push_back( this->getY() + this->getDirY() * this->getRadius());
		ret.push_back( this->getZ() + this->getDirZ() * this->getRadius());

		ret.push_back( this->getX() + this->getDirX());
		ret.push_back( this->getY() + this->getDirY());
		ret.push_back( this->getZ() + this->getDirZ());
	} else if (this->type == CAMERA_ARC) {
		ret.push_back( this->getX() + focus[0] );
		ret.push_back( this->getY() + focus[1] );
		ret.push_back( this->getZ() + focus[2] );

		ret.push_back( focus[0] );
		ret.push_back( focus[1] );
		ret.push_back( focus[2] );
	} else if (this->type == CAMERA_FIRST_PERSON) {
		ret.push_back( focus[0] );
		ret.push_back( focus[1] );
		ret.push_back( focus[2] );

		ret.push_back( focus[3] );
		ret.push_back( focus[4] );
		ret.push_back( focus[5] );
	}
	ret.push_back( 0.0f );
	ret.push_back( 1.0f );
	ret.push_back( 0.0f );
	return ret;
}*/

/*	if (this->type == CAMERA_FREE) {
		float cameraDirX = sinf( this->getTheta()) * sinf( this->getPhi());
		float cameraDirZ = -cosf( this->getTheta()) * sinf( this->getPhi());
		float cameraDirY = -cosf( this->getPhi());

		//and normalize this directional vector!
		float mag = sqrt( cameraDirX * cameraDirX + cameraDirY * cameraDirY + cameraDirZ * cameraDirZ );
		cameraDirX /= mag;
		cameraDirY /= mag;
		cameraDirZ /= mag;
		this->setDirXYZ( cameraDirX, cameraDirY, cameraDirZ );
	} else if (this->type == CAMERA_FIRST_PERSON) {
		this->setXYZ( focus[0], focus[1], focus[2] );
		this->setDirXYZ( focus[3], focus[4], focus[5] );
	}*/

/*	if (this->type == CAMERA_FREE) {
		if (!ctrlClick) {
			this->incrementTheta((x - mouseX) * 0.005 );
			this->incrementPhi((mouseY - y) * 0.005 );

			// make sure that phi stays within the range (0, M_PI)
			if (this->getPhi() <= 0)
				this->setPhi( 0 + 0.001 );
			if (this->getPhi() >= M_PI)
				this->setPhi( M_PI - 0.001 );
		} else {
			this->incrementRadius(((x - mouseX) + (y - mouseY)) * 0.01 );
			if (this->getRadius() < -2.5) {
				this->setRadius( -2.5f );
			}
			if (this->getRadius() > 0.5) {
				this->setRadius( 0.5f );
			}
		}*/

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
