#include <gl/glut.h>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,1,0);
    glBegin(GL_QUAD_STRIP);
        glVertex2f(-0.5,0.3);
        glVertex2f(-0.5,-0.3);

        glVertex2f(-0.2,0.3);
        glVertex2f(-0.2,-0.3);

        glVertex2f(0.2,0.3);
        glVertex2f(0.2,-0.3);

        glVertex2f(0.5,0.3);
        glVertex2f(0.5,-0.3);
    glEnd();

    glFlush();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Muhammad Fahri (24060124120037)");
    glutDisplayFunc(display);
    glClearColor(0,0,1,0);
    glutMainLoop();
}
