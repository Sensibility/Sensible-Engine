#ifndef _SDL_IMAGE_READER_H_
#define _SDL_IMAGE_READER_H_
#include "ImageReader.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "../../SDLTexture.h"
#include "../../../Renderer/SDL.h"

class SDLImageReader : public ImageReader
{
public:	
	SDLImageReader() {
		if (IMG_Init(IMG_INIT_PNG) < 0)
			fprintf(stderr, "Failed to init SDL Images\n");
	}
	~SDLImageReader()
	{
		IMG_Quit();
	}
	Texture* LoadPNG(const char* pFile) override
	{
		auto img = IMG_Load(pFile);
		return new SDLTexture(img, SEGL::GenerateTexture2D(img->h, img->w, img->pixels));
	}
	Texture* LoadTGA(const char* pFile) override
	{
		SDL_Surface* sur;
		SDL_RWops *rwop;
		rwop = SDL_RWFromFile(pFile, "rb");
		sur = IMG_LoadTGA_RW(rwop);
		auto tex = SEGL::GenerateTexture2D(sur->h, sur->w, sur->pixels, 
			GL_RGB, GL_RGB, GL_LINEAR, GL_LINEAR);
		return new SDLTexture(sur, tex);
	}

	bool IsInit() override { return true; }
	std::string Str() override
	{
		return "SDL";
	}
private:
};
#endif _SDL_IMAGE_READER_H_
