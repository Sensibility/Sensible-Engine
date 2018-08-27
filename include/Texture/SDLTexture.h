#ifndef _SDL_TEXTURE_H_
#define _SDL_TEXTURE_H_
#include "gl/glew.h"
#include "Textures.h"
#include "SDL2/SDL.h"

class SDLTexture : public Texture
{
public:
	~SDLTexture()
	{
		if (sur_ != nullptr)
			SDL_FreeSurface(sur_);
	}

	SDLTexture(SDL_Surface* pSur) { sur_ = pSur;}
	SDLTexture(SDL_Surface* pSur, GLuint pTex) { sur_ = pSur;  tex_ = pTex;}

	float w() { return sur_->w; }
	float h() { return sur_->h; }
	SDL_Surface* _Surface() { return sur_; }

	float* Normalized(int pMax)
	{
		float* points = (float*)malloc(sizeof(float) * 2);
		if(pMax == 0)
		{
			points[0] = sur_->w;
			points[1] = sur_->h;
		}
		else
		{
			if(sur_->w > sur_->h)
			{
				points[0] = pMax;
				points[1] = pMax * sur_->h / sur_->w;
			}
			else
			{
				points[0] = pMax * sur_->w / sur_->h;
				points[1] = pMax;
				
			}
		}
		return points;
	}
protected:
	SDL_Surface* sur_;
};

#endif _SDL_TEXTURE_H_