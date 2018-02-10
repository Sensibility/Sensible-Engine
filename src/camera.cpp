
#include "../include/camera.h"

float Camera::getX() {
	return this->x;
}

float Camera::getY() {
	return this->y;
}

float Camera::getZ() {
	return this->z;
}

std::string Camera::getType() {
	return this->type;
}

float Camera::getRadius() {
	return this->radius;
}

float Camera::getDirX() {
	return this->dirX;
}

float Camera::getDirY() {
	return this->dirY;
}

float Camera::getDirZ() {
	return this->dirZ;
}

float Camera::getUpX() {
	return this->upX;
}

float Camera::getUpY() {
	return this->upY;
}

float Camera::getUpZ() {
	return this->upZ;
}

float Camera::getTheta() {
	return this->theta;
}

float Camera::getPhi() {
	return this->phi;
}

std::string Camera::getFocus() {
	return this->focus;
}

void Camera::setType(std::string type, std::vector<float> focus) {
	this->type = type;
	if (type == CAMERA_ARC) this->initArc( focus );
	else if (type == CAMERA_FREE) this->initFree( focus );
	else if (type == CAMERA_FIRST_PERSON) this->initFP( focus );
}

void Camera::setRadius(float radius) {
	this->radius = radius;
}

void Camera::setXYZ(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Camera::setPosition(Point newPosition) {
	x = newPosition.getX();
	y = newPosition.getY();
	z = newPosition.getZ();
}

void Camera::setDirXYZ(float dirX, float dirY, float dirZ) {
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = dirZ;
}

void Camera::setDirection(Vector newDirection) {
	dirX = newDirection.getX();
	dirY = newDirection.getY();
	dirZ = newDirection.getZ();
}

void Camera::setUpXYZ(float upX, float upY, float upZ) {
	this->upX = upX;
	this->upY = upY;
	this->upZ = upZ;
}

void Camera::setUp(Vector newUp) {
	upX = newUp.getX();
	upY = newUp.getY();
	upZ = newUp.getZ();
}

void Camera::setTheta(float theta) {
	this->theta = theta;
}

void Camera::setPhi(float phi) {
	this->phi = phi;
}

void Camera::incrementXYZ(Vector pVec) {
	this->incrementXYZ( pVec.getX(), pVec.getY(), pVec.getZ());
}

void Camera::incrementXYZ(float x, float y, float z) {
	this->x += x;
	this->y += y;
	this->z += z;
}

void Camera::incrementDirXYZ(Vector pVec) {
	this->incrementDirXYZ( pVec.getX(), pVec.getY(), pVec.getZ());
}

void Camera::incrementDirXYZ(float dirX, float dirY, float dirZ) {
	this->dirX += dirX;
	this->dirY += dirY;
	this->dirZ += dirZ;
}

void Camera::incrementTheta(float theta) {
	this->theta += theta;
}

void Camera::incrementPhi(float phi) {
	this->phi += phi;
}

void Camera::incrementRadius(float r) {
	this->radius += r;
}

void Camera::setFocus(std::string focus) {
	this->focus = focus;
}

void Camera::initArc(std::vector<float> focus) {
	this->setXYZ( 60 + focus[0], 60 + focus[1], 60 + focus[2] );
	this->setDirXYZ( focus[0], focus[1], focus[2] );
	this->setTheta( -M_PI / 3.0f );
	this->setPhi( M_PI / 1.8f );
	this->setRadius( 1 );
}

void Camera::initFree(std::vector<float> focus) {
	this->setXYZ( 60 + focus[0], 40 + focus[1], 30 + focus[2] );
	this->setTheta( -M_PI / 3.0f );
	this->setPhi( M_PI / 2.8f );
	this->setRadius( 0.0f );
	this->updateCamera( focus );
}

void Camera::initFP(std::vector<float> focus) {
	this->setXYZ( focus[0], focus[1], focus[2] );
	this->updateCamera( focus );
}

std::vector<float> Camera::setLookAt(std::vector<float> focus) {

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
}

void Camera::updateCamera(std::vector<float> focus) {
	if (this->type == CAMERA_FREE) {
		float cameraDirX = sinf( this->getTheta()) * sinf( this->getPhi());
		float cameraDirZ = -cosf( this->getTheta()) * sinf( this->getPhi());
		float cameraDirY = -cosf( this->getPhi());

		//and normalize this directional vector!
		float mag = sqrt( cameraDirX * cameraDirX + cameraDirY * cameraDirY + cameraDirZ * cameraDirZ );
		cameraDirX /= mag;
		cameraDirY /= mag;
		cameraDirZ /= mag;
		this->setDirXYZ( cameraDirX, cameraDirY, cameraDirZ );
	} else if (this->type == CAMERA_ARC) {
		float cameraX = this->radius * sin( this->getTheta()) * sin( this->getPhi());
		float cameraY = this->radius * -cos( this->getPhi());
		float cameraZ = this->radius * -cos( this->getTheta()) * sin( this->getPhi());

		this->setXYZ( cameraX, cameraY, cameraZ );
	} else if (this->type == CAMERA_FIRST_PERSON) {
		this->setXYZ( focus[0], focus[1], focus[2] );
		this->setDirXYZ( focus[3], focus[4], focus[5] );
	}
}

void Camera::handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY) {
	if (this->type == CAMERA_FREE) {
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
		}
	} else if (this->type == CAMERA_ARC) {
		if (ctrlClick) {
			this->radius += 0.01 * (mouseY - y);
			if (this->radius < 1) this->radius = 1;
		} else {

			this->incrementTheta( 0.005 * (x - mouseX));
			this->incrementPhi( 0.005 * (mouseY - y));
			if (this->getPhi() <= 0)
				this->setPhi( 0.05 );
			if (this->getPhi() >= M_PI)
				this->setPhi( M_PI - 0.05 );
		}

	}
}
