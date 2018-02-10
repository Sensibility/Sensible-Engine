#ifndef CAMERA
#define CAMERA

#include <string>
#include <vector>
#include <math.h>
#include <iostream>

#include "vector.h"
#include "point.h"

#define CAMERA_FREE            "free"
#define CAMERA_ARC                "arc"
#define CAMERA_FIRST_PERSON    "first person"

class Camera {
public:
	Camera() { }

	Camera(float x, float y, float z, float dirX, float dirY, float dirZ, float upX, float upY, float upZ, float theta,
		   float phi, float radius, std::string type, std::string focus) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->dirX = dirX;
		this->dirY = dirY;
		this->dirZ = dirZ;
		this->upX = upX;
		this->upY = upY;
		this->upZ = upZ;
		this->theta = theta;
		this->phi = phi;
		this->radius = radius;
		this->type = type;
		this->focus = focus;
	}

	Camera(std::string type, std::string focus, std::vector<float> foc) {
		this->type = type;
		this->focus = focus;
		if (type == CAMERA_FREE) this->initFree( foc );
		else if (type == CAMERA_ARC) this->initArc( foc );
		else if (type == CAMERA_FIRST_PERSON) this->initFP( foc );
	}

	void initArc(std::vector<float> focus);

	void initFree(std::vector<float> focus);

	void initFP(std::vector<float> focus);

	std::string getType();

	float getRadius();

	float getX();

	float getY();

	float getZ();

	float getDirX();

	float getDirY();

	float getDirZ();

	float getUpX();

	float getUpY();

	float getUpZ();

	float getTheta();

	float getPhi();

	std::string getFocus();

	std::vector<float> setLookAt(std::vector<float> focus);

	void setType(std::string type, std::vector<float> focus);

	void setRadius(float radius);

	void setXYZ(float x, float y, float z);

	void setPosition(Point newPosition);

	void setDirXYZ(float dirX, float dirY, float dirZ);

	void setDirection(Vector newDirection);

	void setUpXYZ(float upX, float upY, float upZ);

	void setUp(Vector newUp);

	void setTheta(float theta);

	void setPhi(float phi);

	void setFocus(std::string focus);

	void incrementRadius(float r);

	void incrementXYZ(float x, float y, float z);

	void incrementDirXYZ(float dirX, float dirY, float dirZ);

	void incrementTheta(float theta);

	void incrementPhi(float phi);

	void handleMouse(int leftMouseButton, bool ctrlClick, int x, int y, int mouseX, int mouseY);

	void updateCamera(std::vector<float> focus);


	void incrementDirXYZ(Vector pVec);

	void incrementXYZ(Vector pVec);

private:
	float x, y, z, dirX, dirY, dirZ, upX, upY, upZ, theta, phi, radius;
	std::string type, focus;

};

#endif

