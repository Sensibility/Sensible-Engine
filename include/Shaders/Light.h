#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "../BaseProvider.h"
class LightProvider;

class Light
{
	friend LightProvider;
public:
	Light() : enabled_(true), local_(true), spot_(false), 
	sCosCutOff_(0), sExponent_(0), 
	attenuation_(1), linearAttenuation_(0), quadraticAttenuation_(0)
	{
		ambient_ = diffuse_ = specular_ = color_ = position_ = halfVec_ = coneDirection_ = glm::vec3(1);
	}
private:
	bool enabled_, local_, spot_;
	glm::vec3 ambient_, diffuse_, specular_, color_, position_, halfVec_, coneDirection_;
	float sCosCutOff_, sExponent_, attenuation_, linearAttenuation_, quadraticAttenuation_;
};

class LightProvider : public BaseProvider
{
public:
	Light* SpotLight()
	{
		return new Light();
	}

	Light* PointLight()
	{
		return new Light();
	}

	Light* DirectionalLight()
	{
		return new Light();
	}

	bool IsInit() override { return true; };
	std::string GetKey() override { return GetKeyStatic(); };
	static std::string GetKeyStatic() { return "Light"; }
};

#endif _LIGHT_H_