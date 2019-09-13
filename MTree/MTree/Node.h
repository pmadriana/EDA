#pragma once
#include <iostream>
#include <vector>
using namespace std;


struct Point
{
	// double x, y;
	Point() {}
	vector<double> dimensiones;
	Point(vector<double>& dimensiones)
	{
		this->dimensiones = dimensiones;
	}
	Point(initializer_list<double> dimensiones)
	{
		this->dimensiones = dimensiones;
	}
	
};

bool operator==(const Point& p1, const Point& p2)
{
	for (int i = 0; i < p1.dimensiones.size(); ++i)
		if (p1.dimensiones[i] != p2.dimensiones[i])
			return false;
	return true;
}

class Circulo
{
public:
	double radius;
	Point center;
	Circulo(Point& center, double radius)
	{
		this->radius = radius;
		this->center = center;
	}
};
class Node
{
public:
	bool isleaf;
	vector<Circulo> circulos;
	vector<Node*> children;
	vector<Point> objetos;
	Node() {}
	Node(vector<Point>& points)
	{
		this->objetos = points;
		this->isleaf = true;
	}
	Node(vector<Circulo>& circulos)
	{
		this->circulos = circulos;
		this->isleaf = false;
	}
	void addCirculo(Circulo& circulo)
	{
		circulos.push_back(circulo);
	}
	void addObjeto(Point& p)
	{
		objetos.push_back(p);
	}
	void addChildren(Node *&n)
	{
		children.push_back(n);
	}
};