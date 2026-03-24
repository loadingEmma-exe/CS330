// OpenGLpopUpMenus.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "glut.h"
#include <stdio.h>

void init(void)
{
	glOrtho(-5, 5, -5, 5, -5, 5);//makes 3D, parameters 2 for each axis
	glMatrixMode(GL_MODELVIEW);//makes it able to see it in 3D
}

void cube() {

	//top face (y 1.0f)
	glColor3f(0.0f, 1.0f, 0.0f);//green

	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	//Bottom face (y -1.0)
	glColor3f(1.0f, 0.5f, 0.0f);//orange

	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	//front face (z 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f); //red

	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	//back face (z - 1.0
	glColor3f(1.0f, 0.5f, 0.5f); //pink

	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	//left face (x -1.0)
	glColor3f(0.0, 0.0, 1.0);//blue

	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	//right face (x 1.0)
	glColor3f(1.0f, 0.7, 0.2); //yellow

	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
}

void drawColorCube() {
	glBegin(GL_QUADS); //begin drawing the color cube with 6 quads
	cube();
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//add clearing depth buffer bit
	glEnable(GL_DEPTH_TEST);//test in the z direction, which one is in front of the other

	glPushMatrix();

	glRotatef(30.0, 0.0, 1.0, 0.0);//for cube
	glRotatef(30.0, 1.0, 0.0, 0.0);//for cube

	drawColorCube();

	glFlush();
}

//
void main_menu(int value) {
	if (value == 1) {
		printf("White Background\n");
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glutPostRedisplay();
	}
	else if (value == 2) {
		printf("Black Background\n");
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glutPostRedisplay();
	}
}
//

void main(int argc, char** argv)
{
	glutInitWindowSize(640, 640);//change window size in pixels
	glutInitWindowPosition(50, 50);//change window position

	glutCreateWindow("Color Cube With Menu");

	glutCreateMenu(main_menu);
	glutAddMenuEntry("White Background", 1);
	glutAddMenuEntry("Black Background", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

