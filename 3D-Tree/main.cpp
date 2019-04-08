include "Node.h"
#include <vector>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>
#include<GL/glut.h>

#define dimension 3
using namespace std;


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

float random() // Random number entre [] 
{

	float  r = -5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4 + 5 + 1)));//(rand() % 11) - 5 ;
	while (r == 0) {
		r = (rand() % 10) - 5;//-1.f + (2.f*rand()) * (1.f / RAND_MAX);
	}
	return r;
}

Vec3 randVec3() // Random vector 
{
	return Vec3(random(), random(), random());
}


class KdTree3D
{
public:
	Node * root;
	KdTree3D(std::vector<Point> &points)
	{
		Build(points, 0, points.size(), 0);
	}
	Node * Build(std::vector<Point> &points, int begin, int end, int depth)
	{

		if (end - begin <= 0)
			return 0;

		int ax = depth % dimension;
		if (ax == 0) //nivel x
		{
			sort(points.begin() + begin, points.begin() + end, comp_x);
		}
		else if (ax == 1) //nivel y
		{
			sort(points.begin() + begin, points.begin() + end, comp_x);
		}
		else if (ax == 2) //nivel z
		{
			sort(points.begin() + begin, points.begin() + end, comp_z);
		}
		else
		{
			printf(" Error");
		}

		int half = (begin + end) / 2;
		Node * median = new Node(points[half]);
		median->left = Build(points, begin, half, depth + 1);
		median->right = Build(points, half + 1, end, depth + 1);

		if (depth == 0)
		{
			root = median;
		}
		return median;
	}

	void Print(Node * root, int cont)
	{
		//cout << "root: " << root->p.getPosition().x << ", " << root->p.getPosition().y << ", " << root->p.getPosition().z << endl;
		if (root == 0)
		{
			return;
		}
		

		//cout << root->right->p.getPosition().x << root->right->p.getPosition().y << " l " << root->left->p.getPosition().x << root->left->p.getPosition().y << endl;
		Print(root->right, cont + 1);
		
		for (int i = 0; i < cont; i++)
			cout << "  ";
		std::cout << root->p.getPosition().x << root->p.getPosition().y << root->p.getPosition().z << std::endl;
		Print(root->left, cont + 1);
	}
	

};




using namespace std;


int main()
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
	*//*
	points.push_back(Vec3(4, 4, 3));
	points.push_back(Vec3(-1, 2, 4));
	points.push_back(Vec3(3, -4, 2));
	points.push_back(Vec3(-2, -2, -1));
	points.push_back(Vec3(-1, -3, -1));
	points.push_back(Vec3(-4, -4, -4));
	points.push_back(Vec3(-3.5, -3.5, -3.5));*/
	const int nPoints = 10000;
	for (int i = 0; i < nPoints; ++i) {
		points.push_back(randVec3());
	}

	KdTree3D tree(points);
	Node* j =  tree.Build(points, 0, points.size(), 0);
	cout << "root: " << j->p.getPosition().x << ", " << j->p.getPosition().y << ", " << j->p.getPosition().z << endl;
	int cont= 0;
	tree.Print(j, cont);

	int z;
	cin >> z;
}
