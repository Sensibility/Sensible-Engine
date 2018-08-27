#ifndef TEXTUERS_H_
#define TEXTUERS_H_
#include "gl/glew.h"

class Texture
{
public:
	Texture() {}
	Texture(GLuint pTex) { this->tex_ = pTex;}
	~Texture() { } 

	GLuint _Handle() { return this->tex_; }
protected:
	GLuint tex_, normTex_;
};

#endif TEXTUERS_H_