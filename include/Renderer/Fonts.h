#ifndef _FONTS_H_
#define _FONTS_H_
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL.h"
#include <cstdio>

class TrueTypeFont
{
public:
	TrueTypeFont() {}
	TrueTypeFont(const char* pFile) { Read(pFile); }
	~TrueTypeFont()
	{
		//if(font_ != nullptr)
			//TTF_CloseFont(font_);
	}

	void Read(const char* pFile)
	{
		font_ = TTF_OpenFont(pFile, 72);
		if (font_ == nullptr)
			fprintf(stderr, "Unable to load font %s\n", pFile);
		std::string sdl = TTF_GetError();
		if (!sdl.empty())
			fprintf(stderr, "ERR: %s\n", sdl.c_str());
	}

	GLuint ToTexture(SDL_Surface* pSurface)
	{
		if (!pSurface)
			fprintf(stderr, "Unable to create texture from font\n");
		this->surface_ = pSurface;
		return ToTexture();
	};
	GLuint ToTexture()
	{
		if (!this->surface_)
			fprintf(stderr, "Texture not yet created!\n");
		this->tex_ = new Texture(this->surface_, SurfaceToTexture(this->surface_));
		return this->tex_->_Handle();
	}
	int Height() const
	{
		if(surface_ != nullptr)
			return this->surface_->h;
		return 0;
	}

	int Width() const
	{
		if(surface_ != nullptr)
			return this->surface_->w;
		return 0;
	}

	void* Pixels() const
	{
		return this->surface_->pixels;
	}
	SDL_Surface* RenderGlyph_SDL_Sur(Uint16 ch, SDL_Color pColor) { return TTF_RenderGlyph_Blended(font_, ch, pColor); }
	SDL_Surface* RenderTextSolid_SDL_Sur(const char *text, SDL_Color fg) { return TTF_RenderText_Blended(font_, text, fg); };
	SDL_Surface* RenderUTF8Solid_SDL_Sur(const char *text, SDL_Color fg) { return TTF_RenderUTF8_Blended(font_, text, fg); };
	SDL_Surface* RenderUNICODESolid_SDL_Sur(const Uint16 *text, SDL_Color fg) { return TTF_RenderUNICODE_Blended(font_, text, fg); };
	GLuint RenderGlyph_GL_Tex(Uint16 ch, SDL_Color pColor) { return ToTexture(TTF_RenderGlyph_Blended(font_, ch, pColor)); }
	GLuint RenderTextSolid_GL_Tex(const char *text, SDL_Color fg) { return ToTexture(TTF_RenderText_Blended(font_, text, fg)); };
	GLuint RenderUTF8Solid_GL_Tex(const char *text, SDL_Color fg) { return ToTexture(TTF_RenderUTF8_Blended(font_, text, fg)); };
	GLuint RenderUNICODESolid_GL_Tex(const Uint16 *text, SDL_Color fg) { return ToTexture(TTF_RenderUNICODE_Blended(font_, text, fg)); };

private:
	TTF_Font * font_;
	SDL_Surface * surface_;
	Texture* tex_;
};

static class Fonts
{
public:
	~Fonts()
	{
		TTF_Quit();
	}

	static void SetUp()
	{
		fonts_ = SEMap < std::string, TrueTypeFont* > ();
		color_ = SDL_Color();
		color_.r = 255;
		color_.g = 255;
		color_.b = 255;
		color_.a = 255;
		if(TTF_Init() < 0)
			fprintf(stderr, "Unable to init SDL TTF Fonts");
	}

	static GLuint RenderToGLTexture(string pKey, string pText)
	{
		return fonts_[pKey]->ToTexture(RenderTOSDLSurface(pKey, pText));
	}

	static SDL_Surface * RenderTOSDLSurface(string pKey, string pText)
	{
		if (fonts_.Find(pKey))
		{
			return fonts_[pKey]->RenderUTF8Solid_SDL_Sur(pText.c_str(), color_);
		}
		fprintf(stderr, "Cannot find font\n");
	}

	static TrueTypeFont* OpenFont(const char* pFile, std::string pKey)
	{
		auto font = new TrueTypeFont(pFile);
		fonts_.Insert(pKey, font);
		return font;
	}

	static bool IsInit() { return TTF_WasInit() == 1; }
	static string* Diagnostics()
	{
		linked_ = *TTF_Linked_Version();
		SDL_TTF_VERSION(&compiled_);

		auto str = new string[2];
		str[0] = "TTF Version";
		char buff[100];
		snprintf(buff, sizeof(buff), "%i.%i.%i", compiled_.major, compiled_.minor, compiled_.patch);
		str[1] = buff;
		return str;
	}
private:
	static SDL_version linked_;
	static SDL_version compiled_;
	static SDL_Color color_;
	static SEMap<std::string, TrueTypeFont*> fonts_;

};
SDL_version Fonts::linked_;
SDL_version Fonts::compiled_;
SDL_Color Fonts::color_;
SEMap<std::string, TrueTypeFont*> Fonts::fonts_;

#endif _FONTS_H_