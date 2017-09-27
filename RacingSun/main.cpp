#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <glut.h>
#define _USE_MATH_DEFINES
#include <cmath> 
#include <time.h>
#include <iostream>

void draw();
void idle();
void resize(int w, int h);
void drawCube(double _x, double _y, double _z, int _w, int _l, int _h);
void keyDown(unsigned char, int, int);
void keyUp(unsigned char, int, int);
double lerp(double, double, double);

double lerp(double val, double target, double fraction)
{
	return val + (target - val) * fraction;
}

double floor_width = 6.5;
double floor_length = 10.5;

bool grid[13][22];

double ply_z = 0;
double tar_ply_x = 0;
double ply_x = 0;

double pi2 = M_PI * 2;

const int numberOfCubes = 35;
int cubesX[numberOfCubes], cubesY[numberOfCubes];

int main(int argc, char **argv)
{
	srand(time(NULL));

	glutInit(&argc, argv);

	glutInitWindowPosition(64, 64);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Solar System");

	// Init stuff
	/*glEnable(GL_LIGHTING);
	GLfloat diffuseLight[] = { .75, .75, .75, 1 };
	GLfloat lightPosition[] = { -1, -1, -1, 1 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);*/

	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			grid[i][j] = false;
		}
	}
	for (int i = 0; i < numberOfCubes; i++)
	{
		cubesX[i] = (rand() % 6) * (1 - (rand() % 2) * 2);
		cubesY[i] = 10 + ((rand() % 8) * (1 - (rand() % 2) * 2) + 2);
		grid[cubesX[i] + 6][cubesY[i]] = true;
	}
	

	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glutMainLoop();

	resize(800, 600);

	return 0;
}

void keyDown(unsigned char key, int x, int y)
{
	if (key == 'a' && tar_ply_x > -5)
	{
		tar_ply_x -= 1;
	}
	else if (key == 'd' && tar_ply_x < 5)
	{
		tar_ply_x += 1;
	}
}

void keyUp(unsigned char key, int x, int y)
{
	
}

void draw()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Draw Stuff
	glColor3d(0.7, 0.7, 0.7);
	glBegin(GL_QUADS);
	glVertex3d(floor_width, floor_length*2, -0.5);
	glVertex3d(floor_width, 0, -0.5);
	glVertex3d(-floor_width, 0, -0.5);
	glVertex3d(-floor_width, floor_length*2, -0.5);
	glEnd();

	glColor3d(0.2, 0.2, 0.2);
	glBegin(GL_LINES);
	for (int i = (-floor_width); i < (floor_width+1); i++)
	{
		glVertex3d(i-0.5, 0, -0.5);
		glVertex3d(i-0.5, floor_length*2, -0.5);
	}
	glEnd();

	drawCube(-6, 10.5, 0, 1, 21, 1);
	drawCube(6, 10.5, 0, 1, 21, 1);

	for (int i = 0; i < numberOfCubes; i++)
	{
		drawCube(cubesX[i], cubesY[i], 0, 1, 1, 1);
	}

	/*drawCube(-3.5, -4, 0, 2, 1, 1);
	drawCube(-2, -2, 0, 1, 5, 1);
	drawCube(0.5, -4, 0, 2, 1, 1);
	drawCube(2, -2, 0, 1, 5, 1);
	drawCube(-0.5, 0, 0, 2, 1, 1);
	drawCube(3.5, 0, 0, 2, 1, 1);*/

	glutSwapBuffers();
}

void drawCube(double _x, double _y, double _z, int _w, int _l, int _h)
{

	double w2 = 0.5 * _w, l2 = 0.5 * _l, h2 = 0.5 * _h;
	glColor3d(0.85, 0.85, 0.85);
	glBegin(GL_QUADS);
	// Front
	glVertex3d(_x + w2, _y + l2, _z + h2);
	glVertex3d(_x + w2, _y + l2, _z - h2);
	glVertex3d(_x - w2, _y + l2, _z - h2);
	glVertex3d(_x - w2, _y + l2, _z + h2);
	// Back
	glVertex3d(_x + w2, _y - l2, _z + h2);
	glVertex3d(_x + w2, _y - l2, _z - h2);
	glVertex3d(_x - w2, _y - l2, _z - h2);
	glVertex3d(_x - w2, _y - l2, _z + h2);
	// Right
	glVertex3d(_x + w2, _y + l2, _z + h2);
	glVertex3d(_x + w2, _y + l2, _z - h2);
	glVertex3d(_x + w2, _y - l2, _z - h2);
	glVertex3d(_x + w2, _y - l2, _z + h2);
	// Left
	glVertex3d(_x - w2, _y + l2, _z + h2);
	glVertex3d(_x - w2, _y + l2, _z - h2);
	glVertex3d(_x - w2, _y - l2, _z - h2);
	glVertex3d(_x - w2, _y - l2, _z + h2);
	// Top
	glVertex3d(_x + w2, _y + l2, _z + h2);
	glVertex3d(_x + w2, _y - l2, _z + h2);
	glVertex3d(_x - w2, _y - l2, _z + h2);
	glVertex3d(_x - w2, _y + l2, _z + h2);
	glEnd();

	glColor3d(0.2, 0.2, 0.2);
	glBegin(GL_LINE_STRIP);
	glVertex3d(_x + w2, _y + l2, _z + h2);
	glVertex3d(_x + w2, _y + l2, _z - h2);
	glVertex3d(_x - w2, _y + l2, _z - h2);
	glVertex3d(_x - w2, _y + l2, _z + h2);
	glVertex3d(_x + w2, _y + l2, _z + h2);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3d(_x + w2, _y - l2, _z + h2);
	glVertex3d(_x + w2, _y - l2, _z - h2);
	glVertex3d(_x - w2, _y - l2, _z - h2);
	glVertex3d(_x - w2, _y - l2, _z + h2);
	glVertex3d(_x + w2, _y - l2, _z + h2);
	glEnd();
	glBegin(GL_LINES);
	glVertex3d(_x + w2, _y + l2, _z + h2);
	glVertex3d(_x + w2, _y - l2, _z + h2);
	glVertex3d(_x + w2, _y + l2, _z - h2);
	glVertex3d(_x + w2, _y - l2, _z - h2);
	glVertex3d(_x - w2, _y + l2, _z + h2);
	glVertex3d(_x - w2, _y - l2, _z + h2);
	glVertex3d(_x - w2, _y + l2, _z - h2);
	glVertex3d(_x - w2, _y - l2, _z - h2);
	glEnd();
}

void idle()
{
	ply_x = lerp(ply_x, tar_ply_x, 0.45);
	ply_z += 0.05;
	if (ply_z > 20.5)
	{
		ply_z -= 20.5;
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 21; j++)
			{
				grid[i][j] = false;
			}
		}
		for (int i = 0; i < numberOfCubes; i++)
		{
			cubesX[i] = (rand() % 6) * (1 - (rand() % 2) * 2);
			cubesY[i] = 10 + ((rand() % 8) * (1 - (rand() % 2) * 2) + 2);
			grid[cubesX[i] + 6][cubesY[i]] = true;
		}
	}
	glutPostRedisplay();

	if (grid[((int)tar_ply_x + 6)][(int)ceil(ply_z)])
	{
		tar_ply_x = 0;
		ply_x = 0;
		ply_z = 0;
	}

	resize(800, 600);
}

void resize(int w, int h)
{
	if (h == 0)
		h = 1;

	double ratio = 1.0 * w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(90, ratio, 0.1, 50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(ply_x, ply_z, 0, ply_x, ply_z + 1, 0.0, 0.0f, 0.0f, 1.0f);
}