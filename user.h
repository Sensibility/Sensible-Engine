#ifndef USER
#define USER

#include "gameObject.h"
#include "drawing.h"
#include <typeinfo>
#include "enemy.h"

extern std::vector<std::string> pressedKeys;
extern std::vector<std::shared_ptr<gameObject>> objects;
extern bool moving, blinking, closed;
extern int tileWidth, tileHeight, windowWidth, windowHeight, enemies;
extern float irisX, irisY;
extern void levelComp();
extern void levelLose();

class User : public gameObject{
	public:
		User(float xLoc, float yLoc, float setHeight, float setWidth, int scale){
			this->xLoc = xLoc;
			this->yLoc = yLoc;
			this->width = setWidth;
			this->height = setHeight;
			this->scale = scale;
			objHeight = this->scale * this->height;
			objWidth = this->scale * this->width;
		}

		void traverseX(int amount){
			this->xLoc+= amount;
		}

		void traverseY(int amount){
			this->yLoc+= amount;
		}

		void drawEyes(std::string which){
			glPushMatrix();
				if(!blinking){
					Drawing::drawEllipseEmpty(.6, .6, 360);
					float newX = irisX;
					float newY = irisY;
					newY-= (this->scale * this->yLoc + this->scale * -1);
					if(which == "right"){
						newX-= (this->scale * this->xLoc + this->scale * 1.75);
					}
					else{
						newX-= (this->scale * this->xLoc - this->scale * 1.75);
					}
					if(newY == 0) newY = 1;
					if(newX == 0) newX = 1;
					float newDiv = ((newY/newX));
					float angle = atan(newDiv);
					if(newX < 0){
						newX = -cos(angle) / 5;
						newY = -sin(angle) / 5;
					}
					else{
						newX = cos(angle) / 5;
						newY = sin(angle) / 5;
					}
					glTranslatef(newX, newY, 0);
					Drawing::drawEllipseEmpty(.1, .1, 360);
				}
				else{
					glBegin(GL_LINES);
						glVertex2f(-.6, 0);
						glVertex2f(.6, 0);
					glEnd();
				}
			glPopMatrix();
		}

		void drawMouth(){
			glPushMatrix();
				if(closed){
					glBegin(GL_LINE_STRIP);
						glVertex2f(-1.5, 0);
						glVertex2f(1.5,  0);
					glEnd();
				}
				else{
					glBegin(GL_QUADS);
						glVertex2f(-1.2, .8);
						glVertex2f(1.2, .8);
						glVertex2f(1.2, -.8);
						glVertex2f(-1.2, -.8);
					glEnd();
				}
			glPopMatrix();
		}

		void drawHead(){
			glPushMatrix();
				glScalef(this->scale, this->scale, 0);
				//Helmet top
				Drawing::drawEllipseEmpty(4, 4, 180);

				//Helmet outline
				glBegin(GL_LINE_STRIP);
					glVertex2f(-3, -4);
					glVertex2f(-3, 0);
					glVertex2f(-.5, 0);
					glVertex2f(-.5, -1.5);
					glVertex2f(.5, -1.5);
					glVertex2f(.5, 0);
					glVertex2f(3, 0);
					glVertex2f(3, -4);
				glEnd();

				//Helmet detail
				glBegin(GL_LINE_STRIP);
					glVertex2f(-3.75, 1);
					glVertex2f(3.75, 1);
				glEnd();

				//Helmet curves
				glPushMatrix();
					glTranslatef(-3, 0, 0);
					glRotatef(180, 0, 0, 1);
					Drawing::drawEllipseEmpty(1, 4, 90);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(3, 0, 0);
					glRotatef(-90, 0, 0, 1);
					Drawing::drawEllipseEmpty(4, 1, 90);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-1.75, -1, 0);
					drawEyes("left"); 
				glPopMatrix();
				glPushMatrix();
					glTranslatef(1.75, -1, 0);
					drawEyes("right"); 
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, -3, 0);
					drawMouth();
				glPopMatrix();

				//Chin
				glBegin(GL_LINE_STRIP);
					glVertex2f(-3, -3.25);
					glVertex2f(0, -5);
					glVertex2f(3, -3.25);
				glEnd();
			glPopMatrix();
		}

		void draw(){
			glPushMatrix();
				glTranslatef(this->xLoc + this->width / 2, this->yLoc + this->height / 2 + 2, 0);
				glScalef(5, 5, 0);
		 		drawHead();
			glPopMatrix();
			/*
			glPushMatrix();
				glBegin(GL_QUADS);
					glVertex2f(this->xLoc, this->yLoc);
					glVertex2f(this->xLoc + this->width, this->yLoc);
					glVertex2f(this->xLoc + this->width, this->yLoc + this->height);
					glVertex2f(this->xLoc, this->yLoc + this->height);
				glEnd();
				glColor3f(0, 0, 0);
				glBegin(GL_LINES);
					glVertex2f(this->xLoc, this->yLoc + this->height);
					glVertex2f(this->xLoc, this->yLoc);

					glVertex2f(this->xLoc, this->yLoc);
					glVertex2f(this->xLoc + this->width, this->yLoc);
				glEnd();
			glPopMatrix();
			*/
		}

		bool update(){
			float changes[2] = {0};
			bool xChange = true, yChange = true;
			for(std::vector<std::string>::iterator it = pressedKeys.begin(); it != pressedKeys.end(); ++it){
				if((*it) == "w" || (*it) == "W") changes[1] += 5;
				else if((*it) == "s" || (*it) == "S") changes[1] += -5;
				else if((*it) == "a" || (*it) == "A") changes[0] += -5;
				else if((*it) == "d" || (*it) == "D") changes[0] += 5;
			}

			if(this->xLoc+this->width+changes[0] >= 1050 && this->yLoc+this->height+changes[1] >= 550){
				this->incrementX(changes[0]);
				this->incrementY(changes[1]);
				levelComp();
				return false;
			}
			
			this->incrementX(changes[0]);
			this->incrementY(changes[1]);
			for(int i = 0; i < enemies; i++){
				if(this->checkMove( &(*objects.at(objects.size() - enemies)) )){
					levelLose();
					return  false;
				}
			}
			this->incrementX(-changes[0]);
			this->incrementY(-changes[1]);

			unsigned int i = 0;
			for(std::vector<std::shared_ptr<gameObject>>::iterator obj = objects.begin(); obj != objects.end(); ++obj) {
				++i;
				if(obj->get() != this){
					if(xChange){
						this->incrementX(changes[0]);
						if(this->checkMove(obj->get())) {
							xChange = false;
							this->incrementX(-changes[0]);
						}
					}
					if(yChange){
						this->incrementY(changes[1]);
						if(this->checkMove(obj->get())) yChange = false;
						this->incrementY(-changes[1]);
					}
					if(xChange) this->incrementX(-changes[0]);
					if(!xChange && !yChange) return true;
				}
			}
			if(xChange) this->incrementX(changes[0]);
			if(yChange) this->incrementY(changes[1]);
			return true;
		}

		bool checkMove(gameObject* obj){
			if(collides(this, obj)){
				return true;
			}
			else return false;
		}

		float getX(){
			return xLoc;
		}

		float getY(){
			return yLoc;
		}

		float getHeight(){
			return this->height;
		}

		float getWidth(){
			return this->width;
		}

		void incrementX(float x = 1){
			this->xLoc+= x;
		}

		void incrementY(float y = 1){
			this->yLoc+= y;
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

		const bool COLLIDABLE = true, UPDATEABLE = true;
	private:
		float xLoc, yLoc, height, width, objHeight, objWidth;
		int scale;
};

#endif