#ifndef _FFP_TEXTURE_H_
#define _FFP_TEXTURE_H_

#include "../SDLTexture.h"

class FFPTexture : SDLTexture
{
public:
	void Render(int pSize = 0)
	{
		glPushMatrix();
			//glEnable(GL_TEXTURE_2D); glEnable(GL_BLEND);
			glColor4f(1, 1, 1, 1);
			glBindTexture(GL_TEXTURE_2D, tex_);
			glBegin(GL_QUADS);
				auto wh = Normalized(pSize);
				glTexCoord2i(0, 1); 
					glVertex2f(-wh[0]/2, wh[1]/2);
				glTexCoord2i(1, 1);
					glVertex2f(wh[0] / 2, wh[1]/2);
				glTexCoord2i(1, 0); 
					glVertex2f(wh[0] / 2, -wh[1]/2);
				glTexCoord2i(0, 0);
					glVertex2f(-wh[0] / 2, -wh[1]/2);
				free(wh);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
private:
};

#endif _FFP_TEXTURE_H_
