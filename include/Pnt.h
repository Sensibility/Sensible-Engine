#ifndef _PNT_H_
#define _PNT_H_

template <typename T>
class Pnt2
{
public:
	Pnt2() {}
	Pnt2(T pX) : Pnt2() { x_ = pX; } 
	Pnt2(T pX, T pY) : Pnt2(pX) { y_ = pY; }

	virtual T *AsArray()
	{
		T* arr = (T *)malloc(2 * sizeof(T));
		arr[0] = x_; arr[1] = y_;
		return arr;
	}

	T x() const { return x_; };
	void x(T pX) { x_ = pX; };
	void addX(T pX) { x_ += pX; }
	virtual T y() const { return y_; };
	void y(T pY) { y_ = pY; };
	void addY(T pY) { y_ += pY; }
	virtual std::string ToString() 
	{
		char buf[255];
		sprintf(buf, "(%f, %f)", x_, y_);
		return std::string(buf);
	}
protected:
	T x_, y_;
};

template <typename T>
class Pnt3 : public Pnt2<T>
{
public:
	Pnt3(T pX, T pY, T pZ) : Pnt2(pX, pY) { z_ = pZ; };

	T *AsArray() override
	{
		T* arr = (T *)malloc(3 * sizeof(T));
		arr[0] = x(); arr[1] = this->y_; arr[2] = z_;
		return arr;
	}
	T z() const { return z_; };
	void z(T pZ) { z_ = pZ; };
	void addZ(T pZ) { z_ += pZ; }
	std::string ToString() override
	{
		char buf[255];
		sprintf(buf, "(%f, %f, %f)", x(), this->y_, z_);
		return std::string(buf);
	}
protected:
	T z_;
};

template <typename T>
class Pnt4 : public Pnt3<T>
{
public:
	Pnt4(T pX, T pY, T pZ, T pW) : Pnt3(pX, pY, pZ) { w_ = pW; };
	T w() const { return  w_; };
	void w(T pW) { w_ = pW; };

	T *AsArray() override
	{
		T* arr = (T *)malloc(4 * sizeof(T));
		arr[0] = Pnt3<T>::x_; arr[1] = Pnt3<T>::y_; arr[2] = Pnt3<T>::z_; arr[3] = w_;
		return arr;
	}
	std::string ToString() override
	{
		char buf[255];
		sprintf(buf, "(%f, %f, %f, %f)", Pnt3<T>::x_, Pnt3<T>::y_, Pnt3<T>::z_, w_);
		return std::string(buf);
	}
private:
	T w_;
};

#endif _PNT_H_