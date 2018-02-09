#ifndef ENEMY
#define ENEMY

#include "gameObject.h"

extern std::vector<std::shared_ptr<gameObject>> objects;
extern void levelLose();
extern int counter;


class Enemy : public gameObject{
	public:
		Enemy(float xLoc, float yLoc, float setHeight, float setWidth, int scale){
			this->xLoc = xLoc;
			this->yLoc = yLoc;
			this->scale = scale;
			this->width = setWidth;
			this->height = setHeight;
			objHeight = this->scale * this->height;
			objWidth = this->scale * this->width;
			this->collideable = false;
		}

		float getRand() {
		   	return rand() / (float)RAND_MAX;
		}

		bool checkMove(gameObject* obj){
			if(collides(this, obj)){
				return true;
			}
			else return false;
		}

		void incrementX(float x = 1){
			this->xLoc+= x;
		}

		void incrementY(float y = 1){
			this->yLoc+= y;
		}

		void draw(){
		    glPushMatrix();
		    glColor3f( 1, .8, 0);
		    glTranslatef(this->xLoc, this->yLoc + 4, 0);
		    glRotatef(-45, 0, 0, 1);
		    glScalef(7, 7, 0);
		    glBegin(GL_QUADS);
		        //base
		        glVertex2f(.25, 0);
		        glVertex2f(.25, .25);
		        glVertex2f(1.75, .25);
		        glVertex2f(1.75, 0);

		        //sword base?
		        glVertex2f(.5, 1.5);
		        glVertex2f(-.25, 2);
		        glVertex2f(2.25, 2);
		        glVertex2f(1.5, 1.5);
		    glEnd();  

		    //Hilt
		    glBegin(GL_QUAD_STRIP);
		        glColor3f(.3, .3, .3);
		        glVertex2f(.5, .25);
		        glVertex2f(1.5, .25);
		        glColor3f(.5, .5, .5);
		        glVertex2f(.5, 1);
		        glVertex2f(1.5, 1);
		        glColor3f(.3, .3, .3);
		        glVertex2f(.5, 1.5);
		        glVertex2f(1.5, 1.5);
		    glEnd();
		    //Sword
		    glBegin(GL_QUAD_STRIP);
		        glVertex2f(.25, 2);
		        glVertex2f(1.75, 2);
		        glVertex2f(.25, 3);
		        glVertex2f(1.75, 3);
		        glVertex2f(.5, 3.25);
		        glVertex2f(1.5, 3.25);
		        glVertex2f(.5, 4);
		        glVertex2f(1.5, 4);
		        glVertex2f(.25, 4.25);
		        glVertex2f(1.75, 4.25);
		        glVertex2f(.25, 5.5);
		        glVertex2f(1.75, 5.5);
		    glEnd();

		    glBegin(GL_TRIANGLES);
		        glVertex2f(.25, 5.5);
		        glVertex2f(1.75, 5.5);
		        glVertex2f(1, 6.5);
		    glEnd();

		    //Give the sword depth
		    glColor3f(0, 0, 0);
		    glBegin(GL_LINES);
		        glVertex2f(1, 6.5);
		        glVertex2f(1, 2);
		    glEnd();

		    glPopMatrix();
		}
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
			glPopMatrix();*/
		//}

		bool update(){
			float changes[2] = {0};
			bool xChange = true, yChange = true;
			bool changed = false;
			float dir = getRand();
			while(!changed){
				dir = getRand();
				if(this->dir == -1){
					if(dir < .25){
						this->dir = 0;
						changes[0] = -10;
					}
					else if(dir < .5){
						this->dir = 1;
						changes[1] = 10;
					}
					else if(dir < .75){
						this->dir = 2;
						changes[0] = 10;
					}
					else if(dir < 1){
						this->dir = 3;
						changes[1] = -10;
					}
				}
				else if (this->dir == 0) changes[0] = -10;
				else if (this->dir == 1) changes[1] = 10;
				else if (this->dir == 2) changes[0] = 10;
				else if (this->dir == 3) changes[1] = -10;
				int i = -1;
				for(std::vector<std::shared_ptr<gameObject>>::iterator obj = objects.begin(); obj != objects.end(); ++obj) {
					++i;
					if(obj->get() != this){
						if(i == 0){
							this->incrementX(changes[0]);
							this->incrementY(changes[0]);
							if(this->checkMove(obj->get())){
								this->incrementX(-changes[0]);
								this->incrementY(-changes[0]);
								levelLose();
								return false;
							}
							else{
								this->incrementX(-changes[0]);
								this->incrementY(-changes[0]);
							}
						}
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
						if(!xChange && !yChange) break;
					}
				}
				if(xChange || yChange) changed = true;
				if(xChange) this->incrementX(changes[0]);
				if(yChange) this->incrementY(changes[1]);
				if((int)this->xLoc % 50 == 5 && (int)this->yLoc % 50 == 5) this->dir = -1;
			}
			return true;

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

		const bool COLLIDABLE = true, UPDATEABLE = true;
		int dir = -1;
	private:
		float xLoc, yLoc, height, width, objHeight, objWidth;
		int scale;
		bool collideable;
};


#endif