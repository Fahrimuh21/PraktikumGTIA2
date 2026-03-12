#include <gl/glut.h>
#include <math.h>

float wheelAngle = 0.0;

void RenderScene(void)
{
    int i;
    float angle;

    glClear(GL_COLOR_BUFFER_BIT);

    // ================= BADAN MOBIL =================
    glPushMatrix();
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_QUADS);
        glVertex2f(-0.6,-0.1);
        glVertex2f(0.6,-0.1);
        glVertex2f(0.6,0.2);
        glVertex2f(-0.6,0.2);
    glEnd();
    glPopMatrix();


    // ================= ATAP MOBIL =================
    glPushMatrix();
    glColor3f(0.8,0.0,0.0);

    glBegin(GL_QUADS);
        glVertex2f(-0.3,0.2);
        glVertex2f(0.3,0.2);
        glVertex2f(0.15,0.4);
        glVertex2f(-0.15,0.4);
    glEnd();
    glPopMatrix();


    // ================= RODA KIRI =================
    glPushMatrix();
    glTranslatef(-0.35,-0.1,0);
    glRotatef(wheelAngle,0,0,1);

    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        for(i=0;i<100;i++)
        {
            angle = 2*3.14159*i/100;
            glVertex2f(cos(angle)*0.1, sin(angle)*0.1);
        }
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(-0.1,0);
        glVertex2f(0.1,0);
        glVertex2f(0,-0.1);
        glVertex2f(0,0.1);
    glEnd();
    glPopMatrix();


    // ================= RODA KANAN =================
    glPushMatrix();
    glTranslatef(0.35,-0.1,0);
    glRotatef(wheelAngle,0,0,1);

    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        for(i=0;i<100;i++)
        {
            angle = 2*3.14159*i/100;
            glVertex2f(cos(angle)*0.1, sin(angle)*0.1);
        }
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(-0.1,0);
        glVertex2f(0.1,0);
        glVertex2f(0,-0.1);
        glVertex2f(0,0.1);
    glEnd();
    glPopMatrix();

    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Muhammad Fahri (24060124120037)");

    glutDisplayFunc(RenderScene);

    glClearColor(0.5,0.8,1.0,1.0);

    glutMainLoop();
    return 0;
}
