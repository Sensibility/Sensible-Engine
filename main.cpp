#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <memory>
#include <iostream>
#include "drawing.h"
#include "keys.h"
#include "gameObject.h"
#include "blockCell.h"
#include "wallCell.h"
#include "user.h"
#include <time.h>
#include "door.h"
#include "enemy.h"

int counter = 0;
char level = '1';
bool moving = false;
int moveX = 0, moveY = 0, enemies = 1;
bool blinking = false;
bool closed = true;
float irisX;
float irisY;

int windowWidth = 1150, windowHeight = 650;
int tileWidth = 50, tileHeight = 50;

std::vector<std::shared_ptr<gameObject>> objects;

int windowId;

float getRand() {
   	return rand() / (float)RAND_MAX;
}

void addEnemies(){
	for(int i = 0; i < enemies; i++){
		if(i == 0){
    		objects.push_back( std::shared_ptr<gameObject> (new Enemy(505, 255, tileHeight - 10, tileWidth - 10, 1)) );
		}
		else if(i == 1){
    		objects.push_back( std::shared_ptr<gameObject> (new Enemy(355, 455, tileHeight - 10, tileWidth - 10, 1)) );
		}
    	else if(i == 9){
    		objects.push_back( std::shared_ptr<gameObject> (new Enemy(305, 455, tileHeight - 10, tileWidth - 10, 1)) );
    	}
    	else if(i == 2){
    		objects.push_back( std::shared_ptr<gameObject> (new Enemy(305, 155, tileHeight - 10, tileWidth - 10, 1)) );
    	}
    	else if(i == 3){
    		objects.push_back( std::shared_ptr<gameObject> (new Enemy(705, 555, tileHeight - 10, tileWidth - 10, 1)) );
    	}
    	else if(i == 4){
    		objects.push_back( std::shared_ptr<gameObject> (new Enemy(1005, 255, tileHeight - 10, tileWidth - 10, 1)) );
    	}
    	else if(i == 5){
    		objects.push_back( std::shared_ptr<gameObject> (new Enemy(905, 455, tileHeight - 10, tileWidth - 10, 1)) );
    	}
    	else if(i == 6){
    		objects.push_back( std::shared_ptr<gameObject> (new Enemy(955, 55, tileHeight - 10, tileWidth - 10, 1)) );
    	}
    	else if(i == 7){
    		objects.push_back( std::shared_ptr<gameObject> (new Enemy(155, 55, tileHeight - 10, tileWidth - 10, 1)) );
    	}
    	else if(i == 8){
    		objects.push_back( std::shared_ptr<gameObject> (new Enemy(55, 355, tileHeight - 10, tileWidth - 10, 1)) );
    	}
	}
}

void removeEnemies(){
	for(int i = 0; i < enemies; i++){
		objects.pop_back();
	}

}

void restartGame(int levels = 0){
	objects.at(0)->setX(55);
	objects.at(0)->setY(55);
	removeEnemies();
	if(levels != 0) enemies = levels;
	addEnemies();
}

//go up a level
void levelComp(){
	int levels = 0;
	if(level != '9'){
		level++;
		levels  = level - 48;
	}
	else{
		level = '+';
		levels  = 10;
	}
	restartGame(levels);
}

//restart :(
void levelLose(){
	level = '1';
	restartGame(1);
}

void changeSize( int w, int h ) {
    windowWidth = w;
    windowHeight = h;

    // update the projection matrix based on the window size
    // the GL_PROJECTION matrix governs properties of the view;
    // i.e. what gets seen - use an Orthographic projection that ranges
    // from [0, windowWidth] in X and [0, windowHeight] in Y. (0,0) is the lower left.
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, windowWidth, 0, windowHeight + 50 );
    
    // update the viewport as well - tell OpenGL we want to render the whole window
    glViewport( 0, 0, windowWidth, windowHeight + 50 );

    // just as good practice, switch back to GL_MODELVIEW mode; that's the matrix
    // that we want to be changing with glTranslatef(), glScalef(), etc., so
    // just in case we forget to explicitly set it later...
    glMatrixMode( GL_MODELVIEW );
}

void timerFunc(int value){
	unsigned int i = 0;
	counter++;
	//used for blinking
    if(counter == 120){
    	counter = 0;
    	blinking = true;
    }
    if(counter == 5) blinking = false;
    //update all objects if they can be updated
	for(std::vector<std::shared_ptr<gameObject>>::iterator it = objects.begin(); it != objects.end(); ++it){
		/*if(i == 0 && moving){
			if(it->get()->getX() != moveX){
				int x = 0;
				if(it->get()->getX() < moveX) x =10;
				else x = -10;
				it->get()->traverseX(x);
			}
			else if(it->get()->getY() != moveY){
				int y = 0;
				if(it->get()->getY() < moveY) y = 10;
				else y = -10;
				it->get()->traverseY(y);
			}
			else moving = false;
		}
		++i*/
		++i;
		if(it->get()->UPDATEABLE){
			bool result = it->get()->update();
			if(!result){
				break;
			}
		};
	}

	glutPostRedisplay();
    glutTimerFunc((1000/60), timerFunc, 0);
}

//DEBUG
void drawGrid(){
	glPushMatrix();
	    glColor3f(0, 0, 0);
	    glBegin(GL_LINES);
	    	for(int i = tileWidth; i <= windowWidth; i+=tileWidth){
	    		glVertex2f(i, 0);
	    		glVertex2f(i, windowHeight);
	    	}
	    	for(int i = tileHeight; i <= windowHeight; i+=tileHeight){
	    		glVertex2f(0, i);
	    		glVertex2f(windowWidth, i);
	    	}
	    glEnd();	
	glPopMatrix();
}

//Draw level text
void drawLevelText(){
	glPushMatrix();
		glTranslatef(537, 668, 0);
		glColor4f(0, 0, 1, 1);
		glScalef(.2, .2, 0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'L');
		glTranslatef(10, 0, 0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
		glTranslatef(10, 0, 0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'v');
		glTranslatef(10, 0, 0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
		glTranslatef(10, 0, 0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'l');
		glTranslatef(20, 0, 0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, level);
	glPopMatrix();
}

//Draw everything
void drawMap(){
	glPushMatrix();
		for(std::vector<std::shared_ptr<gameObject>>::iterator it = objects.begin(); it != objects.end(); ++it) {
    		it->get()->draw();
		}
		drawLevelText();
#ifdef DEBUG
		drawGrid();
#endif
	glPopMatrix();
}

void renderScene() {
    // clear whatever was drawn to the screen last time - 
    // set the clear color to black and then signal to clear the RGB buffer.
    glDrawBuffer(GL_BACK);
    glClearColor( 0, 146, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT );

    // switch to GL_MODELVIEW, for when we start using glTranslatef(), glScalef(), etc..
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glPushMatrix();
    	drawMap();
	glPopMatrix();
	
    glFlush();

	glutSwapBuffers();
}

void keyPressCall(unsigned char key, int mouseX, int mouseY){
	std::string val = handleKey(key, mouseX, mouseY, true);
	if(val == "No Action") return;
	if(val == "ESCAPE") exit(0);
	//restart level
	if(val == "r" || val == "R"){
		if(level == '+') level = 9;
		else if(level != '1') level--;
		restartGame((int)level - 48);
	}
#ifdef DEBUG
	std::cout << val << ": ";
	for(int i = 0; i < 6; i++){
		std::cout << keys[val][i] << ", ";
	}
	std::cout << std::endl << pressedKeys.size();
	std::cout << std::endl;
#endif

}

void keyReleaseCall(unsigned char key, int mouseX, int mouseY){
	std::string val = handleKey(key, mouseX, mouseY, false);
	if(val == "No Action") return;
#ifdef DEBUG
	std::cout << val << ": ";
	for(int i = 0; i < 6; i++){
		std::cout << keys[val][i] << ", ";
	}
	std::cout << std::endl << pressedKeys.size();
	std::cout << std::endl;
#endif
}

int roundUp50(int val){
	return (50 - val % 50) + val;
}

int roundDown50(int val){
	return val - val % 50;
}

void mousePressCall( int button, int state, int mouseX, int mouseY ){
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
			blinking = true;
			closed = false;
			/*if(moving == false){
				mouseY = (windowHeight - mouseY);
				mouseX = roundUp50(mouseX)-1;
				mouseY = roundUp50(mouseY)-1;
				bool result = true;
				for(std::vector<std::shared_ptr<gameObject>>::iterator it = objects.begin(); it != objects.end(); ++it) {
					if(
						(mouseX > it->get()->getX() && mouseX < it->get()->getX() + it->get()->getWidth())
						&&
						(mouseY > it->get()->getY() && mouseY < it->get()->getY() + it->get()->getHeight())
					){
						result = false;
						break;
					}
				}
				if(result){
					//moving = true;
					moveX = (mouseX + 1) - 45;
					moveY = (mouseY + 1) - 45;
				}
			}*/
				mouseY = (windowHeight - mouseY);
				mouseX = roundUp50(mouseX) - 1;
				mouseY = roundUp50(mouseY) - 1;
				bool result = false;
				unsigned int i = 0;
				for(std::vector<std::shared_ptr<gameObject>>::iterator it = objects.begin(); it!= objects.end(); ++it){
					if(it->get()->getBlock() == true){
						if(
							(mouseX > it->get()->getX() && mouseX < it->get()->getX() + it->get()->getWidth())
							&&
							(mouseY > it->get()->getY() && mouseY < it->get()->getY() + it->get()->getHeight())
						){
							result = true;
							break;
						}
					}
					++i;
				}
				if(result){
					objects.erase(objects.begin() + i);
				}
		}
		else{
			blinking = false;
			closed = true;
		}
	}
}

void mouseMoveCall( int mouseX, int mouseY ){
	mouseY = windowHeight - mouseY;
	irisY = mouseY;
	irisX = mouseX;
}


int main( int argc, char* argv[] ) {
    glutInit( &argc, argv );

    srand( time(NULL) );

    // request a window with just an RGB frame buffer, nothing fancy...
    // place it at (50,50) on the screen and set its size to our constants from earlier
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( windowWidth, windowHeight + 50 );
    
    // this actually creates our window.
    windowId = glutCreateWindow( "SQ 1" );

    objects.push_back( std::shared_ptr<gameObject> (new User(55, 55, tileHeight - 10, tileWidth - 10, 1)) );

    for(int i = 0; i < windowWidth; i+=tileWidth){
    	for(int j = 0; j < windowHeight; j+=tileHeight){
    		if(
    			(
	    			(i != 0 && i != (windowWidth - tileWidth)) &&
	    			(j != 0 || j != (windowHeight - tileHeight))
	    		) 
	    		&&
	    		(
	    			(j != 0 && j != (windowHeight - tileHeight)) &&
	    			(i != 0 || i != (windowHeight - tileWidth))
	    		)
    		) continue;
    		objects.push_back( std::shared_ptr<gameObject> (new WallCell(i, j, tileHeight, tileWidth, 1)) );
    	}
    }

    for(int i = 2 * tileWidth; i < windowWidth - (tileWidth * 2); i+=(tileWidth * 2)){
    	for(int j = 2 * tileHeight; j < windowHeight - (tileHeight * 2); j+=(tileHeight * 2)){
    		objects.push_back( std::shared_ptr<gameObject> (new WallCell(i, j, tileHeight, tileWidth, 1)) );
    	}
    }

    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(50, 100, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(100, 50, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(50, 550, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(150, 150, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(150, 200, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(150, 400, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(150, 550, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(450, 150, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(450, 350, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(450, 450, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(550, 250, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(550, 250, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(600, 150, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(650, 150, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(700, 150, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(650, 550, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(650, 450, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(650, 350, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(650, 250, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(650, 150, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(700, 350, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(1050, 250, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(1000, 550, tileHeight, tileWidth, 1)) );
    objects.push_back( std::shared_ptr<gameObject> (new BlockCell(1050, 500, tileHeight, tileWidth, 1)) );
    
    objects.push_back( std::shared_ptr<gameObject> (new Door(1050, 550, tileHeight, tileWidth, 1)) );

    addEnemies();

    glutDisplayFunc( renderScene );
    glutReshapeFunc( changeSize );

	/********** ADD CALLBACKS ***************/
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyPressCall);
    glutKeyboardUpFunc(keyReleaseCall);
    glutMouseFunc(mousePressCall);
    glutPassiveMotionFunc(mouseMoveCall);
    glutTimerFunc((1000/60), timerFunc, 0);

    // begin GLUT loop
    glutMainLoop();    

    return 0;
}
