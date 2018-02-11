//
// Created by steve on 2/10/18.
//

#ifndef MAIN_FPCAMERA_H
#define MAIN_FPCAMERA_H


#include "baseCamera.h"

class FpCamera : public BaseCamera {
public:
	FpCamera();
	explicit FpCamera(Point pTarget);
	virtual void handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY);

	virtual void updateCamera(std::vector<float> focus);

	virtual void lookAt(vector<float> vector1);
	virtual void keyPressCall(std::string val);
};


#endif //MAIN_FPCAMERA_H
