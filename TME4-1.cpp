/* Athabasca University
 
 Comp390 - Introduction to Computer Graphics
 
 Version 4
 
 Unit 11 Section 2 Objective 2
 
 Ray tracing - two objects, one reflection
 
 
 
 @author: Steve Leung
 
 @date: May 4, 2011
 
 */

#define GL_SILENCE_DEPRECATION

#include <iostream>

#include <math.h>

#include "GLUT/glut.h"

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

float local_coef   = 0.6;



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
    
    
    
    return vector3(r,g,b);
    
}

vector3 recursiveTracer (vector3 i, vector3 contribution) {
    
    vector3 reflect = i.subtract(viewer).reflect(floorNormal);
    vector3 sm = wall.intersect(i, i.add(reflect));
    vector3 color = localColor(i, grey, floorNormal);
    
    //vector3 c is the contact point that the ray makes
    vector3 c = wall.intersect(viewer, i);
    
    if ( (c.x >= -25.0) && (c.x <= 25.0) && (c.y >= 0.0) && (c.y <= 50.0) ) {
        contribution = lightRed;
    } else if ((sm.x >= -25.0) && (sm.x <= 25.0) && (sm.y >= 0.0) && (sm.y <= 50.0)){
        vector3 reflectColor = localColor(sm, lightRed, wallNormal);
        contribution = color.scalar(local_coef).add(reflectColor.scalar(reflect_coef));
        recursiveTracer(reflect, contribution);
    } else {
        contribution = color;
        recursiveTracer(reflect, contribution);
    }
    return contribution;
}


// render

void render() {
    
    // render the floor
    
    for (int i=-75; i < 75; i++) {
        
        for (int j=-75; j < 75; j++) {
            
            vector3 incident = vector3(i,0,j);
            
            vector3 mixedColor = recursiveTracer(incident, vector3(0,0,0));
            
            glColor3f(mixedColor.x, mixedColor.y, mixedColor.z);
            
            
            
            // use the small rectangles method
            
            glBegin(GL_POLYGON);
            
            glVertex3i(i, 0, j);
            
            glVertex3i(i+1, 0, j);
            
            glVertex3i(i+1, 0, j+1);
            
            glVertex3i(i, 0, j+1);
            
            glEnd();
            
        }
        
    }
    
    
    
    // render the wall - non-reflective surface
    
    for (int m=-25; m<25; m++) {
        
        for(int n=0; n<50; n++) {
            
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
    
    
    
    gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    
    
    render();
    
    
    
    glutSwapBuffers();
    
}



// reshape registry

void reshape(int w, int h) {
    
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);
    
    glMatrixMode(GL_MODELVIEW);
    
}



// main program

int main(int argc, char **argv)

{
    
    glutInit( &argc, argv );
    
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;
    
    glutInitWindowSize(500, 500);
    
    glutInitWindowPosition(100, 100);
    
    
    
    int windowHandle = glutCreateWindow("Athabasca University - Comp390 U11 S2 O2");
    
    glutSetWindow(windowHandle);
    
    
    
    glutDisplayFunc( display );
    
    glutReshapeFunc( reshape );
    
    
    
    initialize();
    
    
    
    glutMainLoop();
    
}
