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

vector3 viewer(80, 80, 80);

// color

vector3 lightRed(0.75, 0.1, 0.1);


// lighting position

vector3 lightPosition(200, 200, 0);

vector3 lightPosition2(0, 200, 200);



// lighting elements

float ambient_coef = 0.3;

float diffuse_coef = 0.7;

float reflect_coef = 0.4;

float local_coef   = 0.6;



// initialize

void initialize() {
    
    glClearColor(0.0, 0.3, 0.6, 0.0);
    
}

// calculate local color

// local color is intensity * base color

vector3 localColor(vector3 intersect, vector3 baseColor, vector3 normal) {
    
    // calculate unit vector
    
    vector3 origin = lightPosition.subtract(intersect);
    
    vector3 unitVec = origin.normalize();
    
    // calculate unit vector for second light
    
    vector3 origin2 = lightPosition2.subtract(intersect);
    
    vector3 unitVec2 = origin2.normalize();
    
    
    
    // calculate dot product
    
    float dotProd = unitVec.dot(normal);
    
    // calculate second dot product
    
    float dotProd2 = unitVec2.dot(normal);
    
    
    
    // calculate intensity
    
    float ambientContr = ambient_coef;
    
    float diffuseContr = diffuse_coef * dotProd;
    
    float diffuseContr2 = diffuse_coef * dotProd2;
    
    // add the intensities of both lights
    
    float intensity = ambientContr + diffuseContr + diffuseContr2 + ambientContr;
    
    if (intensity > 1.0) intensity = 1.0;
    
    float r = intensity * baseColor.x;
    
    float g = intensity * baseColor.y;
    
    float b = intensity * baseColor.z;
    
    vector3 color(r,g,b);
    
    return color;
}


vector3 floorColor(vector3 in) {
    vector3 f(0, 0, 0);
    
    for (int i= -200; i <= in.x; i += 10) {
        
        for (int j=-200; j <= in.z; j += 10) {
            
            if (((i+j)/10 % 2) == 0) {
                
                f = vector3(0.9, 0.9, 0.9);
            
            } else {
                
                f = vector3(0.2, 0.2, 0.2);
            }
        }
        
    }
    
    return f;
}

vector3 colorMix (vector3 i, vector3 n, plane fp) {
    
    vector3 color = localColor(i, lightRed, n);
    
    vector3 reflectColor(0.0, 0.3, 0.6);
    
    vector3 mixedColor(0.0, 0.0, 0.0);
    
    vector3 reflect = i.subtract(viewer).reflect(n);
    
    vector3 sm = fp.intersect(i, i.add(reflect));
    
    if((sm.x >= -200) && (sm.x <= 200) && (sm.z >= -200) && (sm.z <= 200) && (n.y == 0)) {
        vector3 reflectColor = localColor(sm, floorColor(sm), n);
        mixedColor = color.scalar(local_coef).add(reflectColor.scalar(reflect_coef));
    } else {
        mixedColor = color.scalar(local_coef).add(reflectColor.scalar(reflect_coef));
    }
    
    return mixedColor;
}

vector3 shadow (vector3 i, vector3 n, plane wp) {
    
    vector3 mixedColor(0,0,0);
    
    vector3 color = localColor(i, floorColor(i), n);
    
    vector3 l = plane(1,0,0,0).intersect(i, lightPosition);
    
    vector3 m = plane(0,0,1,0).intersect(i, lightPosition2);
    
    if((l.z >= 0) && (l.z <= 40) && (l.y >= 0) && (l.y <= 40)) {
        vector3 shadowColor = localColor(l, vector3(0,0,0), n);
        return mixedColor = color.scalar(local_coef).add(shadowColor.scalar(reflect_coef));
    } else if((m.x >= 0) && (m.x <= 40) && (m.y >= 0) && (m.y <= 40)) {
        vector3 shadowColor = localColor(m, vector3(0,0,0), n);
        return mixedColor = color.scalar(local_coef).add(shadowColor.scalar(reflect_coef));
    }
    
    return color;
}

void scene() {

    plane p(0, 0, 4, 0);
    vector3 n(0, 0, 1);
    
    plane fp(0, 4, 0, 0);
    vector3 fn(0, 1, 0);
    
    // render the shadows on the floor
    
    for(int x = -200; x < 200; x++) {
        for(int z = -200; z < 200; z++) {
            vector3 floorColor = shadow(vector3(x,0,z), vector3(0,1,0), plane(0,0,1,0));
            
            glColor3f(floorColor.x, floorColor.y, floorColor.z);
            
            glBegin(GL_POLYGON);
            
            glVertex3i(x, 0, z);
            
            glVertex3i(x+1, 0, z);
            
            glVertex3i(x+1, 0, z+1);
            
            glVertex3i(x, 0, z+1);
            
            glEnd();
        }
    }
    
    //render the cube
    
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            
            vector3 mixedColor = colorMix(vector3(i,j,40), vector3(0,0,1), plane(0,1,0,0));
            
            glColor3f(mixedColor.x, mixedColor.y, mixedColor.z);
            
            glBegin(GL_QUADS);
            
            glVertex3i(i, j, 40);
            
            glVertex3i(i+1, j, 40);
            
            glVertex3i(i+1, j+1, 40);
            
            glVertex3i(i, j+1, 40);
            
            glEnd();
            
            mixedColor = colorMix(vector3(40,i,j), vector3(1,0,0), plane(0,1,0,0));
            
            glColor3f(mixedColor.x, mixedColor.y, mixedColor.z);
            
            glBegin(GL_QUADS);
            
            glVertex3i(40, i, j);
            
            glVertex3i(40, i+1, j);
            
            glVertex3i(40, i+1, j+1);
            
            glVertex3i(40, i, j+1);
            
            glEnd();
            
            mixedColor = colorMix(vector3(i,40,j), vector3(0,1,0), plane(0,1,0,0));
            
            glColor3f(mixedColor.x, mixedColor.y, mixedColor.z);
            
            glBegin(GL_QUADS);
            
            glVertex3i(i, 40, j);
            
            glVertex3i(i+1, 40, j);
            
            glVertex3i(i+1, 40, j+1);
            
            glVertex3i(i, 40, j+1);
            
            glEnd();
            
        }
    }

}

void cubeOutline() {
    
    
    glColor3f(1, 0, 0);
    
    glBegin(GL_LINE_LOOP);
    //quad(p2,p0,p1,p3);
    
    glVertex3f(40, 0, 0);
    
    glVertex3f(40,40,0);
    
    glVertex3f(40, 40, 40);
    
    glVertex3f(40, 0, 40);
    
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    //quad(p2,p0,p1,p3);
    
    glVertex3f(0, 0, 40);
    
    glVertex3f(0,40,40);
    
    glVertex3f(40, 40, 40);
    
    glVertex3f(40, 0, 40);
    
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    //quad(p2,p0,p1,p3);
    
    glVertex3f(0, 40, 0);
    
    glVertex3f(0,40,40);
    
    glVertex3f(40, 40, 40);
    
    glVertex3f(40, 40, 0);
    
    glEnd();
    
}

// render

void render() {
    
    scene();
    
    cubeOutline();
    
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
