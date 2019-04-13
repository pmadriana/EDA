#ifndef OctreePoint_H
#define OctreePoint_H


#include <cmath>

struct Vec3;
Vec3 operator*(float r, const Vec3& v);

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

	float& operator[](unsigned int i) {
		return D[i];
	}

	const float& operator[](unsigned int i) const {
		return D[i];
	}

	float maxComponent() const {
		float r = x;
		if (y > r) r = y;
		if (z > r) r = z;
		return r;
	}

	float minComponent() const {
		float r = x;
		if (y < r) r = y;
		if (z < r) r = z;
		return r;
	}

	Vec3 operator+(const Vec3& r) const {
		return Vec3(x + r.x, y + r.y, z + r.z);
	}

	Vec3 operator-(const Vec3& r) const {
		return Vec3(x - r.x, y - r.y, z - r.z);
	}

	Vec3 cmul(const Vec3& r) const {
		return Vec3(x*r.x, y*r.y, z*r.z);
	}

	Vec3 cdiv(const Vec3& r) const {
		return Vec3(x / r.x, y / r.y, z / r.z);
	}

	Vec3 operator*(float r) const {
		return Vec3(x*r, y*r, z*r);
	}


	Vec3 operator/(float r) const {
		return Vec3(x / r, y / r, z / r);
	}
};


class OctreePoint {

	Vec3 position;
public:
	OctreePoint() { }
	OctreePoint(const Vec3& position) : position(position) { }
	inline const Vec3& getPosition() const { return position; }
	inline void setPosition(const Vec3& p) { position = p; }
};

#endif
