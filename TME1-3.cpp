/* Athabasca University
 
 Comp390 - Introduction to Computer Graphics
 
 Version 4
 
 Unit 5 Section 2 Objective 2
 
 Color a polygon
 
 
 
 @author: Steve Leung
 
 @date: May 4, 2011
 
 */



#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <math.h>



// initialize

void initialize() {
    
    // set background color
    
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
}



// render

void render() {
    
    glBegin(GL_QUADS);
    
    glColor3f(0.0, 1.0, 0.0);        //  green
    
    glVertex2f(-2.0, 2.0);
    
    glColor3f(0.0, 0.0, 1.0);       // blue
    
    glVertex2f(2.0, 2.0);
    
    glColor3f(1.0, 1.0, 0.0);        //  yellow
    
    glVertex2f(2.0, -2.0);
    
    glColor3f(1.0, 0.0, 0.0);       // red
    
    glVertex2f(-2.0, -2.0);
    
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
    
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);
    
    glMatrixMode(GL_MODELVIEW);
    
}



// main program

int main(int argc, char **argv)

{
    
    glutInit( &argc, argv );
    
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;
    
    glutInitWindowSize(500, 500);
    
    glutInitWindowPosition(100, 100);
    
    
    
    int windowHandle = glutCreateWindow("Athabasca University - Comp390 U5 S2 O2");
    
    glutSetWindow(windowHandle);
    
    
    
    glutDisplayFunc( display );
    
    glutReshapeFunc( reshape );
    
    
    
    initialize();
    
    
    
    glutMainLoop();
    
}
