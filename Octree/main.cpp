#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Octree.h"
#include <time.h>
#include<GL/glut.h>

using namespace std;

std::vector<Vec3> points;
Octree *octree;
OctreePoint *octreePoints;



float random() // Random number entre [] 
{ 

	float  r = -5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4 +5 +1 )));//(rand() % 11) - 5 ;
	while (r == 0) {
		r = (rand() % 10) - 5;//-1.f + (2.f*rand()) * (1.f / RAND_MAX);
	}
	return r;
}

Vec3 randVec3() // Random vector 
{
	return Vec3(random(), random(), random());
}



void init() {

	octree = new Octree(Vec3(0, 0, 0), Vec3(5, 5, 5)); //diametro 10 origen(000)
	//octree->inicio();
	const int nPoints = 7;
	/*for (int i = 0; i < nPoints; ++i) {

		points.push_back(randVec3());
	}*/
	points.push_back(Vec3(4, 4, 3));
	points.push_back(Vec3(-1, 2, 4));
	points.push_back(Vec3(3, -4, 2));
	points.push_back(Vec3(-2, -2, -1));
	points.push_back(Vec3(-1,- 3, -1));
	points.push_back(Vec3(-4, -4, -4));
	points.push_back(Vec3(-3.5, -3.5, -3.5));
	cout << "puntos:" << endl;
	for (int i = 0; i < nPoints; ++i) {
		cout << points[i].D[0] << ", " << points[i].D[1] << ", " << points[i].D[2] << endl;
	}
	cout << "se crearon: " << nPoints << " puntos" << endl;

	//Insertar puntos en octree
	octreePoints = new OctreePoint[nPoints];
	int cont = 0;
	for (int i = 0; i < nPoints; i++) {
		octreePoints[i].setPosition(points[i]);
		cout << "Proceso del punto: " << i << endl;
		octree->insert(octreePoints+i, cont);
		cout << "termino proceso " << endl;
		cout << endl;
	}
//	cout << "se dividio: " << cont << endl;
	cout << "regiones " <<( cont*8) << endl;
	//cout << octree->children[6]->data->getPosition().D[0];
	
}






int main(int argc, char **argv) {
	init();
	//testOctree();


	
}
