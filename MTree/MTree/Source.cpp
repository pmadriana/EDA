#include <iostream>
#include <math.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono> 
#include <time.h>

#include <sstream>
#include "Node.h"

using namespace std;
using namespace std::chrono;

double euclidean_distance(const Point& a, const Point& b) {
	double rpta = 0;
	for (int i = 0; i < a.dimensiones.size(); ++i) {
		rpta += pow((a.dimensiones[i] - b.dimensiones[i]), 2);
	}
	return sqrt(rpta);
}

bool operator<(pair<double, Point> p1, pair<double, Point> p2)
{
	return p1.first < p2.first;
}


class Mtree
{
public:
	int m, M;
	Node *root;
	Mtree();
	Mtree(int m)
	{
		root = new Node;
		root->isleaf = true;
		this->M = m;
	}

	void promotion(vector<Point>& points, Point& O1, Point& O2) //M_RAD
	{
		double maxDis = 0;
		for (int i = 0; i < points.size(); ++i)
		{
			for (int j = 0; j < points.size(); ++j)
			{
				if (i != j)
				{
					double d = euclidean_distance(points[i], points[j]);
					if (d > maxDis)
					{
						maxDis = d;
						O1 = points[i];
						O2 = points[j];
					}
				}
			}
		}
	}

	void partition(vector<Point>& points, Point O1, Point O2, vector<Point>& N1, vector<Point>& N2) //HYPERPLANE
	{
		for (const Point& pt : points)
		{
			if (!(pt == O1 || pt == O2)) 
			{
				if (euclidean_distance(pt, O1) < euclidean_distance(pt, O2)) 
					N1.push_back(pt);
				else
					N2.push_back(pt);
			}
		}
	}
	double getRadio(Point& p1, vector<Point>& points)
	{
		double max =0;
		for (int i = 0; i < points.size(); i++)
		{
			if (euclidean_distance(points[i], p1) > max)
				max = euclidean_distance(points[i], p1);
		}
		return max;
	}
	void split(Node *&n, Point p)
	{
		vector<Point> points, N1, N2; 
		points = n->objetos;
		Point O1, O2;
		promotion(points, O1, O2);
		partition(points, O1, O2, N1, N2);
		Node *p1 = new Node(N1);
		Node *p2 = new Node(N2);
		vector<Circulo> c;
		c.push_back(Circulo(O1, getRadio(O1, N1 )));
		c.push_back(Circulo(O2, getRadio(O2, N2 )));
		n->circulos = c;
		n->objetos.clear();
		n->isleaf = false;
		n->children.push_back(p1);
		n->children.push_back(p2);
		if (euclidean_distance(O1, p) < euclidean_distance(O2, p))
		{
			if (N1.size() < M)
				n->children[0]->addObjeto(p);
			else
				split(p1, p);
		}
		else
		{
			if (N2.size() < M)
				n->children[1]->addObjeto(p);
			else
				split(p2, p);
		}
		
	}

	void insertar(Point p)
	{
		insertar(root, p);
	}

	void insertar(Node *n, Point p) //n node, entry O(n)
	{

		if (!n->isleaf)
		{
			Node* child = NULL;
			double min = INFINITY;
			int idx = 0;
			for (int i = 0; i< n->circulos.size(); i++)
			{
				if (euclidean_distance(n->circulos[i].center, p) < min)
				{
					min = euclidean_distance(n->circulos[i].center, p);
					child = n->children[i];
					idx = i;
				}
			}
			n->circulos[idx].radius = max(n->circulos[idx].radius, euclidean_distance(p, n->circulos[idx].center));
			insertar(child, p);
		}
		else /* n es una hoja*/
		{
			if (n->objetos.size() < M) //n->isNotFull
				n->addObjeto(p);
			else
				split(n, p);
		}
	}

	void print()
	{
		print(this->root, 0);
	}
	void print(Node* n, int tab)
	{
		if (!n->isleaf)
		{
			for (int i=0; i<n->circulos.size(); ++i)
			{
				std::string tt("    ", tab);
				cout << tt << "Circulo "; 
				for (double dim : n->circulos[i].center.dimensiones)
					cout << " " << dim;
				cout << "[" << n->circulos[i].radius << "]";
				cout << endl;
				print(n->children[i], tab + 1);
			}
		}
		else
		{
			for (int i = 0; i < n->objetos.size(); ++i)
			{
				std::string tt("    ", tab);
				cout << tt << "Punto ";// << n->objetos[i].x << "  " << n->objetos[i].y << endl;
				for (double dim : n->objetos[i].dimensiones)
					cout << " " << dim;
				cout << endl;
			}
		}
	}

	vector<Point> find_all(Node *n)
	{
		vector<Point> pts;
		if (!(n->isleaf)) {
			for (int i = 0; i < n->circulos.size(); i++)
			{
				vector<Point> vec = find_all(n->children[i]);
				for (Point p : vec)
					pts.push_back(p);
				pts.push_back(n->circulos[i].center);
			}
		}
		else
		{
			return n->objetos;
		}
		return pts;
	}

	vector<Point> knn_search(Node *n, Point &Q, int k)
	{
		vector<Point> pts;
		if (!(n->isleaf))
		{
			for(int i = 0; i < n->circulos.size(); i++)
			{
				if (euclidean_distance(Q, n->circulos[i].center) < n->circulos[i].radius) //esta dentro
				{
					pts = knn_search(n->children[i], Q, k);
					pts.push_back(n->circulos[i].center);
					if (pts.size() >= k)
						return pts;
					else
						return find_all(n);
				}
			}
		}
		else
		{
			return n->objetos;
		}
	}

	vector<Point> knn_query(Point Q, int k)
	{
		vector<pair<double, Point>> ans;
		vector<Point> res = knn_search(root, Q, k);
		for (Point p : res) 
			ans.push_back(make_pair(0, p));
		for (pair<double, Point> &a : ans)
			a.first = euclidean_distance(a.second, Q);
		 sort(ans.begin(), ans.end());

		vector<Point> resp;
		cout << k << "nn: ";
		for (int i = 0; i < min(k, (int)ans.size()); ++i)
		{
			resp.push_back(ans[i].second);
			for(int j=0; j< ans[i].second.dimensiones.size(); ++j)
				cout << ans[i].second.dimensiones[j] <<",";
			cout << " ; ";
		}
		cout << endl;

		return resp;
	}
};

int main()
{
	Mtree t(500);
	/*t.insertar(Point{ 1, 1,1 });
	t.insertar(Point{ 2, 2 , 2 });
	t.insertar(Point{ 2.5, 2.5, 2.5 });
	t.insertar(Point{ 4, 4, 4 });
	t.insertar(Point{ 5, 5, 5 });
	t.insertar(Point{ 5, 1, 3 });
	t.insertar(Point{ 6, 6, 6 });
	t.insertar(Point{ 7, 9, 8 });
	t.insertar(Point{ 7, 5, 5 });
	t.insertar(Point{ 12, 3, 5 });
	t.insertar(Point{ 14, 13, 3 });
	t.insertar(Point{ 15, 13, 12 });
	t.insertar(Point{ 100,100, 100 });
	t.print();*/
	
	//vector<Point> r = t.knn_query(Point{ 99, 99, 99 }, 6);
		ifstream bunny("C:\\Users\\Adriana\\Dropbox\\EDA\\MTree\\MTree\\testdata.txt");
		//C:\\Users\\Adriana\\Dropbox\\EDA\\MTree\\MTree\\testdata.txt");
	cout << bunny.is_open() << endl;
	string line;

	vector<Point> puntos;
	while (getline(bunny, line))
	{
		vector<double> vec;
		stringstream ss;
		ss << line;
		double d; 
		while (ss >> d)
		{
				vec.push_back(d);
		}
		//
		t.insertar(Point(vec));
		puntos.push_back(Point(vec));

	}
	
	auto start = high_resolution_clock::now();
	vector<Point> r = t.knn_query(puntos[0], 500);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "milisegundos: " << duration.count() << endl;
	
	char c; cin >> c;
	return 0;
}