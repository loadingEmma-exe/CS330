// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//camera movement-cyrstall ball interface using arrow keys

#include <math.h>
#include  "glut.h"

int windowWidth = 1024; //init window width
int windowHeight = 768; //init window height

float aspect = float(windowWidth) / float(windowHeight);
float spin = 0.0; //init spin to 0, for no spin

bool rotating = false; //init rotating to false, for not rotating

double eye[] = { 0,0,1 }; //define the eye axis of the camera to be the z axis
double center[] = { 0,0,0 }; //define center of the image to be the orgin
double up[] = { 0,1,0 }; //define the up axis of the camera to be the y axis

void crossProduct(double a[], double b[], double c[]) 
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[]) // takes in a point a
{ //this function finds the length of the vector
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}

void rotatePoint(double a[], double theta, double p[]) // rotation point p, with angle theta, with direction a
{ //this function rotates around any axis
    double temp[3];

    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];

    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];

    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);

    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];

    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];
}

void Left()
{ //keyboard interaction for left arrow key
    double speed = 3.1415 / 8;
    rotatePoint(up, speed, eye);
}

void Right()
{ //keyboard interaction for right arrow key
    double speed = 3.1415 / 8;
    rotatePoint(up, -speed, eye);
}

void Up()
{ //keyboard interaction for up arrow key
    double speed = 3.1415 / 8;
    double rot_axis[3];
    double look[3];

    look[0] = -eye[0];
    look[1] = -eye[1];
    look[2] = -eye[2];

    crossProduct(look, up, rot_axis);
    normalize(rot_axis);
    rotatePoint(rot_axis, speed, eye);
    rotatePoint(rot_axis, speed, up);
}

void Down()
{ //keyboard interactions for the down arrow key
    double speed = 3.1415 / 8;
    double rot_axis[3];
    double look[3];

    look[0] = -eye[0];
    look[1] = -eye[1];
    look[2] = -eye[2];

    crossProduct(look, up, rot_axis);
    normalize(rot_axis);
    rotatePoint(rot_axis, -speed, eye);
    rotatePoint(rot_axis, -speed, up);
}

void specialKeys(int key, int x, int y)
{ //assigns keys for keyboard interaction
    switch (key)
    {
    case GLUT_KEY_LEFT: 
        Left(); 
        break;
    case GLUT_KEY_RIGHT:
        Right();
        break;
    case GLUT_KEY_UP:
        Up(); 
        break;
    case GLUT_KEY_DOWN:  
        Down(); 
        break;
    }

    glutPostRedisplay();
}

void display(void)
{ //displays our current matrix
    //setup
    glClearColor(0.0, 0.0, 0.0, 0.0); 
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]); //defines camera view
    
    //matrix
    glPushMatrix(); //pushes matrix to stack
    glutWireTeapot(0.25); //draws teapot
    glPopMatrix(); //pop matrix from stack
    glFlush(); 
    glutSwapBuffers();
}

void main(int argc, char** argv)
{
    glutInitWindowSize(windowWidth, windowHeight); //init window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //init display mode
    glutInitWindowPosition(50, 50); //init position
    glutCreateWindow("Cyrstall Ball Interface Example"); //window name

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, aspect, 0, 10);
    glutDisplayFunc(display); //allows keyboard interaction
    glutSpecialFunc(specialKeys); //allows keyboard interaction
    glutMainLoop();
}