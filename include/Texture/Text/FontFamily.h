#ifndef _FONT_FAMILY_H_
#define _FONT_FAMILY_H_

#ifdef _win32
#include<windows.h>
#endif

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <cstdio>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H
#include "../../RenderObject/Object.h"
#include "../../Shaders/ShaderProvider.h"

std::string font_v = SEString::Join(std::vector<std::string>{
	"#version 330 core", 
	"layout(location = 0) in vec4 vPos_M;",
	"out vec2 UV;",
	"uniform mat4 MVP;",
	"void main() {",
		"gl_Position = MVP * vec4(vPos_M.xy, 0.0, 1.0);",
		"UV = vPos_M.zw;",
"}"}, '\n');
std::string fragment_v = SEString::Join(std::vector<std::string>{
	"#version 330 core", 
	"in vec2 UV;",
	"out vec4 color;",
	"uniform sampler2D text;",
	"uniform vec3 textColor;",
	"void main() {",
		"vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, UV).r);",
		"color = vec4(textColor, 1.0) * sampled;",
"}"}, '\n');

class FontFamily : public Object
{
public:
	GLuint p; GLuint hndl;

	FontFamily(FT_Library* lib, const char* pFile, int pFontSize) : Object(), lib_(lib)
	{
		auto shader = (ShaderProvider*)GetProvider<ShaderProvider>();
		shader->Register("Font", ShaderBuilder::CreateShaderStr(font_v, fragment_v));
		shader_ = shader->Get("Font");
		hndl = shader_->GetHandle("textColor");
		p = shader_->GetHandle("MVP");
		shader_->Validate();

		sourceFile_ = pFile;
		if (FT_New_Face(*lib_, pFile, 0, &face_))
			fprintf(stderr, "Could not read in %s\n", pFile);
		FT_Set_Pixel_Sizes(face_, 0, pFontSize);

		LoadCharset();
	}
	~FontFamily()
	{
		FT_Done_Face(face_);
	} 

	struct StringTextureMetaData {
		int Height, Width;
	};

	StringTextureMetaData GetMetaData(std::string pText, glm::vec2 pOffset, int pScale)
	{
		auto md = StringTextureMetaData();
		md.Height = md.Width = 0;
		for(auto& c: pText)
		{
			if (!chars_.Find(c))
				continue;
			auto tex = chars_[c];

			auto xpos = pOffset.x + tex->bearing_.x * pScale;
			auto ypos = pOffset.y - (tex->size_.y - tex->bearing_.y) * pScale;

			auto w = tex->size_.x * pScale;
			auto h = tex->size_.y * pScale;
			md.Width += w + ((tex->margin_ >> 6) * pScale);
			if (h > md.Height)
				md.Height = h;
		}
		printf("H:%i, W:%i\n", md.Height, md.Width);
		return md;
	}

	void Render(std::string pText, glm::mat4 pMVP, glm::vec2 pOffset, glm::vec3 pColor, int pScale)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		shader_->Activate();
		glBindVertexArray(vertexArray_);
		glActiveTexture(GL_TEXTURE0);

		glUniform3f(hndl, pColor.x, pColor.y, pColor.z);
		glUniformMatrix4fv(p, 1, GL_FALSE, &pMVP[0][0]);

		for(auto& c: pText)
		{
			if(!chars_.Find(c))
			{
				fprintf(stderr, "Couldnt find %c\n", c);
				continue;
			}
			auto tex = chars_[c];
			auto xpos = pOffset.x + tex->bearing_.x * pScale;
			auto ypos = pOffset.y - (tex->size_.y - tex->bearing_.y) * pScale;

			auto w = tex->size_.x * pScale;
			auto h = tex->size_.y * pScale;

			GLfloat v[6][4] = {
				{xpos, ypos + h, 0.0, 0.0},
				{xpos, ypos, 0.0, 1.0},
				{xpos + w, ypos, 1.0, 1.0},
				{xpos, ypos + h, 0.0, 0.0},
				{xpos + w,ypos,1.0,1.0},
				{xpos + w,ypos + h,1.0,0.0}
			};

			glBindTexture(GL_TEXTURE_2D, tex->_Handle());

			glBindBuffer(GL_ARRAY_BUFFER, vBuff_);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(v), v);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			pOffset.x += (tex->margin_ >> 6) * pScale;
		}

		glBindVertexArray(0);
		shader_->Deactivate();
	}
	void Render() override {};

	void LoadCharset(int pLow = 0, int pHigh = 128)
	{
		for(auto c = pLow; c < pHigh; ++c)
		{
			if(FT_Load_Char(face_, c, FT_LOAD_RENDER))
			{
				fprintf(stderr, "Could not load glyph %c\n", c);
				continue;
			}

			if (face_->glyph->bitmap.rows == 0 || face_->glyph->bitmap.width == 0
				|| chars_.Find(c))
				continue;

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			//GL_RED because we use a single byte since the font is in 8-bit greyscale
			auto tex = SEGL::GenerateTexture2D( face_->glyph->bitmap.rows,
				face_->glyph->bitmap.width, face_->glyph->bitmap.buffer,
				GL_RED, GL_RED, GL_LINEAR, GL_LINEAR,
				GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

			auto texture = new FontTexture(tex, (char)c,
				glm::ivec2(face_->glyph->bitmap.width, face_->glyph->bitmap.rows),
				glm::ivec2(face_->glyph->bitmap_left, face_->glyph->bitmap_top),
				face_->glyph->advance.x);

			chars_.Insert(c, texture);
		}
	}

	void InitBuffers() override
	{
		glCreateVertexArrays(1, &vertexArray_);
		glCreateBuffers(1, &vBuff_);
		glBindVertexArray(vertexArray_);
		glBindBuffer(GL_ARRAY_BUFFER, vBuff_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		SEGL::ErrorCheck(__LINE__, __FILE__);
	}
protected:
	std::string sourceFile_;
	SEMap<char, FontTexture*> chars_;
	FT_Face face_;
	FT_Library *lib_;
};


#endif _FONT_FAMILY_H_