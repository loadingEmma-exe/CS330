// OpenGLTextureMapping.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <math.h>
#include  "glut.h"
#include "imageloader.h"

// get the texture IDs
GLuint _textureId1;
GLuint _textureId2;

GLuint loadTexture(Image* image) {
    GLuint textureId;

    glGenTextures(1, &textureId); //
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,  //type of the texture
        0,                    //used for mipmapping should be zero otherwise
        3,                    //elements per texel, usually 3 (RGB) or 4 (RGBA)
        image->width,
        image->height,       //Width and height of the image
        0,                   //The border of the image
        GL_RGB,               //Texels Format
        GL_UNSIGNED_BYTE,   // type
        image->pixels);      //The actual pixel data
    return textureId;           //Returns the id of the texture
}

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
{
    //load your images
    Image* image1 = loadBMP("floor.bmp");
    Image* image2 = loadBMP("monalisa.bmp");

    // get the IDs
    _textureId1 = loadTexture(image1);
    _textureId2 = loadTexture(image2);

    //setup
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]); //defines camera view

    //texture mapping
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glutSolidCube(0.25);        
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS); //QUADS, POLYGON, 3D
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

    glEnd();

    glFlush();
    glutSwapBuffers();

    //free memory
    delete image1;
    delete image2;
}

void main(int argc, char** argv)
{
    glutInitWindowSize(windowWidth, windowHeight); //init window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //init display mode
    glutInitWindowPosition(50, 50); //init position
    glutCreateWindow("Texture Mapping"); //window name

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, aspect, 0, 10);
    glutDisplayFunc(display); //allows keyboard interaction
    glutSpecialFunc(specialKeys); //allows keyboard interaction
    glutMainLoop();
}

/*
//texture mapping
    // Add texture to your object
    glPushMatrix();
    // Before drawing an object, you need to enable
    // GL_TEXTURE_2D using glEnable(GL_TEXTURE_2D).
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId1);
    // When texture coordinates are out of the normal range
    //[0,1], you need to specify their desired effects for
    //the final texture mapping using the function
    //glTexParameteri(). If you want to repeat the texture,
    //they can use the built-in GL_REPEAT feature. Texture
    //filling step decides which textel’s color is as the
    //texture is scaled up or down. With GL_NEAREST, the
    //exact point sample of texture is used to make the
    //decision. With GL_LINEAR, four nearby texels are
    //linearly interpolated to decide the final result for
    //the texel’s color.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glutSolidTeapot(1);
    // After finishing the drawing, you can disable it using
    // glDisable(GL_TEXTURE_2D).
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
*/