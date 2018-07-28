#include "../include/point.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <assert.h>


Point::Point() {
	x = y = z = 0;
	w = 1;
}

Point::Point(int a, int b, int c) {
	x = a;
	y = b;
	z = c;
	w = 1;
}

Point::Point(double a, double b, double c) {
	x = a;
	y = b;
	z = c;
	w = 1;
}



// OPERATOR OVERLOADS

Point operator*(Point a, float f) {
	return Point( a.getX() * f, a.getY() * f, a.getZ() * f );
}

Point operator/(Point a, float f) {
	return Point( a.getX() / f, a.getY() / f, a.getZ() / f );
}

Point operator/(float f, Point a) {
	return Point( a.getX() / f, a.getY() / f, a.getZ() / f );
}

Point operator*(float f, Point a) {
	return Point( a.getX() * f, a.getY() * f, a.getZ() * f );
}

Point operator*(Point a, Point b)
{
	return Point(a.getX() * b.getX(), a.getY() * b.getY(), a.getZ() * b.getZ());
}

Point operator+(Point a, Vector b) {
	return Point( a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

Vector operator-(Point a, Point b) {
	return Vector( a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}


Point &Point::operator+=(Vector rhs) {
	this->setX( this->getX() + rhs.getX());
	this->setY( this->getY() + rhs.getY());
	this->setZ( this->getZ() + rhs.getZ());
	return *this;
}


Point &Point::operator-=(Vector rhs) {
	this->setX( this->getX() - rhs.getX());
	this->setY( this->getY() - rhs.getY());
	this->setZ( this->getZ() - rhs.getZ());
	return *this;
}

Point &Point::operator*=(float rhs) {
	this->setX( this->getX() * rhs );
	this->setY( this->getY() * rhs );
	this->setZ( this->getZ() * rhs );
	return *this;
}

Point &Point::operator/=(float rhs) {
	this->setX( this->getX() / rhs );
	this->setY( this->getY() / rhs );
	this->setZ( this->getZ() / rhs );
	return *this;
}

Point operator+(Point a, Point b) {
	return Point( a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

bool operator==(Point a, Point b) {
	return (a.getX() == b.getX() && a.getY() == b.getY() && a.getZ() == b.getZ());
}

bool operator!=(Point a, Point b) {
	return !(a == b);
}

// MEMBER FUNCTIONS

double Point::at(int i) {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	return -1;
}

void Point::glVertex() {
	glVertex3f( x, y, z );
}

void Point::glTexCoord() {
	glTexCoord2f( x, y );
}

void Point::glTranslate() {
	glTranslatef( x, y, z );
}

void glTranslatef(Point p) {
	p.glTranslate();
}

void glVertex3f(Point p) {
	p.glVertex();
}

void gluLookAt(Point eye, Point lookAt, Point upVector) {
	gluLookAt( eye.getX(), eye.getY(), eye.getZ(),
			   lookAt.getX(), lookAt.getY(), lookAt.getZ(),
			   upVector.getX(), upVector.getY(), upVector.getZ());
}


vector<float> Point::toVector() {
	vector<float> ret;
	ret.push_back( x );
	ret.push_back( y );
	ret.push_back( z );
	return ret;
}

ostream &operator<<(ostream &os, const Point &point) {
	os << "X: " << point.getX() << ", Y: " << point.getY() << ", Z: " << point.getZ();
	return os;
}
