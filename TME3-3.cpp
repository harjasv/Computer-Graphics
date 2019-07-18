/*
Harjas Virk - 3373921

TME3: Lighting and Surface Textures
Project 3

This project is a continuation of Project 2 from TME 2, in which a textured background is created.
*/

#include "windows.h"

#include <iostream>

#include <math.h>

#include "gl/glut.h"

#include <iostream>

#include <fstream>

#include <string>



using namespace std;


typedef GLint vertex3i[3];

vertex3i pt[8] = { { 0,0,0 },{ 0,1,0 },{ 1,0,0 },{ 1,1,0 },{ 0,0,1 },{ 0,1,1 },{ 1,0,1 },{ 1,1,1 } };

typedef GLfloat vertex3f[3];
vertex3f pt2[5] = { { -0.2,1.0,-0.2 },{ 1.2,1,-0.2 },{ 1.2,1,1.2 },{ -0.2,1,1.2 },{ 0.5,1.5,0.5 } };

// image

GLubyte *image;

GLubyte * l_texture;

BITMAPFILEHEADER fileheader;

BITMAPINFOHEADER infoheader;

RGBTRIPLE rgb;

GLuint texName;



// makeImage is from the unit objective 9.1.2 and reads and stores the bitmap image 

void makeImage(void) {

	int i, j = 0;

	FILE *l_file;



	string fn = "side.bmp";

	const char * filename = fn.c_str();



	// open image file, return if error

	fopen_s(&l_file, filename, "rb");

	if (l_file == NULL) exit(0);



	// read file header and header info

	fread(&fileheader, sizeof(fileheader), 1, l_file);

	fseek(l_file, sizeof(fileheader), SEEK_SET);

	fread(&infoheader, sizeof(infoheader), 1, l_file);



	// allocate space for the image file

	l_texture = (GLubyte *)malloc(infoheader.biWidth * infoheader.biHeight * 4);

	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);



	// read da data

	j = 0;

	for (i = 0; i < infoheader.biWidth*infoheader.biHeight; i++)

	{

		fread(&rgb, sizeof(rgb), 1, l_file);



		l_texture[j + 0] = (GLubyte)rgb.rgbtRed; // Red component

		l_texture[j + 1] = (GLubyte)rgb.rgbtGreen; // Green component

		l_texture[j + 2] = (GLubyte)rgb.rgbtBlue; // Blue component

		l_texture[j + 3] = (GLubyte)255; // Alpha value

		j += 4; // Go to the next position

	}



	fclose(l_file); // Closes the file stream

}

// quad, triangle, cube, and pyramid are from my TME2 Project 2
void quad(GLint n1, GLint n2, GLint n3, GLint n4) {

	glBegin(GL_QUADS);


	glVertex3iv(pt[n1]);


	glVertex3iv(pt[n2]);


	glVertex3iv(pt[n3]);


	glVertex3iv(pt[n4]);

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

	quad(2, 0, 1, 3);

	quad(6, 2, 3, 7);

	quad(4, 0, 2, 6);

	quad(5, 1, 0, 4);

	quad(7, 3, 1, 5);

	quad(7, 5, 4, 6);

}

void pyramid() {

	triangle(0, 1, 4);

	triangle(1, 2, 4);

	triangle(2, 3, 4);

	triangle(3, 0, 4);

}


void initialize(void) {

	// set background color

	glClearColor(1.0, 1.0, 1.0, 1.0);



	// image

	makeImage();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	// bind the texture to texName

	glGenTextures(1, &texName);

	glBindTexture(GL_TEXTURE_2D, texName);


	// set texture parameters

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	// set parameters for 2d rgba texture space

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,

		infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,

		l_texture);

	// depth test
	
	glEnable(GL_DEPTH_TEST);

}

// drawPicture is from unit objective 9.1.2 and sets the coordinates for the texture to inhabit, in this case, the background

void drawPicture() {

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0); glVertex3f(-8.0, -0.1, -8.0);

	glTexCoord2d(0.0, 1.0); glVertex3f(-8.0, 15.9, -8.0);

	glTexCoord2d(1.0, 1.0); glVertex3f(8.0, 15.9, -8.0);

	glTexCoord2d(1.0, 0.0); glVertex3f(8.0, -0.1, -8.0);

	glEnd();

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0); glVertex3f(-8.0, -0.1, 8.0);

	glTexCoord2d(0.0, 1.0); glVertex3f(-8.0, 15.9, 8.0);

	glTexCoord2d(1.0, 1.0); glVertex3f(-8.0, 15.9, -8.0);

	glTexCoord2d(1.0, 0.0); glVertex3f(-8.0, -0.1, -8.0);

	glEnd();

}

// the following draw functions are from my TME2 project 2, and draw the shapes for the scene

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

	// Draw the background and immediately disable the texture so that the texture is limited to its coordinates

	glEnable(GL_TEXTURE_2D);
	drawPicture();
	glDisable(GL_TEXTURE_2D);

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
