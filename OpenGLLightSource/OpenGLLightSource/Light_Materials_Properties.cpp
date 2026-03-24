// OpenGLLightSource.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <glut.h>
//Setting White Light Source RGBA

GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 },
light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 },
light_specular[] = { 1.0, 1.0, 1.0, 1.0 },
light_position[] = { 0.0, 2.5, 4.0, 1.0 };

GLfloat light_ambient2[] = { 0.0, 0.3, 0.5, 1.0 },
light_diffuse2[] = { 0.0, 1.0, 1.0, 1.0 },
light_specular2[] = { 0.0, 1.0, 1.0, 1.0 },
light_position2[] = { 0.0, 0.0, 7.0, 1.0 };

//Setting materials for Red object

GLfloat material_ambient[] = { 0.3, 0.01, 0.01, 1.0 },
material_diffuse[] = { 0.7, 0.01, 0.01, 1.0 },
material_specular[] = { 0.7, 0.7, 0.7, 1.0 },
material_shininess = 10;

//Setting materials for Smaller Red object

GLfloat material_ambient2[] = {0, 0, 1, 1.0},
material_diffuse2[] = { 0, 0, 10, 1.0 },
material_specular2[] = { 0.5, 0.5, 0.5, 1.0 },
material_shininess2 = 1;

//Setting Camera

float eye[] = { 0.0, 0.0, 5.0 };
float center[] = { 0.0, 0.0, 0.0 };
float up[] = { 0.0, 1.0, 0.0 };

void set_material_props()
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

void set_light_props()
{
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glEnable(GL_LIGHT1);

    glEnable(GL_LIGHTING);
}

void set_light_prop2() 
{
    glTranslatef(0, -3, 0);

    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
    glEnable(GL_LIGHT2);

    glEnable(GL_LIGHTING);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
        glutSolidSphere(3, 32, 32);
    glPopMatrix();

    glPushMatrix();
        set_material_props2();
        glTranslatef(0, -5, -2);  
        glutSolidSphere(1, 32, 32);
    glPopMatrix();

    glutSwapBuffers();
}

void init()
{
    set_material_props();

    set_light_props();
    set_light_prop2();

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(100.0, 1.0, 1.0, 10.0);
    gluLookAt(eye[0], eye[1], eye[2],

        center[0], center[1], center[2],

        up[0], up[1], up[2]);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("red 3D lighted sphere");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}