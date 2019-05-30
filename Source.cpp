/*
TME 1: 2D Graphics

Name: Harjas Virk

Student ID: 3373921
*/



#include "gl/glut.h"



// initialize

void initialize() {

	// set background color

	glClearColor(1.0, 1.0, 1.0, 0.0);

}



// render

void render() {

	// points color

	glColor3f(0.0, 0.0, 0.0);

	// line

	const GLfloat p1[] = {-3.0, 3.0};

	glBegin(GL_LINE_LOOP);

	glVertex2fv(p1);

	//glVertex2f(-3.0, 3.0);

	glVertex2f(0.0, 4.0);

	glVertex2f(1.0, 1.0);

	glVertex2f(-2.0, 0.0);

	glEnd();

	glBegin(GL_LINE_LOOP);

	glVertex2f(-3.75, 2.75);

	glVertex2f(0.75, 4.25);

	glVertex2f(-1.75, 4.25);

	glEnd();

	glEnable(GL_LINE_SMOOTH);

	glBegin(GL_LINE_LOOP);

	glVertex2f(-1.5, -1.5);

	glVertex2f(1.5, -0.5);

	glVertex2f(2.5, -3.5);

	glVertex2f(-0.5, -4.5);

	glEnd();

	glBegin(GL_LINE_LOOP);

	glVertex2f(-2.25, -1.75);

	glVertex2f(2.25, -0.25);

	glVertex2f(-0.25, -0.25);

	glEnd();




}



// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();



	// viewing

	gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);



	render();



	glutSwapBuffers();

}



// reshape registry

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);

	glMatrixMode(GL_MODELVIEW);

}



// main program

int main(int argc, char **argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutInitWindowPosition(100, 100);



	int windowHandle = glutCreateWindow("Athabasca University - Comp390 U3 S2 O2");

	glutSetWindow(windowHandle);



	glutDisplayFunc(display);

	glutReshapeFunc(reshape);



	initialize();



	glutMainLoop();

}