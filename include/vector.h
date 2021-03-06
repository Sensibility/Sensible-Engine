#ifndef _VECTOR_H_
#define _VECTOR_H_ 1

#include <ostream>
#include "PointBase.h"
#include "matrix.h"

using namespace std;

class Vector : public PointBase {
public:

	// CONSTRUCTORS / DESTRUCTORS
	Vector();

	Vector(int a, int b, int c);

	Vector(double a, double b, double c);

	// MISCELLANEOUS
	double magSq();

	double mag();

	void normalize();

	double at(int i);

	Vector &operator+=(Vector rhs);

	Vector &operator-=(Vector rhs);

	Vector &operator*=(float rhs);

	Vector &operator/=(float rhs);

	ostream &operator<<(ostream &str);

	/* call glNormal3f( a, b, c ) */
	void glNormal();
};

// RELATED OPERATORS

Vector operator*(Vector a, Vector b);

Vector operator*(Vector a, float f);

Vector operator/(Vector a, float f);

Vector operator*(float f, Vector a);

Vector operator+(Vector a, Vector b);

Vector operator-(Vector a, Vector b);

bool operator==(Vector a, Vector b);

bool operator!=(Vector a, Vector b);

Vector cross(Vector a, Vector b);

double dot(Vector a, Vector b);

void glRotatef(float angle, Vector axis);

void glNormal3f(Vector normal);

#endif

