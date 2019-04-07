#ifndef Octree_H
#define Octree_H

#include <cstddef>
#include <vector>
#include "OctreePoint.h"

#include <iostream>

using namespace std;
int cont = 0;
class Octree {
public:

	Vec3 origin;
	Vec3 halfDimension;
	

	Octree *children[8];
	vector<OctreePoint> *data;
	vector<OctreePoint> dat;

	/*
			hijos:	0 1 2 3 4 5 6 7
			x:      - - - - + + + +  
			y:      - - + + - - + +
			z:      - + - + - + - +
	 */

public:

	Octree(const Vec3& origin, const Vec3& halfDimension)
		: origin(origin), halfDimension(halfDimension), data(NULL) {
		// no hay hijos al principio
		for (int i = 0; i < 8; ++i)
			children[i] = NULL;
	}

	

	~Octree() {
		for (int i = 0; i < 8; ++i)
			delete children[i];
	}

	int getOctant(const Vec3& point) const { 
		int oct = 0;
		if (point.x >= origin.x) oct |= 4; //0100  
		if (point.y >= origin.y) oct |= 2; //0010
		if (point.z >= origin.z) oct |= 1; //0001

		//cout << "Octante en el que esta el punto:  " << point.D[0]<< point.D[1] << point.D[2]<<" : " << oct <<endl;
		return oct;
	}

	bool isLeafNode() const { //si no tenemos hijo return 1, osea estamos vacios en ese octante
		return children[0] == NULL;
	
	}


	void insert(OctreePoint* point, int &cont ) {
		//int octante = getOctantContainingPoint(point->getPosition());
		if (isLeafNode()) { 
			if (data == NULL) { //si estamos vacios pongo el punto y ya, sin partir
				data = point;
				
			//	cout << "Octante en el que esta el punto:  " << point->getPosition().D[0] << point->getPosition().D[1] << point->getPosition().D[2] << " : " << getOctant(point->getPosition()) << endl;
				return;
			}
			

			else { //si tiene un punto entonces parto y agrego 8 hijos
				// y inserto la data antigua con la nueva (reacomodar)
				cout << "SE DIVIDE " << endl;
				cout << "Nueva dimension: " << ((halfDimension *.5f).D[0]) * 2<< ", Origen: " << (halfDimension * .5f).D[0]<<endl;
				cout << "Octante en el que esta el punto:  " << point->getPosition().D[0] << ", " << point->getPosition().D[1] << ", "<<point->getPosition().D[2] << " : " << getOctant(point->getPosition()) << endl;
				cont++;
				// guardar anterior punto
				OctreePoint *oldPoint = data;
				data = NULL;

				// dividir el nodo actual en 8
				for (int i = 0; i < 8; ++i) {
					// calcular nuevo cubito 
					Vec3 newOrigin = origin;
					newOrigin.x += halfDimension.x * (i & 4 ? .5f : -.5f); // si es + o - dividir 
					newOrigin.y += halfDimension.y * (i & 2 ? .5f : -.5f);
					newOrigin.z += halfDimension.z * (i & 1 ? .5f : -.5f);
					children[i] = new Octree(newOrigin, halfDimension*.5f); /// el origen y las nuevas dim de nuevo cubo, aqui se crea practicamente los cubos
					//cout << newOrigin.D[0] << " " << newOrigin.D[0] << " " << newOrigin.D[0] << " half dim: " << (halfDimension *.5f).D[0];
				}
			

				// parte recursiva donde reorganizamos los puntos del mismo octante
				children[getOctant(oldPoint->getPosition())]->insert(oldPoint, cont);
				children[getOctant(point->getPosition())]->insert(point,  cont);
			}
		}
		else {
			// insertar recursivamente en el octante correcto
			cout << "Octante en el que esta el punto:  " << point->getPosition().D[0] << point->getPosition().D[1] << point->getPosition().D[2] << " : " << getOctant(point->getPosition()) << endl;
			int octant = getOctant(point->getPosition());
			children[octant]->insert(point, cont);
		}
	}


};


	



#endif
