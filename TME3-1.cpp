/*
 TME 3: Lighting and Surface Textures
 Project 1
 
 Name: Harjas Virk
 
 Student ID: 3373921
 
 README:
 The program's defaults are set to all lights off, the material property set to gold, and the default light element setting is set to Ambient, Diffuse, and Specular. 
 */


#include <gl/glut.h>
#include <stdlib.h>

// This Light class is for ease of use in determining the light factors
class Light {
    public:
        GLenum light;
        GLfloat* ambient;
        GLfloat* diffuse;
        GLfloat* specular;
        GLfloat* colour;
        GLfloat* position;
};

// This enum is used as a helper for determining the light element
enum Element {
    AMBIENT,
    AMBIENT_DIFFUSE,
    AMBIENT_DIFFUSE_SPECULAR,
};

// light positions:
// This light position is top left
GLfloat light_position0[] = { -10.0, 10.0, 10.0, 0.0 };

// This light position is top right
GLfloat light_position1[] = { 10.0, 10.0, 10.0, 0.0 };

// This light position is right behind the viewer
GLfloat light_position2[] = { 0.0, 0.0, 5.0, 0.0 };


//These are colours used for the lights
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat red_light[] = { 1.0, 0.4, 0.4, 1.0 };

GLfloat blue_light[] = { 0.2, 0.2, 1.0, 1.0 };

GLfloat green_light[] = { 0.2, 1.0, 0.2, 1.0 };

GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

GLfloat no_light[] = { 0.0, 0.0, 0.0, 0.0 };



// some surface materials parameters

// gold

GLfloat gold_ambient[] = { 0.24725, 0.1995, 0.0745, 1.0 };

GLfloat gold_diffuse[] = { 0.75164, 0.60648, 0.22658, 1.0 };

GLfloat gold_specular[] = { 0.628281, 0.555802, 0.366065, 1.0 };

GLfloat gold_shininess[] = { 51.2 };


// silver

GLfloat silver_ambient[] = { 0.19225, 0.19225, 0.19225, 1.0 };

GLfloat silver_diffuse[] = { 0.50754, 0.50754, 0.50754, 1.0 };

GLfloat silver_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };

GLfloat silver_shininess[] = { 51.2 };

// copper

GLfloat copper_ambient[] = { 0.2295, 0.08825, 0.0275, 1.0 };

GLfloat copper_diffuse[] = { 0.5508, 0.2118, 0.066, 1.0 };

GLfloat copper_specular[] = { 0.580594, 0.223257, 0.0695701, 1.0 };

GLfloat copper_shininess[] = { 51.2 };

// Lights
//This function initializes the lights, with the default being only ambient, and no lights on
Light initLight(GLenum l) {
    Light light;
    light.light = l;
    //light.ambient = no_light;
    //light.diffuse = no_light;
    //light.specular = no_light;
    light.colour = no_light;
    return light;
}

Light L1 = initLight(GL_LIGHT0);
Light L2 = initLight(GL_LIGHT1);
Light L3 = initLight(GL_LIGHT2);

// This is the function used to set the colour of each light, without effecting the elements of the lights
void setColour(Light &l, GLfloat* colour) {
    l.colour = colour;
    
    l.ambient = colour;
    glLightfv(l.light, GL_AMBIENT, colour);
    
    if(l.diffuse != no_light) {
        l.diffuse = colour;
        glLightfv(l.light, GL_DIFFUSE, colour);
    }
    
    if(l.specular != no_light) {
        l.specular = colour;
        glLightfv(l.light, GL_SPECULAR, colour);
    }
}

// This function is used to set the elements of the lights using the enum above, so that only the element specified is changed.
void setElement(Light &l, Element setting) {
    if(setting == AMBIENT) {
        l.ambient = l.colour;
        l.diffuse = no_light;
        l.specular = no_light;
        glLightfv(l.light, GL_AMBIENT, l.colour);
        glLightfv(l.light, GL_DIFFUSE, no_light);
        glLightfv(l.light, GL_SPECULAR, no_light);
    }
    
    if(setting == AMBIENT_DIFFUSE) {
        l.ambient = l.colour;
        l.diffuse = l.colour;
        l.specular = no_light;
        glLightfv(l.light, GL_AMBIENT, l.colour);
        glLightfv(l.light, GL_DIFFUSE, l.colour);
        glLightfv(l.light, GL_SPECULAR, no_light);
    }
    
    if(setting == AMBIENT_DIFFUSE_SPECULAR) {
        l.ambient = l.colour;
        l.diffuse = l.colour;
        l.specular = l.colour;
        glLightfv(l.light, GL_AMBIENT, l.colour);
        glLightfv(l.light, GL_DIFFUSE, l.colour);
        glLightfv(l.light, GL_SPECULAR, l.colour);
    }
}

// initialize

void initialize() {
    
    // set background color
    
    glClearColor(0.5, 0.7, 0.5, 0.0);
    
    
    
    // enable depth test
    
    glEnable(GL_DEPTH_TEST);
    
    
    
    // enable lighting
    
    glEnable(GL_LIGHTING);
    
    glEnable(GL_LIGHT0);
    
    glEnable(GL_LIGHT1);
    
    glEnable(GL_LIGHT2);            // don't forget to enable light 2
    
    
    
    // set lights
    
    //The lights are all initially turned off, and the default material of the sphere is set to gold
    
    // light 0
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
    
    glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
    
    
    
    // light 1
    
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    
    glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light);
    
    glLightfv(GL_LIGHT1, GL_SPECULAR, no_light);
    
    
    
    // light 2
    
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    
    glLightfv(GL_LIGHT2, GL_DIFFUSE, no_light);
    
    glLightfv(GL_LIGHT2, GL_SPECULAR, no_light);
    
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, gold_specular);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);
    
    glMaterialfv(GL_FRONT, GL_SHININESS, gold_shininess);
    
    
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    
}



// render

void render() {
    
    glColor3f(0.5, 0.5, 0.5);
    
    glPushMatrix();
    
    glutSolidSphere(1.0, 64, 10);
    
    glPopMatrix();
    
}



// display registry

void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
    gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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


// This is the main menu, which has only one case that is not a sublist, which is quit.
void mainMenu(int id){
    switch (id) {
        case 1:
            exit(0);
            break;
            
        default:
            break;
    }
}

// The following three light menus operate on their each individual lights, hence three separate light menus

void lightMenu1(int id){
    glPushMatrix();
    switch (id) {
        case 1:
            glDisable(GL_LIGHT0);
            break;
        case 2:
            if(!glIsEnabled(GL_LIGHT0)) glEnable(GL_LIGHT0);
            setColour(L1, white_light);
            break;
        case 3:
            if(!glIsEnabled(GL_LIGHT0)) glEnable(GL_LIGHT0);
            setColour(L1, red_light);
            break;
        case 4:
            if(!glIsEnabled(GL_LIGHT0)) glEnable(GL_LIGHT0);
            setColour(L1, blue_light);
            break;
        case 5:
            if(!glIsEnabled(GL_LIGHT0)) glEnable(GL_LIGHT0);
            setColour(L1, green_light);
            break;
        default:
            break;
    }
    glPopMatrix();
    glutPostRedisplay();
}

void lightMenu2(int id){
    glPushMatrix();
    switch (id) {
        case 1:
            glDisable(GL_LIGHT1);
            break;
        case 2:
            if(!glIsEnabled(GL_LIGHT1)) glEnable(GL_LIGHT1);
            setColour(L2, white_light);
            break;
        case 3:
            if(!glIsEnabled(GL_LIGHT1)) glEnable(GL_LIGHT1);
            setColour(L2, red_light);
            break;
        case 4:
            if(!glIsEnabled(GL_LIGHT1)) glEnable(GL_LIGHT1);
            setColour(L2, blue_light);
            break;
        case 5:
            if(!glIsEnabled(GL_LIGHT1)) glEnable(GL_LIGHT1);
            setColour(L2, green_light);
            break;
        default:
            break;
    }
    glPopMatrix();
    glutPostRedisplay();
}

void lightMenu3(int id){
    glPushMatrix();
    switch (id) {
        case 1:
            glDisable(GL_LIGHT2);
            break;
        case 2:
            if(!glIsEnabled(GL_LIGHT2)) glEnable(GL_LIGHT2);
            setColour(L3, white_light);
            break;
        case 3:
            if(!glIsEnabled(GL_LIGHT2)) glEnable(GL_LIGHT2);
            setColour(L3, red_light);
            break;
        case 4:
            if(!glIsEnabled(GL_LIGHT2)) glEnable(GL_LIGHT2);
            setColour(L3, blue_light);
            break;
        case 5:
            if(!glIsEnabled(GL_LIGHT2)) glEnable(GL_LIGHT2);
            setColour(L3, green_light);
            break;
        default:
            break;
    }
    glPopMatrix();
    glutPostRedisplay();
}

// The material menu simply selects what material the sphere will be, dependant upon the selection.
void materialMenu(int id){
    glPushMatrix();
    switch (id) {
        case 1:
            glMaterialfv(GL_FRONT, GL_SPECULAR, gold_specular);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);
            glMaterialfv(GL_FRONT, GL_SHININESS, gold_shininess);
            break;
        case 2:
            glMaterialfv(GL_FRONT, GL_SPECULAR, silver_specular);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, silver_diffuse);
            glMaterialfv(GL_FRONT, GL_SHININESS, silver_shininess);
            break;
        case 3:
            glMaterialfv(GL_FRONT, GL_SPECULAR, copper_specular);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, copper_diffuse);
            glMaterialfv(GL_FRONT, GL_SHININESS, copper_shininess);
            break;
        default:
            break;
    }
    glPopMatrix();
    glutPostRedisplay();
}

// The elements menu determines the light elements
void elementsMenu(int id){
    glPushMatrix();
    switch (id) {
        case 1:
            setElement(L1, AMBIENT);
            setElement(L2, AMBIENT);
            setElement(L3, AMBIENT);
            break;
        case 2:
            setElement(L1, AMBIENT_DIFFUSE);
            setElement(L2, AMBIENT_DIFFUSE);
            setElement(L3, AMBIENT_DIFFUSE);
            break;
        case 3:
            setElement(L1, AMBIENT_DIFFUSE_SPECULAR);
            setElement(L2, AMBIENT_DIFFUSE_SPECULAR);
            setElement(L3, AMBIENT_DIFFUSE_SPECULAR);
            break;
            
        default:
            break;
    }
    glPopMatrix();
    glutPostRedisplay();
}

// This is the main menu class, which sets up the main menu and all the sub menus
void menu(){
    int light1 = glutCreateMenu(lightMenu1);
        glutAddMenuEntry("Off", 1);
        glutAddMenuEntry("White light", 2);
        glutAddMenuEntry("Red light", 3);
        glutAddMenuEntry("Blue light", 4);
        glutAddMenuEntry("Green light", 5);
    int light2 = glutCreateMenu(lightMenu2);
        glutAddMenuEntry("Off", 1);
        glutAddMenuEntry("White light", 2);
        glutAddMenuEntry("Red light", 3);
        glutAddMenuEntry("Blue light", 4);
        glutAddMenuEntry("Green light", 5);
    int light3 = glutCreateMenu(lightMenu3);
        glutAddMenuEntry("Off", 1);
        glutAddMenuEntry("White light", 2);
        glutAddMenuEntry("Red light", 3);
        glutAddMenuEntry("Blue light", 4);
        glutAddMenuEntry("Green light", 5);
    int material_menu = glutCreateMenu(materialMenu);
        glutAddMenuEntry("Gold", 1);
        glutAddMenuEntry("Silver", 2);
        glutAddMenuEntry("Copper", 3);
    int elements_menu = glutCreateMenu(elementsMenu);
        glutAddMenuEntry("Ambient only", 1);
        glutAddMenuEntry("Ambient and Diffuse", 2);
        glutAddMenuEntry("Ambient, Diffuse and Specular", 3);
    glutCreateMenu(mainMenu);
        glutAddSubMenu("Light 1", light1);
        glutAddSubMenu("Light 2", light2);
        glutAddSubMenu("Light 3", light3);
        glutAddSubMenu("Material Properties", material_menu);
        glutAddSubMenu("Light Elements", elements_menu);
        glutAddMenuEntry("Quit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// main program

int main(int argc, char **argv)

{
    
    glutInit( &argc, argv );
    
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;
    
    glutInitWindowSize(500, 500);
    
    glutInitWindowPosition(100, 100);
    
    
    
    int windowHandle = glutCreateWindow("Athabasca University - Comp390 U8 S2 O1");
    
    glutSetWindow(windowHandle);
    
    
    
    glutDisplayFunc( display );
    
    glutReshapeFunc( reshape );
    
    initialize();
    
    menu();
    
    glutMainLoop();
    
}
