/*
TME 2: 3D Graphics

Name: Harjas Virk

Student ID: 3373921
*/



#include <iostream>

#include <math.h>

#include "gl/glut.h"


// initialize

void initialize() {

	// set background color

	glClearColor(1.0, 1.0, 1.0, 1.0);



	// depth test

	glEnable(GL_DEPTH_TEST);

}


// render

void render() {

	glNewList(1, GL_COMPILE_AND_EXECUTE);

	glEndList();

}



// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();



	gluLookAt(0.0, 6.0, 16.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);



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
