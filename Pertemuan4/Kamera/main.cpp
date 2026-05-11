#include <stdlib.h>   // standard definitions
#include <stdio.h>    // C I/O (for sprintf)
#include <math.h>     // math functions
#include <GL/glut.h>  // GLUT

// Global rotation angles
double rotAngle  = 5;
double rotAngle1 = 10;

//------------------------------------------------------------------
// init
// Sets up default OpenGL values
//------------------------------------------------------------------
void init() {
    glClearColor(0, 0, 0, 0);   // background color
    glClearDepth(1.0);          // depth buffer

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000); // perspective projection

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 0.0, 10.0,  // eye position
        0.0, 0.0, 0.0,  // look-at position
        0.0, 1.0, 0.0   // up vector
    );
}

//------------------------------------------------------------------
// display
// Called when the screen needs to be redrawn
//------------------------------------------------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    // Rotations
    glRotated(rotAngle,  0, 1, 0); // Y-axis
    glRotated(rotAngle1, 1, 0, 0); // X-axis

    // Object color
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0, 0.1, 0.1);

    // Draw object
    glutSolidTeapot(1);

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

//------------------------------------------------------------------
// keyboard
// Handles keyboard input
//------------------------------------------------------------------
void keyboard(unsigned char k, int x, int y) {
    switch (k) {
        case 'a':
            rotAngle += 5;
            break;
        case 'l':
            rotAngle -= 10;
            break;
        case 'y':
            rotAngle1 += 5;
            break;
        case 'b':
            rotAngle1 -= 5;
            break;
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay(); // redraw
}

//------------------------------------------------------------------
// main
//------------------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |  // double buffering
        GLUT_DEPTH  |  // depth buffer
        GLUT_RGB       // RGB color
    );

    glutCreateWindow("Muhammad Fahri (24060124120037)");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();
    return 0;
}
