#ifndef CAMERA
#define CAMERA

#include <string>
#include <vector>
#include <math.h>
#include <iostream>

#include "../vector.h"
#include "../point.h"

enum class CameraType {
	Arc = 0, Fp = 1
};

class BaseCamera {
public:
	BaseCamera();

	virtual void lookAt(vector<float> vector1);

	virtual Point getXYZ() { return this->eye; };
	virtual void setXYZ(Point pEye) { this->eye = pEye; }

	virtual Point getDirXYZ() { return this->target; };
	virtual void setDirXYZ(Point pTarget) { this->target = pTarget; }

	virtual Point getUpXYZ() { return this->up; };
	virtual void setUpXYZ(Point pUp) { this->up = pUp; }

	virtual float getRadius() { return this->radius; };
	virtual void setRadius(float pRadius) { this->radius = pRadius; };

	virtual float getTheta() { return this->theta; };
	virtual void setTheta(float pTheta) { this->theta = pTheta; };

	virtual float getPhi() { return this->phi; };
	virtual void setPhi(float pPhi) { this->phi = pPhi; };

	virtual void incrementRadius(float r) { this->radius += r; };
	virtual void incrementXYZ(Point pEye) { this->eye = this->eye + pEye; }
	virtual void incrementDirXYZ(Point pTarget) { this->target = this->target + pTarget; }
	virtual void incrementTheta(float theta) { this->theta += theta; };
	virtual void incrementPhi(float phi) { this->phi += phi; };

	virtual void handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY) { };

	virtual void updateCamera(std::vector<float> focus) { };
	virtual void handleKeyPress(std::string val) { };

	virtual void keyPressCall(string basic_string) = 0;

	CameraType type;
private:
	Point eye, target, up;
	float theta, phi, radius;

};

#endif

