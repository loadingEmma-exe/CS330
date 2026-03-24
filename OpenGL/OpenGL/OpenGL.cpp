// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "glut.h"

double speed = 0.1f;
float translation[3] = { 0.0f, 0.0f, 0.0f };

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

void square() {
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
}

void drawColorCube() {
	glBegin(GL_QUADS); //begin drawing the color cube with 6 quads
	cube();
	glEnd();
}

void Left() { //left arrow key, to move the color cube in the +ve X direction
	translation[0] -= speed;
}

void Right() { //right arrow key, to move the color cube in the -ve X direction
	translation[0] += speed;
}

void Up() { //up arrow key, to move the color cube in the +ve Y direction
	translation[1] += speed;
}

void Down() { //down arrow key, to move the color cube in the -ve direction
	translation[1] -= speed;
}

void specialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: Left(); break;
		case GLUT_KEY_RIGHT: Right(); break;
		case GLUT_KEY_UP: Up(); break;
		case GLUT_KEY_DOWN: Down(); break;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'f': //f, to move the color cube in the +ve Z direction
		translation[2] += speed;
		break;
	case 'b': //b, to move the color cube in the -ve Z direction
		translation[2] -= speed;
		break;
	}

	glutPostRedisplay();
}

void init(void)
{
	glOrtho(-5, 5, -5, 5, -5, 5);//makes 3D, parameters 2 for each axis
	glMatrixMode(GL_MODELVIEW);//makes it able to see it in 3D
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//add clearing depth buffer bit
	glEnable(GL_DEPTH_TEST);//test in the z direction, which one is in front of the other

	glPushMatrix();
		glTranslatef(translation[0], translation[1], translation[2]);
		glRotatef(30.0, 0.0, 1.0, 0.0);//for cube
		glRotatef(30.0, 1.0, 0.0, 0.0);//for cube
	drawColorCube();
	glPopMatrix();

	glFlush();
}

void main(int argc, char** argv)
{
	glutInitWindowSize(640, 640);//change window size in pixels
	glutInitWindowPosition(50, 50);//change window position

	glutCreateWindow("Emma Raymond");
	init();
	glutDisplayFunc(display);

	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

}

