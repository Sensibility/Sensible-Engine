#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <memory>

class gameObject{
	public:
		virtual void draw(){};
		virtual bool update(){return true;};

		virtual void traverseX(int amount){};
		virtual void traverseY(int amount){};

		virtual float getX(){return 0;};
		virtual float getY(){return 0;};
		virtual float getHeight(){return 0;};
		virtual float getWidth(){return 0;};
	
		virtual void setHeight(float height){};
		virtual void setWidth(float width){};
		virtual void setX(float x){};
		virtual void setY(float y){};

		virtual bool getBlock(){return false;};

		const bool COLLIDEABLE = true, UPDATEABLE = true;
	private:
		float xLoc, yLoc, height, width, objHeight, objWidth;
		int scale;
};

//True means there is a collision
using namespace std;
bool collides(gameObject *obj1, gameObject *obj2, bool override = true){
		if(
			(
				((obj1->getX() + obj1->getWidth()) >= obj2->getX() && obj1->getX() <= (obj2->getX() + obj2->getWidth()))
				||
				((obj2->getX() + obj2->getWidth()) >= obj1->getX() && obj2->getX() <= (obj1->getX() + obj1->getWidth()))
			) 
			&&
			(
				((obj1->getY() + obj1->getHeight()) >= obj2->getY() && obj1->getY() <= (obj2->getY() + obj2->getHeight())) 
				||
				((obj2->getY() + obj2->getHeight()) >= obj1->getY() && obj2->getY() <= (obj1->getY() + obj1->getHeight()))
			) 
		) return true;
		else return false;
}

#endif