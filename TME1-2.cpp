/* Athabasca University
 
 Comp390 - Introduction to Computer Graphics
 
 Version 4
 
 Unit 3 Section 2 Objective 2
 
 Draw a line
 
 
 
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

class verts {
    public:
    GLfloat x, y;
};

void rotate(verts pivot, GLdouble theta, verts& p) {
    verts newPoint;
    
    newPoint.x = pivot.x + (p.x - pivot.x) * cos(theta) - (p.y - pivot.y) * sin(theta);
    newPoint.y = pivot.y + (p.x - pivot.x) * sin(theta) + (p.y - pivot.y) * cos(theta);
    p = newPoint;
    //return newPoint;
}

GLdouble theta(GLdouble degrees) {
    return -degrees * M_PI/180;
}

// render

void render() {
    
    // points color
    
    glColor3f(0.0, 0.0, 0.0);
    
    // line
    
    GLfloat points[7][2] = {
        {-0.5, 1.5},
        {-0.5, 0.5},
        {0.5, 0.5},
        {0.5, 1.5},
        {-1.0, 1.5},
        {0.0, 2.0},
        {1.0, 1.5}
    };
    
    int i, j;
    verts p[5][7];
    verts pivot;
    pivot.x = 0;
    pivot.y = -11;

    for(j = 0; j < 5; j++) {
        for(i = 0; i < 7; i++) {
            if(j%2 == 0) {
                p[j][i].x = points[i][0];
            } else {
                p[j][i].x = points[i][0];
            }
            
            p[j][i].y = points[i][1];
        }
    }
    
    for(i = 0; i < 7; i++) {
        rotate(pivot, theta(10), p[1][i]);
        rotate(pivot, theta(-10), p[2][i]);
        rotate(pivot, theta(20), p[3][i]);
        rotate(pivot, theta(-20), p[4][i]);
    }
    
    glEnable(GL_LINE_SMOOTH);
    for(j = 0; j < 5; j++) {
        glBegin(GL_LINE_LOOP);
        for(i = 0; i < 7; i++){
            glVertex2f(p[j][i].x, p[j][i].y);
        }
        glEnd();
    }
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
    
    
    
    int windowHandle = glutCreateWindow("Athabasca University - Comp390 U3 S2 O2");
    
    glutSetWindow(windowHandle);
    
    
    
    glutDisplayFunc( display );
    
    glutReshapeFunc( reshape );
    
    
    
    initialize();
    
    
    
    glutMainLoop();
    
}
