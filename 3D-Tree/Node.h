#pragma once
#include "Point.h"
class Node
{
public:
	Node * left, *right;
	Point p;
	Node(Point p)
	{
		this->p = p;
		this->left = 0;
		this->right = 0;
	}
};
