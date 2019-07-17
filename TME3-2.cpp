/* Athabasca University
 
 Comp390 - Introduction to Computer Graphics
 
 Version 4
 
 Unit 8 Section 3 Objective 1
 
 Calculating three terms
 
 
 
 @author: Steve Leung
 
 @date: June 5, 2011
 
 */

#include <iostream>

#include <math.h>

#include "gl/glut.h"

#include "vector3.h"



using namespace std;



// viewer set to 150 in order to see the difference of specular contribution

vector3 viewer(0.0, 0.0, 150.0);



// square

vector3 wallNormal(0.0, 0.0, 1.0);



// colors

vector3 grey(0.75, 0.75, 0.75);

vector3 lightRed(0.75, 0.1, 0.1);



// lighting position

vector3 lightPosition(10, 10, 10);



// lighting elements

float ambient_coef = 0.3;

float diffuse_coef = 0.7;

float specular_coef = 0.8;


// initialize

void initialize() {
    
    // set background color
    
    glClearColor(0.5, 0.7, 0.5, 0.0);
    
}



// calculate local color

// local color is intensity * base color

vector3 localColor(vector3 intersect, vector3 baseColor, vector3 normal) {
    
    // calculate unit vectors
    
    vector3 origin = lightPosition.subtract(intersect);
    
    vector3 unitVec = origin.normalize();
    
    // calculate the unit vector pointing to the viewer: V
    
    vector3 view = viewer.subtract(intersect);
    
    vector3 VVec = view.normalize();
    
    // calculate the halfway vector between unitVec and VVec
    
    vector3 H = unitVec.add(VVec);
    
    vector3 Hvec = H.normalize();
    
    // specular-reflection exponent ns:
    
    int ns = 75;
    
    // calculate dot product
    
    float dotProd = unitVec.dot(normal);
    
    
    // calculate intensity
    
    float ambientContr = ambient_coef;
    
    float diffuseContr = diffuse_coef * dotProd;
    
    // specular Contribution is calculated as specular_coef * (N dot H)^ns
    
    float specularContr = specular_coef * pow(normal.dot(Hvec), ns);
    
    float intensity = ambientContr + diffuseContr + specularContr;
    
    //float intensity = ambientContr + diffuseContr;
    
    if (intensity > 1.0) intensity = 1.0;
    
    
    
    float r = intensity * baseColor.x;
    
    float g = intensity * baseColor.y;
    
    float b = intensity * baseColor.z;
    
    
    
    return vector3(r,g,b);
    
}



// render

void render() {
    
    // render the square
    
    for (int m=-25; m<25; m++) {
        
        for(int n=-25; n<25; n++) {
            
            vector3 color = localColor(vector3(m,n,0), lightRed, wallNormal);
            
            glColor3f(color.x, color.y, color.z);
            
            glRecti(m, n, m+1, n+1);
            
        }
        
    }
    
}



// display registry

void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
    
    
    //    gluLookAt(0.0, 40.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    
    
    render();
    
    
    
    glutSwapBuffers();
    
}



// reshape registry

void reshape(int w, int h) {
    
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 250.0);
    
    glMatrixMode(GL_MODELVIEW);
    
}



// main program

int main(int argc, char **argv)

{
    
    glutInit( &argc, argv );
    
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;
    
    glutInitWindowSize(500, 500);
    
    glutInitWindowPosition(100, 100);
    
    
    
    int windowHandle = glutCreateWindow("Harjas Virk - TME 3: Project 2");
    
    glutSetWindow(windowHandle);
    
    
    
    glutDisplayFunc( display );
    
    glutReshapeFunc( reshape );
    
    
    
    initialize();
    
    
    
    glutMainLoop();
    
}
