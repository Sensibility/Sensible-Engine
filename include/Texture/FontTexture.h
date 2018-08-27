#ifndef _FONTS_TEXTURE_H_
#define _FONTS_TEXTURE_H_
#include "SDLTexture.h"
#include <string>
#include "../Renderer/OpenGL.h"
#include "glm/glm.hpp"


class FontTexture : public Texture
{
public:
	FontTexture(GLuint tex, char pChar, glm::vec2 size, glm::vec2 bearing, GLuint margin) : Texture(tex), char_(pChar), size_(size), bearing_(bearing), margin_(margin)
	{ } 

	glm::vec2 size_;
	glm::vec2 bearing_;
	GLuint margin_;
	char char_;
protected:
};

#endif _FONTS_TEXTURE_H_