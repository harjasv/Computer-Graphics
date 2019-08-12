/* Athabasca University

Harjas Virk
3373921

TME 4
Project 1

Recursive Ray Tracer

*/

#define GL_SILENCE_DEPRECATION

#include <iostream>

#include <math.h>

#include "gl/glut.h"

#include "plane.h"

using namespace std;

// viewer

vector3 viewer(-40.0, 40.0, 120.0);



// floor

vector3 floorNormal(0.0, 1.0, 0.0);

plane   floorDef(0.0, 4.0, 0.0, 0.0);

vector3 floorLimit1(-75.0, 0, -75.0);

vector3 floorLimit2(-75.0, 0, 75.0);

vector3 floorLimit3(75.0, 0, 75.0);

vector3 floorLimit4(75.0, 0, -75.0);



// wall

vector3 wallNormal(0.0, 0.0, 1.0);

plane   wall(0.0, 0.0, 4.0, 0.0);

vector3 wallLimit1(-25.0, 0.0, 0.0);

vector3 wallLimit2(-25.0, 50.0, 0.0);

vector3 wallLimit3(25.0, 50.0, 0.0);

vector3 wallLimit4(25.0, 0.0, 0.0);



// colors

vector3 grey(0.75, 0.75, 0.75);

vector3 lightRed(0.75, 0.1, 0.1);



// lighting position

vector3 lightPosition(25, 25, 100.0);



// lighting elements

float ambient_coef = 0.3;

float diffuse_coef = 0.7;

float reflect_coef = 0.4;

float local_coef = 0.6;



// initialize

void initialize() {

	// set background color

	glClearColor(0.5, 0.7, 0.5, 0.0);

}



// calculate local color

// local color is intensity * base color

vector3 localColor(vector3 intersect, vector3 baseColor, vector3 normal) {

	// calculate unit vector

	vector3 origin = lightPosition.subtract(intersect);

	vector3 unitVec = origin.normalize();



	// calculate dot product

	float dotProd = unitVec.dot(normal);



	// calculate intensity

	float ambientContr = ambient_coef;

	float diffuseContr = diffuse_coef * dotProd;

	float intensity = ambientContr + diffuseContr;



	if (intensity > 1.0) intensity = 1.0;



	float r = intensity * baseColor.x;

	float g = intensity * baseColor.y;

	float b = intensity * baseColor.z;



	return vector3(r, g, b);

}

//This is the recursive ray tracing function to be used, it takes the destination of the ray as an input, and the viewer is the origin of the ray by default
vector3 recursiveTracer(vector3 i, vector3 contribution) {

	vector3 reflect = i.subtract(viewer).reflect(floorNormal);
	vector3 sm = wall.intersect(i, i.add(reflect));
	vector3 color = localColor(i, grey, floorNormal);

	//vector3 c is the intersect point that the ray makes on its journey to the floor. It's main use is to detect if the wall is hit
	vector3 c = wall.intersect(viewer, i);

	//If the wall is hit, the contribution is simply the color of the wall, and there is no recursive call
	if ((c.x >= -25.0) && (c.x <= 25.0) && (c.y >= 0.0) && (c.y <= 50.0)) {
		contribution = lightRed;
	}
	//If the reflection of the ray hits the wall, it mixes the color
	else if ((sm.x >= -25.0) && (sm.x <= 25.0) && (sm.y >= 0.0) && (sm.y <= 50.0)) {
		vector3 reflectColor = localColor(sm, lightRed, wallNormal);
		contribution = color.scalar(local_coef).add(reflectColor.scalar(reflect_coef));
		recursiveTracer(reflect, contribution);
	}
	else {
		//If it lands on the floor and the reflection does not hit the wall, it simply returns the color of the floor and goes through recursion again
		contribution = color;
		recursiveTracer(reflect, contribution);
	}
	return contribution;
}


// render

void render() {

	// render the floor

	for (int i = -75; i < 75; i++) {

		for (int j = -75; j < 75; j++) {

			vector3 incident = vector3(i, 0, j);

			//This is where the recursive call is made and is input into the mixedColor vector for each point of the scene
			vector3 mixedColor = recursiveTracer(incident, vector3(0, 0, 0));

			glColor3f(mixedColor.x, mixedColor.y, mixedColor.z);



			// use the small rectangles method

			glBegin(GL_POLYGON);

			glVertex3i(i, 0, j);

			glVertex3i(i + 1, 0, j);

			glVertex3i(i + 1, 0, j + 1);

			glVertex3i(i, 0, j + 1);

			glEnd();

		}

	}



	// render the wall - non-reflective surface

	for (int m = -25; m<25; m++) {

		for (int n = 0; n<50; n++) {

			vector3 color = localColor(vector3(m, n, 0), lightRed, wallNormal);

			glColor3f(color.x, color.y, color.z);

			glRecti(m, n, m + 1, n + 1);

		}

	}

}



// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();



	gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);



	render();



	glutSwapBuffers();

}



// reshape registry

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);

	glMatrixMode(GL_MODELVIEW);

}



// main program

int main(int argc, char **argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutInitWindowPosition(100, 100);



	int windowHandle = glutCreateWindow("Athabasca University - TME4 Project 1");

	glutSetWindow(windowHandle);



	glutDisplayFunc(display);

	glutReshapeFunc(reshape);



	initialize();



	glutMainLoop();

}
