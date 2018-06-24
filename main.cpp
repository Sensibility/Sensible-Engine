

#include "include/Windows/RenderWindow.h"
#include "include/Scene/Bench.h"


int main(int argc, char *argv[]) {
	RenderWindow r = RenderWindow();
	r.RegisterScene(new Bench());
	r.Start();

	return 0;
}
