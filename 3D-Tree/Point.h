#pragma once
#include <cmath>
struct Vec3;

struct Vec3 {
	union {
		struct {
			float x, y, z;
		};
		float D[3];
	};

	Vec3() { }
	Vec3(float _x, float _y, float _z)
		:x(_x), y(_y), z(_z)
	{ }

};
class Point {

	Vec3 position;
public:
	Point() { }
	Point(const Vec3& position) : position(position) { }
	inline const Vec3& getPosition() const { return position; }
	inline void setPosition(const Vec3& p) { position = p; }
};
/*class Point
{
public:

	double x, y, z;
	vector<double> coord;

	Point()
	{
		this->x = 0.0;
		this->y = 0.0;
		this->z = 0.0;
	}

	Point(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};*/
