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
	FreeCamera(Point pTarget) : TankCamera(pTarget)
	{
		this->type = CameraType::Free;
	}

	void keyPressCall(std::string val) override
	{
		auto transform = Point();
		if (val == "w") transform = Point(1, 1, 1);
		else if (val == "s") transform = Point(-1, -1, -1);
		this->incrementXYZ(getLookDirection() * transform);
	};
};

#endif