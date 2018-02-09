#ifndef BLOCKCELL
#define BLOCKCELL

class BlockCell : public gameObject{
	public:
		BlockCell(float xLoc, float yLoc, float setHeight, float setWidth, int scale){
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
				//Black
				glColor3f(0, 0, 0);
				//outline
				glBegin(GL_LINES);
					//bottom line
					glVertex2f(this->xLoc, this->yLoc + 1);
					glVertex2f(this->xLoc + this->objWidth, this->yLoc + 1);
					//top line
					glVertex2f(this->xLoc, this->yLoc + this->objHeight - 1);
					glVertex2f(this->xLoc + this->objWidth, this->yLoc + this->objHeight - 1);
					//middle block, bottom line
					glVertex2f(this->xLoc, this->yLoc + (this->objHeight / 3));
					glVertex2f(this->xLoc + this->objWidth, this->yLoc + (this->objHeight / 3));

					//top brick
					//top brick, bottom line
					glVertex2f(this->xLoc, this->yLoc + 2*(this->objHeight / 3));
					glVertex2f(this->xLoc + this->objWidth, this->yLoc + 2*(this->objHeight / 3));
					//top brick, right line
					glVertex2f(this->xLoc + this->objWidth - 1, this->yLoc + this->objHeight);
					glVertex2f(this->xLoc + this->objWidth - 1, this->yLoc + 2*(this->objHeight / 3));
					//top brick, left line
					glColor3f(1, 1, 1);
					glLineWidth(1);
					glVertex2f(this->xLoc + 1, this->yLoc + this->objHeight - 2);
					glVertex2f(this->xLoc + 1, this->yLoc + 2*(this->objHeight / 3) + 1);
					//top brick, top shading line
					glVertex2f(this->xLoc + 1, this->yLoc + this->objHeight - 3);
					glVertex2f(this->xLoc + this->objWidth - 2, this->yLoc + this->objHeight - 3);

					//middle bricks
					glColor3f(0, 0, 0);
					glLineWidth(2);
					//mlb, right line
					glVertex2f(this->xLoc + (2*(this->objWidth / 5)), this->yLoc + 2 * (this->objHeight / 3));
					glVertex2f(this->xLoc + (2*(this->objWidth / 5)), this->yLoc + (this->objHeight / 3));
					//mlb top shading line
					glColor3f(1, 1, 1);
					glLineWidth(1);
					glVertex2f(this->xLoc, this->yLoc + 2*(this->objHeight / 3) - 2);
					glVertex2f(this->xLoc + (2*(this->objWidth / 5)) - 1, this->yLoc + 2*(this->objHeight / 3) - 2);

					//mrb left shading line
					glVertex2f(this->xLoc + (2 * (this->objWidth / 5)) + 2, this->yLoc + 2*(this->objHeight / 3) - 1);
					glVertex2f(this->xLoc + (2 * (this->objWidth / 5)) + 2, this->yLoc + (this->objHeight / 3) + 1);
					//mrb top shading line
					glVertex2f(this->xLoc + (2 * (this->objWidth / 5)) + 1, this->yLoc + 2 *(this->objHeight / 3) - 2);
					glVertex2f(this->xLoc + this->objWidth, this->yLoc + 2 *(this->objHeight / 3) - 2);

					//bottom bricks
					glColor3f(0, 0, 0);
					glLineWidth(2);
					//bb seperating line
					glVertex2f(this->xLoc +(3 * (this->objWidth / 5)), this->yLoc);
					glVertex2f(this->xLoc +(3 * (this->objWidth / 5)), this->yLoc + (this->objHeight / 3));
					glColor3f(1, 1, 1);
					glLineWidth(1);
					//blb top shading line
					glVertex2f(this->xLoc, this->yLoc + (this->objHeight / 3) - 2);
					glVertex2f(this->xLoc + (3 * (this->objWidth / 5)) - 1, this->yLoc + (this->objHeight / 3) - 2);
					//brb top shading line
					glVertex2f(this->xLoc + (3 * (this->objWidth / 5)) + 1, this->yLoc + (this->objHeight / 3) - 2);
					glVertex2f(this->xLoc + this->objWidth, this->yLoc + (this->objHeight / 3) - 2);
					//brb left shading line
					glVertex2f(this->xLoc + (3 * (this->objWidth / 5)) + 2, this->yLoc + 2);
					glVertex2f(this->xLoc + (3 * (this->objWidth / 5)) + 2, this->yLoc + (this->objHeight / 3) - 2);
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

		bool getBlock(){
			return true;
		}

		const bool COLLIDABLE = true, UPDATEABLE = false;
	private:
		float xLoc, yLoc, height, width, objHeight, objWidth;
		int scale;
};


#endif