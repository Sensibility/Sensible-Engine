#ifndef _SHADER_PROVIDER_H_
#define _SHADER_PROVIDER_H_
#include "../BaseProvider.h"
#include "../Renderer/Shader.h"
#include "../SEMap.h"

class ShaderProvider : public BaseProvider
{
public:
	ShaderProvider() : BaseProvider()
	{
		shaders_.Insert("lighting", ShaderBuilder::CreateShaderFolder("assets\\shaders\\lighting"));
		//shaders_.Insert("multiLight", ShaderBuilder::CreateShaderFolder("assets\\shaders\\multiLight"));
	}
	void Register(std::string pKey, Shader* pShader)
	{
		shaders_.Insert(pKey, pShader);
	}
	Shader* Get(std::string pKey)
	{
		if (shaders_.Find(pKey))
			return shaders_[pKey];
	}
	bool IsInit() override { return true; }
	std::string GetKey() override { return GetKeyStatic(); };
	static std::string GetKeyStatic() { return "Shader"; }
private:
	SEMap<std::string, Shader*> shaders_;
};

#endif _SHADER_PROVIDER_H_