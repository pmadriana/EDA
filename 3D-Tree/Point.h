#pragma once
#include <cmath>
#include <vector>
using namespace std;
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
public:
	Vec3 position;
	vector<double> dim; //dim.size = 3 x,y,z [1,2,3]
	double data;
	Point() { }
	Point(vector<double>& dim_, double data_) : dim(dim_), data(data_) {}
	Point(vector<double>& dim_) : dim(dim_) {}
	/*Point(const Vec3& position) : position(position) { }*/
	inline const Vec3& getPosition() const { return position; }
	inline void setPosition(const Vec3& p) { position = p; }
};
