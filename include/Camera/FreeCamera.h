#ifndef _FREE_CAMERA_H_
#define _FREE_CAMERA_H_
#include "TankCamera.h"
#include <string>


class FreeCamera : public TankCamera
{
public:
	FreeCamera() : TankCamera()
	{
		this->type = CameraType::Free;
	}
	FreeCamera(glm::vec3 pTarget) : TankCamera(pTarget)
	{
		this->type = CameraType::Free;
	}

	void keyPressCall(std::string val) override
	{
		auto transform = glm::vec3(0);
		if (val == "w") transform = glm::vec3(1, 1, 1);
		else if (val == "s") transform = glm::vec3(-1, -1, -1);
		this->incrementXYZ(getLookDirection() * transform);
	};
};

#endif