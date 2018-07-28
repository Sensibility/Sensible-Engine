#ifndef SDL_H_
#define SDL_H_

#include "SDL2/SDL.h"
#include <cstdio>
#include <string>
#include "Textures.h"
#include "SDL2/SDL_image.h"

inline void SdlErrorCheck(int lineNum, bool clear = false) {
	std::string sdlErr = SDL_GetError();
	if (!sdlErr.empty()) {
		fprintf(stderr, "ERR: %s, %i\n", sdlErr.c_str(), lineNum);
		if (clear)
			SDL_ClearError();
	}
}

inline GLuint SurfaceToTexture(SDL_Surface* pSurface)
{
	GLuint tex = GenerateTexture2D(pSurface->h, pSurface->w, pSurface->pixels);
	return tex;
}

inline Texture* LoadTextureTGA(string pFile)
{
	SDL_Surface* sur;
	SDL_RWops *rwop;
	rwop = SDL_RWFromFile(pFile.c_str(), "rb");
	sur = IMG_LoadTGA_RW(rwop);
	auto tex = GenerateTexture2D(sur->h, sur->w, sur->pixels);
	return new Texture(sur, tex);
}

inline Texture* LoadTexturePNG(string pFile, GLenum pColor = GL_RGBA)
{
	auto img = IMG_Load(pFile.c_str());
	return new Texture(img, GenerateTexture2D(img->h, img->w, img->pixels, pColor));
}


#endif SDL_H_
