#ifndef DRAWING
#define DRAWING

#define DEG2RAD 3.14159 / 180.0
namespace Drawing{
	void drawEllipseEmpty(float x, float y, int degrees){
		if(degrees == 0) degrees = 360;
		glBegin(GL_LINE_STRIP);
		for(int i = 0; i <= degrees; i++){
			float degInRad = i * DEG2RAD;
			glVertex2f(cos(degInRad) * x, sin(degInRad) * y);
		}
		glEnd();
	}

	void drawEllipseFull(float x, float y, int degrees){
		if(degrees == 0) degrees = 360;
		glVertex2f(0, 0);
		glBegin(GL_TRIANGLE_FAN);
			for(int i = 0; i <+ degrees; i++){
				float degInRad = i * DEG2RAD;
				glVertex2f(cos(degInRad) * x, sin(degInRad) * y);
			}
		glEnd();
	}

	void drawRing(float x, float y, float innerX, float innerY, int degrees){
		
	}
}



#endif