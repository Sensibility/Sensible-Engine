

#include "include/Windows/RenderWindow.h"
#include "include/Scene/Bench.h"
#include "include/Scene/Lighting.h"

RenderWindow r;

int changeScene(std::vector<std::string>& pTokens)
{
	if (pTokens.size() < 2)
		return 0;
	if(pTokens.at(1) == "Bench")
	{
		r = RenderWindow();
		r.RegisterScene(new Bench());
		r.Start();
	}
	else if(pTokens.at(1) == "Lighting")
	{
		r = RenderWindow();
		r.RegisterScene(new Lighting());
		r.Start();
	}
	return 0;
}

int main(int argc, char *argv[]) {
	Console::Register("Load", &changeScene);

	r = RenderWindow();
	r.RegisterScene(new Bench());
	//r.RegisterScene(new Lighting());
	r.Start();

	return 0;
}
