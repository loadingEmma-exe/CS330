// OpenGLProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

//*****************************
// Includes
//*****************************

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "glut.h"

extern "C"
{
    #include "glm.h"
}

//*****************************
// Global Variables
//*****************************

//FOR IMPORTS
GLMmodel* pmodel1 = NULL;
GLMmodel* pmodel2 = NULL;
GLMmodel* pmodel3 = NULL;
GLMmodel* pmodel4 = NULL;

//FOR GLCALLLIST
GLuint importRotate;
GLuint room;
GLuint table;
GLuint door;
GLuint objects;

//INIT WINDOW
int windowWidth = 1024; //init window width
int windowHeight = 768; //init window height
int doorHinge = 0;

//ROOM MEASURES
int x = -3;
int y = -3;
int z = -9;

//ROTATE
float speed = 0.1f;
bool open = false;
int angle;

float aspect = float(windowWidth) / float(windowHeight);
float spin = 0.0; //init spin to 0, for no spin

bool rotating = false; //init rotating to false, for not rotating

//TRANSLATIONS
double eye[] = { 0, 1, -2}; //define the eye axis of the camera to be the z axis
double center[] = { 0, 1, 0 }; //define center of the image to be the orgin
double up[] = { 0, 1, 0 }; //define the up axis of the camera to be the y axis

float translation[3] = { 0.0f, 0.0f, 0.0f }; //define translation of net movement

//Setting White Light Source RGBA

GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 },//color //comes from below the back wall
light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 },
light_specular[] = { 0.8, 0.8, 0.8, 0.8 },
light_position[] = { x, -y, -z, 1.0 }; //position

GLfloat light_ambient2[] = { 1.0, 1.0, 1.0, 1.0 },//color //comes from above the doorway
light_diffuse2[] = { 1.0, 1.0, 1.0, 1.0 },
light_specular2[] = { 0.8, 0.8, 0.8, 0.8 },
light_position2[] = { 0.7, 0.7, 0.7, 1.0 }; //position

//Setting materials for object1 //WALLS

GLfloat material_ambient[] = { 1, 1, 0.8, 1.0 }, //low light color
material_diffuse[] = { 1, 1, 1, 1.0 }, //base color
material_specular[] = { 0, 0, 0, 1.0 }, //highlight
material_shininess = 10;

//Setting materials for object2

GLfloat material_ambient2[] = { 0, 0, 0, 0 }, //low light color
material_diffuse2[] = { 0, 0, 0, 0}, //base color
material_specular2[] = { 0, 0, 0, 0 }, //highlight
material_shininess2 = 1;

//Setting materials for object3

GLfloat material_ambient3[] = { 0.5, 0.5, 0.5, 1.0 }, //low light color
material_diffuse3[] = { 0, 0, 0, 0 }, //base color
material_specular3[] = { 0.5, 0.5, 0.5, 1.0 }, //hig
material_shininess3 = 100;

//*****************************
// Setting Material Props
//*****************************

void set_material_props() //diffuse
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);
}

void set_material_props2()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular2);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess2);
}

void set_material_props3()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse3);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular3);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess3);
}

//*****************************
// Setting Light Props
//*****************************

void set_light_props()
{
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glEnable(GL_LIGHT1);

    glEnable(GL_LIGHTING);
}

void set_light_props2()
{
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
    glEnable(GL_LIGHT2);

    glEnable(GL_LIGHTING);
}

//*****************************
// Math
//*****************************

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

//*****************************
// Imported Objects
//*****************************

void drawmodelSoccerball(void) {
    if (!pmodel1)
    {
        pmodel1 = glmReadOBJ((char*)"data/soccerball.obj");
        if (!pmodel1) {
            exit(0);
        }
        glmUnitize(pmodel1);
        glmFacetNormals(pmodel1);
        glmVertexNormals(pmodel1, 90.0);
    }
    glmDraw(pmodel1, GLM_SMOOTH | GLM_MATERIAL);
}

void drawmodel_rosevase(void)
{
    if (!pmodel2)
    {
        pmodel2 = glmReadOBJ((char*)"data/rose+vase.obj");
        if (!pmodel2) {
            exit(0);
        }
        glmUnitize(pmodel2);
        glmFacetNormals(pmodel2);
        glmVertexNormals(pmodel2, 90.0);
    }
    glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);
}

void drawmodelAl(void) {
    if (!pmodel3)
    {
        pmodel3 = glmReadOBJ((char*)"data/al.obj");
        if (!pmodel3) {
            exit(0);
        }
        glmUnitize(pmodel3);
        glmFacetNormals(pmodel3);
        glmVertexNormals(pmodel3, 90.0);
    }
    glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL);
}

void drawmodelDolphins(void) {
    if (!pmodel4)
    {
        pmodel4 = glmReadOBJ((char*)"data/dolphins.obj");
        if (!pmodel4) {
            exit(0);
        }
        glmUnitize(pmodel4);
        glmFacetNormals(pmodel4);
        glmVertexNormals(pmodel4, 90.0);
    }
    glmDraw(pmodel4, GLM_SMOOTH | GLM_MATERIAL);
}

void drawImportRotate()
{
    //Rose vase - imported
    glPushMatrix();
    glScalef(0.1, 0.1, 0.1);
    drawmodel_rosevase();
    glPopMatrix();
}

void TimerRotate(int value)
{
    spin = spin + 1;
    if (spin > 360.0) {
        spin = spin - 360.0;
    }
    glutPostRedisplay();
    glutTimerFunc(30, TimerRotate, 0);
}

void Timer(int value) {
    if (open && doorHinge <= 90) {
        doorHinge += 5;
    }
    else if (!open && doorHinge >= 0) {
        doorHinge -= 5;
    }

    glutPostRedisplay();
    glutTimerFunc(30, Timer, 0);
}

//*****************************
// Camera Movement
//*****************************

void LeftCamera()
{ //keyboard interaction for left arrow key
    double speed = 3.1415 / 32;

    center[0] -= eye[0];
    center[1] -= eye[1];
    center[2] -= eye[2];

    rotatePoint(up, speed, center); //was eye

    center[0] += eye[0];
    center[1] += eye[1];
    center[2] += eye[2];
}

void RightCamera()
{ //keyboard interaction for right arrow key
    double speed = 3.1415 / 32;

    center[0] -= eye[0];
    center[1] -= eye[1];
    center[2] -= eye[2];

    rotatePoint(up, -speed, center); //was eye

    center[0] += eye[0];
    center[1] += eye[1];
    center[2] += eye[2];
}

void UpCamera()
{ //keyboard interaction for up arrow key
    center[1] += 0.05;
}

void DownCamera()
{ //keyboard interactions for the down arrow key
    center[1] -= 0.05;
}

void ForwardCamera() {
    double speed = 3.1415 / 32;
    double direction[3] = { 0,0,0 };
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];

    eye[0] += direction[0] * speed;
    eye[1] += direction[1] * speed;
    eye[2] += direction[2] * speed;

    center[0] += direction[0] * speed;
    center[1] += direction[1] * speed;
    center[2] += direction[2] * speed;
}

void BackCamera() {
    double speed = -3.1415 / 32;
    double direction[3] = { 0,0,0 };
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];

    eye[0] += direction[0] * speed;
    eye[1] += direction[1] * speed;
    eye[2] += direction[2] * speed;

    center[0] += direction[0] * speed;
    center[1] += direction[1] * speed;
    center[2] += direction[2] * speed;
}

//*****************************
// Keyboard
//*****************************

void specialKeys(int key, int x, int y)
{ //assigns keys for keyboard interaction
    switch (key)
    {
    case GLUT_KEY_LEFT:
        LeftCamera();
        break;
    case GLUT_KEY_RIGHT:
        RightCamera();
        break;
    case GLUT_KEY_UP:
        UpCamera();
        break;
    case GLUT_KEY_DOWN:
        DownCamera();
        break;
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'f': //f, to move the camera in the +ve Z direction
        ForwardCamera();
        break;
    case 'b': //b, to move the camera in the -ve Z direction
        BackCamera();
        break;
    case ' ':
        open = !open;
        break;
    }
    glutPostRedisplay();
}

//*****************************
// Draw Functions
//*****************************

void drawDoor() {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1); //door white
    glVertex3f(-x / 3, y, z / 2); //bottom left corner
    glVertex3f(-x / 3, -y / 1.5, z / 2); //top left corner
    glVertex3f(x / 3, -y / 1.5, z / 2); //top right corner
    glVertex3f(x / 3, y, z / 2); //bottom right corner
    glEnd();
}

void drawDoorway() {
    //left panel
    glBegin(GL_QUADS);
        glColor3f(1, 1, 0.8);
        glVertex3f(-x / 3, -y / 1.5, z / 2); //top left corner
        glVertex3f(-x, -y / 1.5, z /2); //top right corner
        glVertex3f(-x, y, z / 2); //bottom right corner
        glVertex3f(-x / 3, y, z / 2); //bottom left corner
    glEnd();

    //right panel
    glBegin(GL_QUADS);
        glColor3f(1, 1, 0.8);
        glVertex3f(x / 3, -y / 1.5, z / 2); //top left corner
        glVertex3f(x, -y / 1.5, z / 2); //top right corner
        glVertex3f(x, y, z / 2); //bottom right corner
        glVertex3f(x / 3, y, z / 2); //bottom left corner
    glEnd();

    //mantle
    glBegin(GL_QUADS);
        glColor3f(1, 1, 0.8);
        glVertex3f(-x, -y, z / 2); //top left corner
        glVertex3f(x, -y, z / 2); //top right corner
        glVertex3f(x, -y / 1.5, z / 2); //bottom right corner
        glVertex3f(-x, -y / 1.5, z / 2); //bottom left corner
    glEnd();
}

void drawBackLong() {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 0.8);
    glVertex3f(-x, y, z); //top left corner
    glVertex3f(-x, y, 0); //top right corner
    glVertex3f(-x, -y, 0); //bottom right corner
    glVertex3f(-x, -y, z); //bottom left corner
    glEnd();
}

void drawFrontLong() {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 0.8);
    glVertex3f(x, y, z); //top left corner
    glVertex3f(x, y, 0); //top right corner
    glVertex3f(x, -y, 0); //bottom right corner
    glVertex3f(x, -y, z); //bottom left corner
    glEnd();
}

void drawBackWall() {
    glBegin(GL_QUADS);
        glColor3f(1, 1, 0.8);
        glVertex3f(-x, y, z); //top left corner
        glVertex3f(x, y, z); //top right corner
        glVertex3f(x, -y, z); //bottom right corner
        glVertex3f(-x, -y, z); //bottom left corner
    glEnd();
}

void drawFrontWall() {
    glBegin(GL_QUADS);
        glColor3f(1, 1, 0.8);
        glVertex3f(-x, y, 0); //top left corner
        glVertex3f(x, y, 0); //top right corner
        glVertex3f(x, -y, 0); //bottom right corner
        glVertex3f(-x, -y, 0); //bottom left corner
    glEnd();
}

void drawFloor() {
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(-x, -y, 0); //left near corner
    glVertex3f(-x, -y, z); //left far corner
    glVertex3f(x, -y, z); //right far corner
    glVertex3f(x, -y, 0); //right near corner
    glEnd();
}

void drawCeiling() {
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.7, 0.7); //cream
    glVertex3f(-x, y, 0); //left near corner
    glVertex3f(-x, y, z); //left far corner
    glVertex3f(x, y, z); //right far corner
    glVertex3f(x, y, 0); //right near corner
    glEnd();
}

void drawTable() {
    //right short
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1); //white
        glVertex3f(x/2,y, z/5); //bottom left
        glVertex3f(x/2, y/4, z/5); //top left
        glVertex3f(x/2, y/4, 0); //top right
        glVertex3f(x/2, y, 0); //bottom right
    glEnd();

    //left short
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1); //white
        glVertex3f(-x / 2, y, z / 5); //bottom left
        glVertex3f(-x / 2, y / 4, z / 5); //top left
        glVertex3f(-x / 2, y / 4, 0); //top right
        glVertex3f(-x / 2, y, 0); //bottom right
    glEnd();

    //top side
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1); //white
        glVertex3f(-x / 2, y / 4, z / 5); //bottom left
        glVertex3f(-x / 2, y / 4, 0); //top left
        glVertex3f(x / 2, y / 4, 0); //top right
        glVertex3f(x / 2, y / 4, z / 5); //bottom right
    glEnd();

    //front face
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1); //white
        glVertex3f(-x / 2, y, z / 5); //bottom left
        glVertex3f(-x / 2, y / 4, z / 5); //top left
        glVertex3f(x / 2, y / 4, z / 5); //top right
        glVertex3f(x / 2, y, z / 5); //bottom right
    glEnd();

    //back face
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1); //white
        glVertex3f(-x / 2, y, 0); //bottom left
        glVertex3f(-x / 2, y / 4, 0); //top left
        glVertex3f(x / 2, y / 4, 0); //top right
        glVertex3f(x / 2, y, 0); //bottom right
    glEnd();

    //floor
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1); //white
        glVertex3f(-x / 2, -y / 4, z / 5); //bottom left
        glVertex3f(-x / 2, -y / 4, 0); //top left
        glVertex3f(x / 2, -y / 4, 0); //top right
        glVertex3f(x / 2, -y / 4, z / 5); //bottom right
    glEnd();

    glShadeModel(GL_FLAT);
}

void drawRose() {
    glColor3f(0.7, 0.6, 0.4);
    glTranslatef(0, 0, -1.0);
    glScalef(4.0, 4.0, 4.0);
    glRotatef(spin, 0, 1, 0);
    glCallList(importRotate);
}

//*****************************
// INITS, DISPLAY, MAIN
//*****************************

void display(void)
{ //displays our current matrix
    //setup
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]); //defines camera view
    
    //matrix
    glPushMatrix(); //pushes matrix to stack
        drawDoorway();
        drawBackLong();
        drawFrontLong();
        drawBackWall();
        drawFrontWall();
        drawFloor();
        drawCeiling();

    glPushMatrix();//flower vase
        glColor3f(0.7, 0.6, 0.4);
        glTranslatef(0, 0, -1.0);
        glScalef(4.0, 4.0, 4.0);
        glCallList(importRotate);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x / 3, 0, z / 2); //from orgin
        glRotatef(doorHinge, 0, 1, 0);
        glTranslatef(-x / 3, 0, -z / 2); //to orgin
        drawDoor();
    glPopMatrix(); //pop matrix from stack
    
    //THREE TEAPOTS ON THE TABLE

    glPushMatrix();
        glTranslatef(-2, 0, -1.5);

    glPushMatrix();
        drawTable(); 

        glColor3f(1, 0, 0);
        glTranslatef(0, 0.20, -0.5);
        glRotatef(spin, 0, 1, 0);
        glutSolidTeapot(0.25);
        //set_material_props();

        glColor3f(0, 1, 0);
        glTranslatef(-0.65, 0.05, -0.5);
        glutSolidTeapot(0.10);
        //set_material_props2();
    
        glColor3f(0, 0, 1);
        glTranslatef(1.10, 0.05, 0);
        glutSolidTeapot(0.10);
        //set_material_props3();
    glPopMatrix();
    
    //Addtional 3 Objects

    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(2, y + 1, -2);
        glScalef(0.5, 0.5, 0.5);
        drawmodelSoccerball();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.7, 0.7, 1);
        glTranslatef(0, y + 1, z + 1);
        drawmodelAl();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.7, 0.7, 0.2);
        glTranslatef(-2, y + 1, z + 1);
        drawmodelDolphins();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void init()
{
    set_material_props();
    set_material_props2();
    set_material_props3();

    set_light_props(); 
    set_light_props2();
      
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

}

int main(int argc, char** argv)
{
    glutInitWindowSize(windowWidth, windowHeight); //init window

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //init display mode
    glutInitWindowPosition(50, 50);
    glutCreateWindow("OpenGl Project"); //window name

    glMatrixMode(GL_PROJECTION);

    gluPerspective(100, aspect, 0.5, 10);

    room = glGenLists(1);
    importRotate = glGenLists(2);
    door = glGenLists(3);
    objects = glGenLists(4);
    table = glGenLists(5);

    glNewList(room, GL_COMPILE);

    glEndList();

    glNewList(importRotate, GL_COMPILE);
        drawImportRotate();
    glEndList();

    glNewList(door, GL_COMPILE);
        
    glEndList();

    glNewList(objects, GL_COMPILE);

    glEndList();

    glNewList(table, GL_COMPILE);

    glEndList();

    glutDisplayFunc(display); //allows display
    glutSpecialFunc(specialKeys); //allows keyboard interaction
    glutKeyboardFunc(keyboard); //allows keyboard interaction

    glutTimerFunc(0, TimerRotate, 0);
    glutTimerFunc(0, Timer, 0);

    init();
    glutMainLoop();
    return 0;
}
