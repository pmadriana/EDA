#include "Node.h"
#include <vector>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>
#include<GL/glut.h>
#include "KdTree.h"

using namespace std;
Point *a;
/*
bool comp_x(const Point &n1, const Point &n2)
{
	return n1.getPosition().x < n2.getPosition().x;
}

bool comp_y(const Point &n1, const Point &n2)
{
	return n1.getPosition().y < n2.getPosition().y;
}

bool comp_z(const Point &n1, const Point &n2)
{
	return n1.getPosition().z < n2.getPosition().z;
}

*/

float random() // Random number entre [] 
{

	float  r = -5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4 + 5 + 1)));//(rand() % 11) - 5 ;
	while (r == 0) {
		r = (rand() % 10) - 5;//-1.f + (2.f*rand()) * (1.f / RAND_MAX);
	}
	return r;
}

Point* randVec3() // Random vector  AÑADIR ATRIBUTO DIM
{
	//return Vec3(random(), random(), random());
	vector<double>jaja;
	for (int i = 0; i < dimension; i++)
	{
		jaja.push_back(random());
	}
	Point *p = new Point(jaja);
	return p;
}
Point* Vec(int x,int y,int z) // Random vector  AÑADIR DIM
{
	//return Vec3(random(), random(), random());
	vector<double>jaja;
	jaja.push_back(x);
	jaja.push_back(y);
	jaja.push_back(z);
	Point *p = new Point(jaja);
	return p;
}


int main(int argc, char** argv)
{
	vector<Point> points;
	/*points.push_back(Vec3(2, 1, 3));
	points.push_back(Vec3(3, 1, 4));
	points.push_back(Vec3(2, 3, 7));
	points.push_back(Vec3(4, 3, 4));
	points.push_back(Vec3(6, 1, 4));
	points.push_back(Vec3(2, 4, 5));
	points.push_back(Vec3(5, 2, 5));
	points.push_back(Vec3(4, 0, 6));
	points.push_back(Vec3(1, 4, 4));
	points.push_back(Vec3(7, 1, 6));
	points.push_back(Vec3(0, 5, 7));
	points.push_back(Vec3(1, 1, 6));
	points.push_back(Vec3(3, 8, 7));
	*/
	points.push_back(*Vec(4, 4, 3));
	points.push_back(*Vec(-1, 2, 4));
	points.push_back(*Vec(3, -4, 2));
	points.push_back(*Vec(-2, -2, -1));
	points.push_back(*Vec(-1, -3, -1));
	points.push_back(*Vec(-4, -4, -4));
	points.push_back(*Vec(-3.5, -3.5, -3.5));
	const int nPoints = 7;
/*
for (int i = 0; i < nPoints; ++i) {
		points.push_back(*randVec3());
	}*/

	KdTree3D tree(points);
	Node* j =  tree.Build(points, 0, points.size(), 0);
	//cout << "root: " << j->p.getPosition().x << ", " << j->p.getPosition().y << ", " << j->p.getPosition().z << endl;
	int cont= 0;
	tree.Print(j, cont);

}
