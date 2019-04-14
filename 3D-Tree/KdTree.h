#include "Node.h"
#include <vector>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>
#include<GL/glut.h>
#define dimension 3

class KdTree3D
{
public:
	Node * root;
	struct Compare {
		int dim;
		bool operator() (Point &a, Point &b) {
			return (a.dim[dim] < b.dim[dim]);
		}
	};
	Compare compare;
	KdTree3D(std::vector<Point> &points)
	{
		Build(points, 0, points.size(), 0);
	}
	Node * Build(std::vector<Point> &points, int begin, int end, int depth)
	{

		if (end - begin <= 0)
			return 0;

		int ax = depth % dimension;
		//if (ax == 0) //nivel x
		//{
		compare.dim = ax;
		sort(points.begin() + begin, points.begin() + end, compare); //K
	//}
/*	else if (ax == 1) //nivel y
	{
		sort(points.begin() + begin, points.begin() + end, comp_x);
	}
	else if (ax == 2) //nivel z
	{
		sort(points.begin() + begin, points.begin() + end, comp_z);
	}*/


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
		std::cout << root->p.dim[0] << root->p.dim[1] << root->p.dim[2] << std::endl;
		Print(root->left, cont + 1);
	}


};
