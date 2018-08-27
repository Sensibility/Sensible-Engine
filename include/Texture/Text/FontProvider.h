#ifndef _FONT_PROVIDER_H_
#define _FONT_PROVIDER_H_

#include "../../BaseProvider.h"
#include "FontFamily.h"
#include "../../SEMap.h"

#include "ft2build.h"
#include FT_FREETYPE_H

class FontProvider: public BaseProvider
{
public:
	FontProvider() : BaseProvider()
	{

		if (FT_Init_FreeType(&lib_))
			fprintf(stderr, "Could not init freetype\n");
		fonts_ = SEMap< std::string, FontFamily* > ();
	}

	FT_Library lib_;

	~FontProvider()
	{
		FT_Done_FreeType(lib_);
	}

	FontFamily* OpenFont(std::string pFile, std::string pKey = "")
	{
		if (pKey == "")
			pKey = pFile;
		if(!fonts_.Find(pKey))
		{
			auto family = new FontFamily(&lib_, pFile.c_str(), 48);
			fonts_.Insert(pKey, family);
		}
		return fonts_[pKey];
	}

	FontFamily* GetFont(const std::string& pKey)
	{
		if (fonts_.Find(pKey))
			return fonts_[pKey];
	}
	bool IsInit() override { return true; };

	std::string GetKey() { return FontProvider::GetKeyStatic(); };
	static std::string GetKeyStatic() { return "Font"; }
private:
	TTF_Font * ReadInFont(const char* pFile, int pTextSize = 24) 
	{
		if(IsInit()) {
			auto font = TTF_OpenFont(pFile, 24);
			std::string err = TTF_GetError();
			if(!err.empty())
				fprintf(stderr, "ERR: %s\n", err.c_str());
			if (font == nullptr)
				fprintf(stderr, "ERR: Could not open font at %s\n", pFile);
			return font;
		}
		return nullptr;
	}

	SEMap<std::string, FontFamily*> fonts_;
};

#endif _FONT_PROVIDER_H_