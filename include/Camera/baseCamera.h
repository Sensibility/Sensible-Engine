#ifndef CAMERA
#define CAMERA

#include <string>
#include <vector>
#include <math.h>
#include <iostream>

#include "SDL2/SDL.h"
#include "../../lib/glm/glm/detail/type_vec3.hpp"

enum class CameraType {
	Arc = 0, Tank = 1, Free = 2
};

class BaseCamera {
public:
	BaseCamera()
	{
		setUpXYZ(glm::vec3(0, 1, 0));
		setDirXYZ(glm::vec3(0, 0, 0));
		setXYZ(glm::vec3(0, 0, 0));

		setTheta(0); setPhi(0); setRadius(1);
	};

	virtual void lookAt() { this->updateCamera(); };

	virtual glm::vec3 getXYZ() { return this->eye; };
	virtual void setXYZ(glm::vec3 pEye) { this->eye = pEye; }

	virtual glm::vec3 getDirXYZ() { return this->target; };
	virtual void setDirXYZ(glm::vec3 pTarget) { this->target = pTarget; }

	virtual glm::vec3 getUpXYZ() { return this->up; };
	virtual void setUpXYZ(glm::vec3 pUp) { this->up = pUp; }

	virtual float getRadius() { return this->radius; };
	virtual void setRadius(float pRadius) { this->radius = pRadius; };

	virtual float getTheta() { return this->theta; };
	virtual void setTheta(float pTheta) { this->theta = pTheta; };

	virtual float getPhi() { return this->phi; };
	virtual void setPhi(float pPhi) { this->phi = pPhi; };

	virtual void incrementRadius(float r) { this->radius += r; };
	virtual void incrementXYZ(glm::vec3 pEye) { this->eye = this->eye + pEye; }
	virtual void incrementDirXYZ(glm::vec3 pTarget) { this->target = this->target + pTarget; }
	virtual void incrementTheta(float theta) { this->theta += theta; };
	virtual void incrementPhi(float phi) { this->phi += phi; };

	virtual void handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY) { };

	virtual void updateCamera() { };
	virtual void handleKeyPress(int val)
	{
		if(val == SDLK_w)
			keyPressCall("w");
		if(val == SDLK_s)
			keyPressCall("s");
		if(val == SDLK_a)
			keyPressCall("a");
		if(val == SDLK_d)
			keyPressCall("d");
		if(val == SDLK_r)
			keyPressCall("r");
		if(val == SDLK_f)
			keyPressCall("f");
	};
	virtual void keyPressCall(std::string basic_string) = 0;

	virtual glm::vec3 getLookDirection() = 0;

	CameraType type;
private:
	glm::vec3 eye, target, up;
	float theta, phi, radius;

};

#endif

