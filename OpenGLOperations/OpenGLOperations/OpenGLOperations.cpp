// OpenGLOperations.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdlib.h>
#include "glut.h"

void init(void) { //intializer function
	gluOrtho2D(-5, 5, -5, 5); //
}

void drawSquare() {
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 0.5);

	glBegin(GL_POLYGON);

	drawSquare();
	glPushMatrix();
		glTranslatef(0, 1, 0);
		glScalef(0.5, 0.5, 1);
		drawSquare();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 2, 0);
		glScalef(0.5, 0.5, 1);
		drawSquare();
	glPopMatrix();

	glEnd();
	glFlush();
}

void main(int argc, char** argv) 
{
	glutCreateWindow("OpenGlOperations");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
