#ifndef LIGHTING_H_
#define LIGHTING_H_

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include "OpenGL.h"

class Lights
{
public:
	static void SetAmbientLight(GLfloat* p)
	{
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, p);
		GLErrorCheck(__LINE__, __FILE__);
	}

	static void SetDirectionalLight(GLenum pLight, GLfloat* pPosition, GLfloat* pDiffuse, GLfloat* pSpecular)
	{
		glLightfv(pLight, GL_POSITION, pPosition);
		glLightfv(pLight, GL_DIFFUSE, pDiffuse);
		glLightfv(pLight, GL_SPECULAR, pSpecular);

		glEnable(pLight);

		GLErrorCheck(__LINE__, __FILE__);
	}

	static void MoveSpotLight(GLenum pLight, GLfloat* pPosition, GLfloat* pLookAt=nullptr)
	{
		glLightfv(pLight, GL_POSITION, pPosition);
		if(pLookAt != nullptr)
		{
			glLightfv(pLight, GL_SPOT_DIRECTION, pLookAt);
		}

		GLErrorCheck(__LINE__, __FILE__);
	}

	static void SetSpotLight(GLenum pLight, GLfloat* pPosition, GLfloat* pDiffuse, GLfloat* pSpecular, GLfloat* pLookAt, GLfloat pCuttof, GLfloat pExponent)
	{
		glLightfv(pLight, GL_POSITION, pPosition);
		glLightfv(pLight, GL_DIFFUSE, pDiffuse);
		glLightfv(pLight, GL_SPECULAR, pSpecular);
		glLightf(pLight, GL_SPOT_CUTOFF, pCuttof);
		glLightfv(pLight, GL_SPOT_DIRECTION, pLookAt);
		glLightf(pLight, GL_SPOT_EXPONENT, pExponent);

		glEnable(pLight);

		GLErrorCheck(__LINE__, __FILE__);
	}
private:
};

#endif LIGHTING_H_