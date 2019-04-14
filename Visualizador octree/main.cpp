#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include<GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Octree.h"
#include <time.h>
#define KEY_ESC 27
using namespace std;

std::vector<Vec3> points;
Octree *octree;
OctreePoint *octreePoints;
double dimX = 20.0;
double dimY = 20.0;
double dimZ = 20.0;
const int nPoints = 50;
////////////////////INTERFAZ
int mx = 0;
int my = 0;

float ax = 0.0;
float ay = 0.0;
float speed = 0.1;

bool r = false;

void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mx = x;
		my = y;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		r = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		r = false;
	}
}
void OnMouseMotion(int x, int y)
{
	int dx = mx - x;
	int dy = my - y;

	mx = x;
	my = y;

	ax += dx * speed;
	ay += dy * speed;
}



void idle() { // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint_Octree(void) {

	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 500.0);

	glTranslatef(0, 0, -100.0);
	glRotatef(ax, 0, 1, 0);
	glRotatef(ay, 1, 0, 0);

	octree->draw(octree);

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}


void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glEnable(GL_DEPTH_TEST);
	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}

void create_window_Octree() {
	//Inicializacion de la GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("OcTree"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint_Octree);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);
}

/////////////////

float random() // Random number entre [] 
{ 

	float  r = -dimX + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((dimX-1) +dimX +1 )));//(rand() % 11) - 5 ;
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

	octree = new Octree(Vec3(0, 0, 0), Vec3(dimX, dimY, dimZ)); //diametro 10 origen(000)
	//octree->inicio();
	for (int i = 0; i < nPoints; ++i) {

		points.push_back(randVec3());
	}
	/*points.push_back(Vec3(4, 4, 3));
	points.push_back(Vec3(-1, 2, 4));
	points.push_back(Vec3(3, -4, 2));
	points.push_back(Vec3(-2, -2, -1));
	points.push_back(Vec3(-1,- 3, -1));
	points.push_back(Vec3(-4, -4, -4));
	points.push_back(Vec3(-3.5, -3.5, -3.5));*/
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
//	cout << "regiones " <<( cont*8) << endl;
	//cout << octree->children[6]->data->getPosition().D[0];

	
}






int main(int argc, char **argv) {
	init();
	//testOctree();

	glutInit(&argc, argv);
	create_window_Octree();
	//create_window_kdtree();

	//qt = new quadTree();
	glutMainLoop(); //bucle de rendering
/*	int z;
	cin >> z;*/
	return 0;
}
