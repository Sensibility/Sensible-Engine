#ifndef _POINTBASE_H_
#define _POINTBASE_H_ 1



class PointBase {
public:
	// GETTERS / SETTERS
	double getX()const;

	void setX(double x);

	double getY()const;

	void setY(double y);

	double getZ()const;

	void setZ(double z);

	double getW();

	double get(int i);

	/* return values as an array */
	double *asArray();

	/* deprecated due to poor naming!!! */
	double *asVector();

	/* four dimensional array */
	double *asArray4D();

	/* three dimensional array */
	double *asArray3D();

	/* two dimensional array */
	double *asArray2D();

	/* one dimensional array */
	double *asArray1D();

	/* return value as string in format "(x, y, z)" */
	char *toString();

protected:
	// MEMBER VARIABLES
	double x, y, z, w;
};

#endif _POINTBASE_H_

