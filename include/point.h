#ifndef _POINT_H_
#define _POINT_H_ 1

#include "PointBase.h"
#include "Vector.h"
#include "matrix.h"
#include <vector>
#include <ostream>

using namespace std;


class Point : public PointBase {
public:

	// CONSTRUCTORS / DESTRUCTORS
	Point();

	Point(int a, int b, int c);

	Point(double a, double b, double c);

	// MISCELLANEOUS
	double at(int i);

	/* call glVertex3f( a, b, c ) */
	void glVertex();

	/* call glTexCoord2f( a, b ) */
	void glTexCoord();

	/* call glTranslatef( a, b, c ) */
	void glTranslate();

	Point &operator+=(Vector rhs);

	Point &operator-=(Vector rhs);

	Point &operator*=(float rhs);

	Point &operator/=(float rhs);

	vector<float> toVector();
	friend ostream &operator<<(ostream &os, const Point &point);

};

// RELATED OPERATORS

Point operator*(Point a, float f);

Point operator/(Point a, float f);

Point operator/(float f, Point p);

Point operator*(float f, Point a);

Vector operator-(Point a, Point b);

Point operator+(Point a, Vector b);

Point operator+(Vector a, Point b);

Point operator+(Point a, Point b);

bool operator==(Point a, Point b);

bool operator!=(Point a, Point b);

Point operator*(Point a, Point b);

void glTranslatef(Point p);

void glVertex3f(Point p);

void gluLookAt(Point eye, Point lookAt, Point up);

#endif

