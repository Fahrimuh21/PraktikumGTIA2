#include <GL/glut.h>
#include <stdlib.h>

// Variabel rotasi
static int shoulder = 0, elbow = 0;
float curl = 0.0;       // buka-tutup jari
int animating = 0;      // toggle animasi

// Inisialisasi
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

// ===== FUNGSI GAMBAR 1 JARI =====
void drawFinger()
{
    for (int i = 0; i < 3; i++)
    {
        glRotatef(curl, 0.0, 0.0, 1.0);
        glTranslatef(0.3, 0.0, 0.0);

        glPushMatrix();
            glScalef(0.6, 0.15, 0.15);
            glutWireCube(1.0);
        glPopMatrix();

        glTranslatef(0.3, 0.0, 0.0);
    }
}

// Fungsi untuk menggambar
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // ===== SHOULDER =====
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    // Lengan atas
    glPushMatrix();
        glScalef(2.0, 0.4, 1.0);
        glutWireCube(1.0);
    glPopMatrix();

    // ===== ELBOW =====
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    // Lengan bawah
    glPushMatrix();
        glScalef(2.0, 0.4, 1.0);
        glutWireCube(1.0);
    glPopMatrix();

    // ===== TELAPAK =====
    glTranslatef(1.0, 0.0, 0.0);

    glPushMatrix();
        glScalef(0.8, 0.6, 0.4);
        glutWireCube(1.0);
    glPopMatrix();

    // ===== 5 JARI =====
    for (int i = 0; i < 5; i++)
    {
        glPushMatrix();

        // posisi jari di telapak
        glTranslatef(0.5, 0.3 - (i * 0.15), 0.0);

        drawFinger();

        glPopMatrix();
    }

    glPopMatrix();
    glutSwapBuffers();
}

// Fungsi resize window
void reshape(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -6.0);
}

// Animasi buka-tutup jari
void idle()
{
    if (animating)
    {
        curl += 0.5;
        if (curl > 90) curl = 0;

        glutPostRedisplay();
    }
}

// Kontrol keyboard
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 's':
            shoulder = (shoulder + 5) % 360;
            break;
        case 'S':
            shoulder = (shoulder - 5) % 360;
            break;

        case 'e':
            elbow = (elbow + 5) % 360;
            break;
        case 'E':
            elbow = (elbow - 5) % 360;
            break;

        case 'o': // buka tangan
            curl = 0;
            break;

        case 'c': // kepal tangan
            curl = 90;
            break;
        case 27: // ESC
            exit(0);
            break;
    }

    glutPostRedisplay();
}

// Main
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Muhammad Fahri (24060124120037)");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
