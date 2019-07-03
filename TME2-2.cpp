/*
 TME 2: 3D Graphics
 
 Name: Harjas Virk
 
 Student ID: 3373921
 */


#include <iostream>

#include <math.h>

#include "gl/glut.h"


typedef GLint vertex3i [3];

vertex3i pt [8]  = { {0,0,0}, {0,1,0}, {1,0,0}, {1,1,0}, {0,0,1}, {0,1,1}, {1,0,1}, {1,1,1} };

typedef GLfloat vertex3f [3];
vertex3f pt2 [5] = { {-0.2,1.0,-0.2}, {1.2,1,-0.2}, {1.2,1,1.2}, {-0.2,1,1.2}, {0.5,1.5,0.5}};

void quad(GLint n1, GLint n2, GLint n3, GLint n4) {
    
    glBegin(GL_QUADS);
    
    
    glVertex3iv (pt[n1]);
    
    
    glVertex3iv (pt[n2]);
    
    
    glVertex3iv (pt[n3]);
    
    
    glVertex3iv (pt[n4]);
    
    glEnd();
    
}

void triangle(GLint n1, GLint n2, GLint n3) {
    glBegin(GL_TRIANGLES);
    
    glVertex3fv(pt2[n1]);
    
    glVertex3fv(pt2[n2]);

    glVertex3fv(pt2[n3]);
    
    glEnd();
}

void cube() {
    
    quad(2,0,1,3);
    
    quad(6,2,3,7);
    
    quad(4,0,2,6);
    
    quad(5,1,0,4);
    
    quad(7,3,1,5);
    
    quad(7,5,4,6);
    
}

void pyramid() {
    
    triangle(0, 1, 4);
    
    triangle(1, 2, 4);
    
    triangle(2, 3, 4);
    
    triangle(3, 0, 4);

}




// initialize

void initialize() {
    
    // set background color
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    
    
    // depth test
    
    glEnable(GL_DEPTH_TEST);
    
}

void drawRoof() {
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPushMatrix();
    
    glColor3f(0.0, 0.0, 1.0);
    
    pyramid();
    
    glPopMatrix();
    
}

void drawCube() {
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPushMatrix();
    
    glColor3f(1.0, 0.0, 0.0);
    
    cube();
    
    glPopMatrix();

    //glEnd();
}

void drawBase() {
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, 0.0, -0.5);
    glVertex3f(2.0, 0.0, -0.5);
    glVertex3f(2.0, 0.0, 2.5);
    glVertex3f(-1.0, 0.0, 2.5);
    glEnd();
}

void drawBigBase() {
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(-8.0, -0.1, -8.0);
    glVertex3f(8.0, -0.1, -8.0);
    glVertex3f(8.0, -0.1, 8.0);
    glVertex3f(-8.0, -0.1, 8.0);
    glEnd();
}


// render

void render() {
    
    GLuint listID = glGenLists(1);
    //GLfloat baseLeft[3] = {-1.0, 0.0, -0.5};
    //GLfloat baseRight[3] = {2.0, 0.0, 2.5};
    
    drawBigBase();

    
    glNewList(listID, GL_COMPILE_AND_EXECUTE);
    drawBase();
    drawCube();
    drawRoof();
    
    glPushMatrix();
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(5.0, 0.0, 4.0);
    glScalef(0.5, 3.0, 1.0);
    drawBase();
    drawCube();
    drawRoof();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -6.0);
    glScalef(3.0, 1.0, 1.0);
    drawBase();
    drawCube();
    drawRoof();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(0.0, 0.0, 1.0, 0.0);
    glTranslatef(-1.0, 0.0, -5.0);
    glScalef(2.0, 3.0, 1.0);
    drawBase();
    drawCube();
    drawRoof();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(15.0, 0.0, 1.0, 0.0);
    glTranslatef(3.0, 0.0, 4.0);
    glScalef(0.25, 0.25, 0.25);
    drawBase();
    drawCube();
    drawRoof();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(-15.0, 0.0, 1.0, 0.0);
    glTranslatef(5.0, 0.0, 4.0);
    glScalef(0.5, 0.5, 0.5);
    drawBase();
    drawCube();
    drawRoof();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(30.0, 0.0, 1.0, 0.0);
    glTranslatef(4.0, 0.0, 4.0);
    glScalef(0.75, 0.75, 0.75);
    drawBase();
    drawCube();
    drawRoof();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(0.0, 0.0, 1.0, 0.0);
    glTranslatef(-4.0, 0.0, 4.0);
    glScalef(3.0, 0.5, 1.0);
    drawBase();
    drawCube();
    drawRoof();
    glPopMatrix();
    
    glEndList();
    
}



// display registry

void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
    gluLookAt(5.0, 4.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    render();
    
    
    
    glutSwapBuffers();
    
}



// reshape registry

void reshape(int w, int h) {
    
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 50.0);
    
    glMatrixMode(GL_MODELVIEW);
    
}



// main program

int main(int argc, char **argv)

{
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(500, 500);
    
    glutInitWindowPosition(100, 100);
    
    
    
    int windowHandle = glutCreateWindow("Athabasca University - Unit 1 Section 2 Objective 3");
    
    glutSetWindow(windowHandle);
    
    
    
    glutDisplayFunc(display);
    
    glutReshapeFunc(reshape);
    
    
    
    initialize();
    
    
    
    glutMainLoop();
    
}
