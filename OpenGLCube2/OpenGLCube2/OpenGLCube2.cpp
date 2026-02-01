// error writing to program database 
// check for insufficient disk space, invalid path, or insufficient privilege

//disk space plenty, not an invalid path, or insuffiencient privilege
//clean solution, build, run

#include "glut.h"

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

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//add clearing depth buffer bit
	glEnable(GL_DEPTH_TEST);//test in the z direction, which one is in front of the other

	glPushMatrix();

	glRotatef(30.0, 0.0, 1.0, 0.0);//for cube
	glRotatef(30.0, 1.0, 0.0, 0.0);//for cube

	drawColorCube();

	glPopMatrix();

	glTranslatef(2.0, 2.0, 0.0);
	glRotatef(-30.0, 0.0, 1.0, 0.0);//for cube
	glRotatef(-30.0, 1.0, 0.0, 0.0);//for cube
	drawColorCube();

	glFlush();
}

void main(int argc, char** argv)
{
	glutInitWindowSize(640, 640);//change window size in pixels
	glutInitWindowPosition(50, 50);//change window position

	glutCreateWindow("Emma Raymond");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

