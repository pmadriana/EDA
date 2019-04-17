#include "Node.h"
#include <vector>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>
#include<GL/glut.h>
#define dimension 3

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


class KdTree3D
{
public:
	Node * root;
	vector<Point> points;
	vector<double> m_x, m_y, m_z;
	//double top_limit, bot_limit, left_limit, right_limit;
	struct Compare {
		int dim;
		bool operator() (Point &a, Point &b) {
			return (a.dim[dim] < b.dim[dim]);
		}
	};

	Compare compare;
	KdTree3D(std::vector<Point> &points)
	{
		this->points = points;
		Build(0, points.size(), 0, NULL);
	}

	void find_x(vector<Point> &points)
	{
		sort(points.begin() + 0, points.begin() + points.size(), comp_x);
		m_x.push_back(points[0].dim[0]);
		m_x.push_back(points[points.size()-1].dim[0]);
	}
	void find_y(vector<Point> &points)
	{
		sort(points.begin() + 0, points.begin() + points.size(), comp_y);
		m_y.push_back(points[0].dim[1]);
		m_y.push_back(points[points.size() - 1].dim[1]);

	}
	void find_z(vector<Point> &points)
	{
		sort(points.begin() + 0, points.begin() + points.size(), comp_z);
		m_z.push_back(points[0].dim[2]);
		m_z.push_back(points[points.size() - 1].dim[2]);
	}

	Node * Build( int begin, int end, int depth, Node *prev)
	{

		if (end - begin <= 0)
			return 0;

		int ax = depth % dimension;
		
		compare.dim = ax;
		sort(points.begin() + begin, points.begin() + end, compare); //K
		
		int half = (begin + end) / 2;
		Node * median = new Node(points[half]);
		median->prev_m = prev;
		median->left = Build( begin, half, depth + 1, median);
		median->right = Build( half + 1, end, depth + 1, median);

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

	void PrintPapa(Node * root, int cont)
	{
		//cout << "root: " << root->p.getPosition().x << ", " << root->p.getPosition().y << ", " << root->p.getPosition().z << endl;
		if (root == 0)
		{
			return;
		}

		//cout << root->right->p.getPosition().x << root->right->p.getPosition().y << " l " << root->left->p.getPosition().x << root->left->p.getPosition().y << endl;
		PrintPapa(root->right, cont + 1);
		if (root->prev_m != NULL)
			std::cout << root->p.dim[0] << root->p.dim[1] << root->p.dim[2] << "es "<<root->prev_m->p.dim[0] << root->prev_m->p.dim[1]<< std::endl;
		PrintPapa(root->left, cont + 1);
	}

	void Draw_cubo(Point* tlc, Point* brc)
	{
		glLineWidth(3);
		glBegin(GL_LINES);
		glColor3d(0.5, 0.5, 0.5);
		glVertex3d(tlc->dim[0], tlc->dim[1], tlc->dim[2]);
		glVertex3d(tlc->dim[0], brc->dim[1], tlc->dim[2]);

		glVertex3d(tlc->dim[0], tlc->dim[1], tlc->dim[2]);
		glVertex3d(tlc->dim[0], tlc->dim[1], brc->dim[2]);

		glVertex3d(tlc->dim[0], tlc->dim[1], tlc->dim[2]);
		glVertex3d(brc->dim[0], tlc->dim[1], tlc->dim[2]);

		glVertex3d(brc->dim[0], brc->dim[1], brc->dim[2]);
		glVertex3d(tlc->dim[0], brc->dim[1], brc->dim[2]);

		glVertex3d(brc->dim[0], brc->dim[1], brc->dim[2]);
		glVertex3d(brc->dim[0], tlc->dim[1], brc->dim[2]);

		glVertex3d(brc->dim[0], brc->dim[1], brc->dim[2]);
		glVertex3d(brc->dim[0], brc->dim[1], tlc->dim[2]);

		//

		glVertex3d(tlc->dim[0], brc->dim[1], brc->dim[2]);
		glVertex3d(tlc->dim[0], tlc->dim[1], brc->dim[2]);

		glVertex3d(tlc->dim[0], brc->dim[1], brc->dim[2]);
		glVertex3d(tlc->dim[0], brc->dim[1], tlc->dim[2]);

		glVertex3d(brc->dim[0], brc->dim[1], tlc->dim[2]);
		glVertex3d(tlc->dim[0], brc->dim[1], tlc->dim[2]);

		glVertex3d(brc->dim[0], brc->dim[1], tlc->dim[2]);
		glVertex3d(brc->dim[0], tlc->dim[1], tlc->dim[2]);
		//
		glVertex3d(tlc->dim[0], tlc->dim[1], brc->dim[2]);
		glVertex3d(brc->dim[0], tlc->dim[1], brc->dim[2]);

		glVertex3d(tlc->dim[0], tlc->dim[1], brc->dim[2]);
		glVertex3d(brc->dim[0], tlc->dim[1], brc->dim[2]);

		glVertex3d(brc->dim[0], tlc->dim[1], brc->dim[2]);
		glVertex3d(brc->dim[0], tlc->dim[1], tlc->dim[2]);

		glEnd();
		glLineWidth(1);
	}

	void Draw(Node* root, vector<Point> points, int depth, double top_limit, double bot_limit, double left_limit, double right_limit) {
		// 10, -10, 10,-10
		if (root == 0)
		{
			return;
		}

		glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3d(255, 255, 255);
		glutSolidCube(20);
		glPopMatrix();

		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3d(0, 255, 0);

		//	glVertex3f(0, -0.1, 0); glVertex3f(19, -0.1, 0);
		for (int i = 0; i < points.size(); i++) {
			glVertex3f(points[i].dim[0], points[i].dim[1], points[i].dim[2]);
			//cout << A->points[i]->getPosition().D[0] << " " << A->points[i]->getPosition().D[1] << " " << A->points[i]->getPosition().D[2] << endl;
		}
		glEnd();

		int ax = depth % dimension;
		glColor3d(255, 255, 255);
		glBegin(GL_LINES);
		//x
		if (ax == 0) {  //y z 
			glColor3d(255, 0, 0);
			if (root->prev_m == NULL)
			{
				glVertex3d(root->p.dim[0], top_limit, left_limit);  //y
				glVertex3d(root->p.dim[0], bot_limit, left_limit); //y

				glVertex3d(root->p.dim[0], bot_limit, right_limit);  //y
				glVertex3d(root->p.dim[0], top_limit, right_limit); //y

				glVertex3d(root->p.dim[0], top_limit, left_limit);  //z
				glVertex3d(root->p.dim[0], top_limit, right_limit); //z

				glVertex3d(root->p.dim[0], bot_limit, left_limit);  //z
				glVertex3d(root->p.dim[0], bot_limit, right_limit); //z*/

			}
			else
			{

				glVertex3d(root->p.dim[0], root->prev_m->p.dim[1], root->p.dim[2]);  //pt origen
				if (root->p.dim[1] > root->prev_m->p.dim[1]) {
					glVertex3d(root->p.dim[0], top_limit, root->p.dim[2]); //hasta ymax

					glVertex3d(root->p.dim[0], top_limit, root->p.dim[2]);  //z
					glVertex3d(root->p.dim[0], top_limit, root->prev_m->p.dim[2]); //z
				}
				glVertex3d(root->p.dim[0], bot_limit, root->p.dim[2]); //hasta ymin
				glVertex3d(root->p.dim[0], bot_limit, root->p.dim[2]);  //z
				glVertex3d(root->p.dim[0], bot_limit, root->prev_m->p.dim[2]); //z

			}
		}
		else if (ax == 1) { //x z
			glColor3d(0, 255, 0);
			/*	glVertex3d(root->prev_m->p.dim[0], root->p.dim[1], top_limit);
				if (root->p.dim[0] > root->prev_m->p.dim[0]) {
					glVertex3d(left_limit, root->p.dim[1], top_limit);
					glVertex3d(left_limit, root->p.dim[1], bot_limit);
					glVertex3d(root->prev_m->p.dim[0], root->p.dim[1], bot_limit);
				}
				else
				{
					glVertex3d(right_limit, root->p.dim[1], top_limit);
					glVertex3d(right_limit, root->p.dim[1], bot_limit);
					glVertex3d(root->prev_m->p.dim[0], root->p.dim[1], right_limit);
				} jeje gl cuadds*/


			glVertex3d(root->prev_m->p.dim[0], root->p.dim[1], bot_limit);  //pt origen
			if (root->p.dim[0] > root->prev_m->p.dim[0]) {
				glVertex3d(left_limit, root->p.dim[1], bot_limit);  //xmax

				glVertex3d(left_limit, root->p.dim[1], bot_limit); //z
				glVertex3d(left_limit, root->p.dim[1], top_limit); //Z
			}
			else {
				glVertex3d(right_limit, root->p.dim[1], bot_limit); //x 
				glVertex3d(right_limit, root->p.dim[1], top_limit);//z
				glVertex3d(right_limit, root->p.dim[1], bot_limit);//z
			}
			//////////////
			glVertex3d(root->prev_m->p.dim[0], root->p.dim[1], top_limit);  //pt origen
			if (root->p.dim[0] > root->prev_m->p.dim[0]) {
				glVertex3d(left_limit, root->p.dim[1], top_limit);  //xmax

				glVertex3d(root->prev_m->p.dim[0], root->p.dim[1], top_limit); //z
				glVertex3d(root->prev_m->p.dim[0], root->p.dim[1], bot_limit); //Z
			}
			else {
				glVertex3d(right_limit, root->p.dim[1], top_limit); //x 
				glVertex3d(root->prev_m->p.dim[0], root->p.dim[1], bot_limit);//z
				glVertex3d(root->prev_m->p.dim[0], root->p.dim[1], top_limit);//z
			}

		}
		else
		{
			glColor3d(0, 0, 255); //x y
			glVertex3d(root->prev_m->prev_m->p.dim[0], root->p.dim[1], root->p.dim[2]);  //x
			if (root->p.dim[0] > root->prev_m->prev_m->p.dim[0]) {
				glVertex3d(left_limit, root->p.dim[1], root->p.dim[2]);  //x

				glVertex3d(left_limit, root->p.dim[1], root->p.dim[2]); //y
				glVertex3d(left_limit, root->prev_m->p.dim[1], root->p.dim[2]); //y
			}
			glVertex3d(right_limit, root->p.dim[1], root->p.dim[2]);

			glVertex3d(right_limit, root->p.dim[1], root->p.dim[2]); //y
			glVertex3d(right_limit, root->prev_m->p.dim[1], root->p.dim[2]); //y
		}


		glEnd();

		Draw(root->left, points, depth + 1, top_limit, bot_limit,  left_limit,  right_limit);
		Draw(root->right, points, depth + 1, top_limit, bot_limit, left_limit, right_limit);
	}
};
