#include <iostream>
#include <string>

#ifdef _WIN32
	#include<windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>


int main()
{
	std::string ans = "";
	while(ans != "q")
	{
		std::cout << "Shader path/base name? ";
		getline(std::cin, ans);
		std::cout << ans << std::endl;
	}
	return 0;
}