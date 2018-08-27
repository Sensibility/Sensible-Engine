#ifndef _TEXTURE_PROVIDER_H_
#define _TEXTURE_PROVIDER_H_

#include "SDL2/SDL.h"
#include "../BaseProvider.h"
#include "Textures.h"
#include "FontTexture.h"
#include "FreeImage.h"

class TextureProvider : public BaseProvider
{
public:
	TextureProvider() {  }
	~TextureProvider() {  }
	Texture* FromSurface(SDL_Surface *pSurface)
	{
		GLenum format;
		switch(pSurface->format->BytesPerPixel)
		{
		case 4:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				format = GL_BGRA;
			else
				format = GL_RGBA;
			break;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				format = GL_BGR;
			else
				format = GL_RGB;
			break;
		default:
			format = GL_RGB;
			break;
		}
		auto tex = SEGL::GenerateTexture2D(pSurface->h, pSurface->w, pSurface->pixels, format, format);
		return new SDLTexture(pSurface, tex);
	}

	bool IsInit() override { return true; }
	std::string GetKey() { return TextureProvider::GetKeyStatic(); };
	static std::string GetKeyStatic() { return "Texture"; }
private:
};
#endif _TEXTURE_PROVIDER_H_
