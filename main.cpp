

#include "include/Windows/RenderWindow.h"
#include "include/Scene/Bench.h"
#include "include/Scene/Lighting.h"
#include "include/Scene/Multisample.h"
#include "include/Scene/FontsScene.h"
#include "include/Scene/Texture2D.h"
#include <vector>
#include "include/XMLReader.h"
#include "include/Scene/ShaderScene.h"

template<class T> BaseScene* CreateScene()
{
	return new T();
}
typedef BaseScene* (*SceneHandle)();
int changeScene(vector<std::string>& pTokens, void* pContext)
{
	auto windows = SEMap<string, SceneHandle>();
	windows.Insert("Bench", &CreateScene<Bench>);
	windows.Insert("Lighting", &CreateScene<Lighting>);
	windows.Insert("Fonts", &CreateScene<FontsScene>);
	windows.Insert("Multisample", &CreateScene<Multisample>);
	windows.Insert("Texture2D", &CreateScene<Texture2D>);
	windows.Insert("ShaderScene", &CreateScene<ShaderScene>);

	RenderWindow* r = static_cast<RenderWindow*>(pContext);
	if (pTokens.size() < 2)
		return 0;
	r = new RenderWindow();
	if (windows.Find(pTokens.at(1)))
	{
		r->RegisterScene(windows[pTokens.at(1)]());
	}
	else
	{
		fprintf(stderr, "You borked it dude\n");
	}
	r->Start();
	return 0;
}

int main(int argc, char *argv[]) {
	Fonts::SetUp();
	RenderWindow r;
	Console::Register("Load", Command(&changeScene, &r));

	auto obj = new XMLReader("assets\\untitled.dae");
	r.RegisterScene(new ShaderScene());
	r.Start();

	IMG_Quit();
	SDL_Quit();
	return 0;
}
