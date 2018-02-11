//
// Created by steve on 2/10/18.
//

#ifndef MAIN_ARCCAMERA_H
#define MAIN_ARCCAMERA_H


#include "baseCamera.h"

class ArcCamera : public BaseCamera {
public:
	ArcCamera();
	explicit ArcCamera(Point pTarget);
	virtual void handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY);

	virtual void updateCamera(std::vector<float> focus);

	virtual void lookAt(vector<float> vector1);
	virtual void keyPressCall(std::string val);
};


#endif //MAIN_ARCCAMERA_H
