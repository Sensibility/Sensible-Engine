#ifndef WALLCELL
#define WALLCELL

class WallCell : public gameObject{
	public:
		WallCell(float xLoc, float yLoc, float setHeight, float setWidth, int scale){
			this->xLoc = xLoc;
			this->yLoc = yLoc;
			this->scale = scale;
			this->width = setWidth;
			this->height = setHeight;
			objHeight = this->scale * this->height;
			objWidth = this->scale * this->width;
		}

		void draw(){
			glPushMatrix();
				//Grey
				glColor3f(.72, .72, .72);
				//Block
				glBegin(GL_QUADS);
					//bottom left
					glVertex2f(this->xLoc, this->yLoc);
					//top left
					glVertex2f(this->xLoc, this->objHeight + this->yLoc);
					//top right
					glVertex2f(this->xLoc + this->objWidth, this->objHeight + this->yLoc);
					//bottom right
					glVertex2f(this->xLoc + this->objWidth, this->yLoc);
				glEnd();	

				glLineWidth(2);
				//White
				glColor3f(1, 1, 1);
				//outline
				glBegin(GL_LINES);
					//left line
					glVertex2f(this->xLoc+1, this->objHeight + this->yLoc);
					glVertex2f(this->xLoc+1, this->yLoc);
					//top line
					glVertex2f(this->xLoc, this->yLoc + this->objHeight - 1);
					glVertex2f(this->xLoc + this->objWidth, this->yLoc + this->objHeight - 1);
				glEnd();

				//Black
				glColor3f(0, 0, 0);
				//outline
				glBegin(GL_LINES);
					//bottom line
					glVertex2f(this->xLoc + 1, this->yLoc + 1);
					glVertex2f(this->xLoc + this->objWidth - 1, this->yLoc + 1);
					//right line
					glVertex2f(this->xLoc + this->objWidth - 1, this->yLoc);
					glVertex2f(this->xLoc + this->objWidth - 1, this->yLoc + this->objHeight - 1);
				glEnd();
				glLineWidth(1);
		glPopMatrix();
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

		const bool COLLIDEABLE = true, UPDATEABLE = false;
	private:
		float xLoc, yLoc, height, width, objHeight, objWidth;
		int scale;
};


#endif