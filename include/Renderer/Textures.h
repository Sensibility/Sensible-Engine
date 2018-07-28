#ifndef TEXTUERS_H_
#define TEXTUERS_H_
#include "../SEMap.h"
#include <string>
#include "../Scene/BaseScene.h"

class Texture
{
public:
	Texture(SDL_Surface* pSur) { sur_ = pSur; }
	Texture(SDL_Surface* pSur, GLuint pTex) : Texture(pSur) { tex_ = pTex; }

	~Texture() {
		if (sur_ != nullptr)
			SDL_FreeSurface(sur_);
	}

	void Render()
	{
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			glColor4f(1, 1, 1, 1);
			glBindTexture(GL_TEXTURE_2D, tex_);
			glBegin(GL_QUADS);
				float* wh = Normalized(100);
				glTexCoord2i(1, 1);
					glVertex3f(0, 0, 0);
				glTexCoord2i(0, 1); 
					glVertex3f(0, 0, wh[0]);
				glTexCoord2i(0, 0);
					glVertex3f(0, wh[1], wh[0]);
				glTexCoord2i(1, 0); 
					glVertex3f(0, wh[1], 0);
				free(wh);
			glEnd();
			glEnable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	float* Normalized(int pMax)
	{
		float* points = (float*)malloc(sizeof(float) * 2);
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
		return points;
	}
	GLuint _Handle() { return tex_; }
private:
	GLuint tex_;
	SDL_Surface* sur_;
};

static class TextureProvider
{
public:


private:
	static SEMap<std::string, Texture> *textures_;
};

#endif TEXTUERS_H_