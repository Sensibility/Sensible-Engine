#ifndef SDL_H_
#define SDL_H_

#include "SDL2/SDL.h"
#include <cstdio>
#include <string>

inline void SdlErrorCheck(int lineNum, bool clear = false) {
	std::string sdlErr = SDL_GetError();
	if (!sdlErr.empty()) {
		fprintf(stderr, "ERR: %s, %i\n", sdlErr.c_str(), lineNum);
		if (clear)
			SDL_ClearError();
	}
}


#endif SDL_H_
