#ifndef DOOR
#define DOOR

#include "gameObject.h"

class Door : public gameObject{
	public:
		Door(float xLoc, float yLoc, float setHeight, float setWidth, int scale){
			this->xLoc = xLoc;
			this->yLoc = yLoc;
			this->scale = scale;
			this->width = setWidth;
			this->height = setHeight;
			objHeight = this->scale * this->height;
			objWidth = this->scale * this->width;
			this->collideable = false;
		}

		void draw(){
			glPushMatrix();
				glColor3f(.58, .31, .14);
				glBegin(GL_QUADS);
					glVertex2f(this->xLoc, this->yLoc + 30);
					glVertex2f(this->xLoc, this->yLoc);
					glVertex2f(this->xLoc + 50, this->yLoc);
					glVertex2f(this->xLoc + 50, this->yLoc + 30);

					glVertex2f(this->xLoc - 1, this->yLoc + 30);
					glVertex2f(this->xLoc + 25, this->yLoc + 30);
					glVertex2f(this->xLoc + 51, this->yLoc + 30);
					glVertex2f(this->xLoc + 25, this->yLoc + 51);
				glEnd();
				glPushMatrix();
					glTranslatef(this->xLoc + 25, this->yLoc + 30, 0);
					Drawing::drawEllipseFull(25, 20, 90);
					glRotatef(90, 0, 0, 1);
					Drawing::drawEllipseFull(20, 25, 90);
				glPopMatrix();
				glColor3f(0, 0, 0);
				glPushMatrix();
					glTranslatef(this->xLoc + 20, this->yLoc + 20, 0);
					Drawing::drawEllipseEmpty(3, 3, 360);
					glTranslatef(9, 0, 0);
					Drawing::drawEllipseEmpty(3, 3, 360);
				glPopMatrix();
				glBegin(GL_LINES);
					glVertex2f(this->xLoc + 25, this->yLoc + 50);
					glVertex2f(this->xLoc + 25, this->yLoc);
				glEnd();
			glPopMatrix();
		}	

		float getX(){
			return xLoc;
		}

		float getY(){
			return yLoc;
		}

		float getHeight(){
			return this->objHeight;
		}

		float getWidth(){
			return this->objWidth;
		}

		void setHeight(float height){
			this->height = height;
			this->objHeight = height * scale;
		}

		void setWidth(float width){
			this->width = width;
			this->objWidth = width * scale;
		}

		void setX(float x){
			this->xLoc = x;
		}

		void setY(float y){
			this->yLoc = y;
		}

		const bool COLLIDABLE = false, UPDATEABLE = false;
	private:
		float xLoc, yLoc, height, width, objHeight, objWidth;
		int scale;
		bool collideable;
};


#endif