// ----------------------------------------------------
// 4 Dimensions vector class                -----------
// ----------------------------------------------------

#ifndef __VECTOR4D_H__
#define __VECTOR4D_H__

#include "p2Defs.h"
#include <math.h>

template<class TYPE>
class Vector4d {

public:

	TYPE x, y, z, k;

	Vector4d()
	{}

	Vector4d(const Vector4d<TYPE> &q)
	{
		this->x = q.x;
		this->y = q.y;
		this->z = q.z;
		this->k = q.k;
	}

	Vector4d(const TYPE& x, const TYPE& y, const TYPE& z, const TYPE& k)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->k = k;
	}

	Vector4d& create(const TYPE& x, const TYPE& y, const TYPE& z, const TYPE& k)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->k = k;

		return(*this);
	}

	// Math ------------------------------------------------
	Vector4d operator -(const Vector4d &v) const
	{
		Vector4d r;

		r.x = x - v.x;
		r.y = y - v.y;
		r.z = z - v.z;
		r.k = k - v.k;

		return(r);
	}

	Vector4d operator + (const Vector4d &v) const
	{
		Vector4d r;

		r.x = x + v.x;
		r.y = y + v.y;
		r.z = z + v.z;
		r.k = k + v.k;

		return(r);
	}

	const Vector4d& operator -=(const Vector4d &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		k -= v.k;

		return(*this);
	}

	const Vector4d& operator +=(const Vector4d &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		k += v.k;

		return(*this);
	}

	bool operator ==(const Vector4d& v) const
	{
		return (x == v.x && y == v.y && z == v.z && k == v.k);
	}

	bool operator !=(const Vector4d& v) const
	{
		return (x != v.x || y != v.y && z != v.z && k != v.k);
	}

	// Utils ------------------------------------------------
	bool IsZero() const
	{
		return (x == 0 && y == 0 && z == 0 && k == 0);
	}

	Vector4d& SetToZero()
	{
		x = y = z = k = 0;
		return(*this);
	}

	Vector4d& Negate()
	{
		x = -x;
		y = -y;
		z = -z;
		k = -k;

		return(*this);
	}

	// Distances (NOT IMPORTANT FOR WHAT WE WANT NOW) ---------------------------------------------
	/*TYPE DistanceTo(const Vector4d& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return sqrtf((fx*fx) + (fy*fy));
	}

	TYPE DistanceNoSqrt(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (fx*fx) + (fy*fy);
	}

	TYPE DistanceManhattan(const p2Point& v) const
	{
		return abs(v.x - x) + abs(v.y - y);
	}*/
};

typedef Vector4d<int> iPoint4d;
typedef Vector4d<float> fPoint4d;

#endif