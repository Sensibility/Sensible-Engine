#ifndef templateObject
#define templateObject

#include "gameObject.h"


/**********************
	THIS FILE IS USED AS A TEMPLATE, IT SHOULD NEVER BE USED/INCLUDED
**********************/


class templateObject : public gameObject{
	public:
		templateObject(float xLoc, float yLoc, float setHeight, float setWidth, int scale){
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
			//Do stuff
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

	private:
		float xLoc, yLoc, height, width, objHeight, objWidth;
		int scale;
		bool collideable;
};


#endif