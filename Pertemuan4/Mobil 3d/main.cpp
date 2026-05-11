// Template objek 3D OpenGL GLUT
// Kamera bisa maju, mundur, geser kiri, geser kanan, naik, turun
// Sudah dilengkapi depth dan lighting
// Objek: mobil dari rangka balok manual + roda manual

#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846f

float angle = 0.0f;
float deltaAngle = 0.0f;
float ratio;

float x = 0.0f, y = 3.0f, z = 15.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;

int deltaMoveForward = 0;
int deltaMoveSide = 0;
int deltaMoveVertical = 0;

int h, w;

// Variable untuk pencahayaan
const GLfloat light_ambient[]  = {0.5f, 0.5f, 0.5f, 1.0f};
const GLfloat light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {0.0f, 20.0f, 10.0f, 1.0f};

const GLfloat mat_ambient[]    = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[]    = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[]   = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

void setCamera()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f
    );
}

void Reshape(int w1, int h1)
{
    if (h1 == 0)
        h1 = 1;

    w = w1;
    h = h1;

    ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void orientMe(float ang)
{
    lx = sin(ang);
    lz = -cos(ang);
}

void moveCamera()
{
    float speed = 0.12f;

    // Maju dan mundur
    if (deltaMoveForward != 0)
    {
        x += deltaMoveForward * lx * speed;
        z += deltaMoveForward * lz * speed;
    }

    // Geser kiri dan kanan / strafe
    if (deltaMoveSide != 0)
    {
        x += deltaMoveSide * lz * speed;
        z -= deltaMoveSide * lx * speed;
    }

    // Naik dan turun
    if (deltaMoveVertical != 0)
    {
        y += deltaMoveVertical * speed;
    }
}

void Grid()
{
    double i;

    const float Z_MIN = -50.0f;
    const float Z_MAX =  50.0f;
    const float X_MIN = -50.0f;
    const float X_MAX =  50.0f;
    const float gap = 1.5f;

    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINES);

    for (i = Z_MIN; i < Z_MAX; i += gap)
    {
        glVertex3f(i, 0.0f, Z_MIN);
        glVertex3f(i, 0.0f, Z_MAX);
    }

    for (i = X_MIN; i < X_MAX; i += gap)
    {
        glVertex3f(X_MIN, 0.0f, i);
        glVertex3f(X_MAX, 0.0f, i);
    }

    glEnd();
}

// Balok manual dari 6 sisi.
// Setiap sisi diberi normal agar lighting bekerja.
void Balok(float panjang, float tinggi, float lebar)
{
    float px = panjang / 2.0f;
    float py = tinggi / 2.0f;
    float pz = lebar / 2.0f;

    glBegin(GL_QUADS);

    // Depan
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-px, -py,  pz);
    glVertex3f( px, -py,  pz);
    glVertex3f( px,  py,  pz);
    glVertex3f(-px,  py,  pz);

    // Belakang
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f( px, -py, -pz);
    glVertex3f(-px, -py, -pz);
    glVertex3f(-px,  py, -pz);
    glVertex3f( px,  py, -pz);

    // Kanan
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f( px, -py,  pz);
    glVertex3f( px, -py, -pz);
    glVertex3f( px,  py, -pz);
    glVertex3f( px,  py,  pz);

    // Kiri
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-px, -py, -pz);
    glVertex3f(-px, -py,  pz);
    glVertex3f(-px,  py,  pz);
    glVertex3f(-px,  py, -pz);

    // Atas
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-px,  py,  pz);
    glVertex3f( px,  py,  pz);
    glVertex3f( px,  py, -pz);
    glVertex3f(-px,  py, -pz);

    // Bawah
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-px, -py, -pz);
    glVertex3f( px, -py, -pz);
    glVertex3f( px, -py,  pz);
    glVertex3f(-px, -py,  pz);

    glEnd();
}

// Roda manual berbentuk silinder.
// Axis roda mengarah ke sumbu Z.
void Roda(float radius, float tebal, int segmen)
{
    int i;
    float sudut;
    float px, py;

    glColor3f(0.03f, 0.03f, 0.03f);

    // Sisi luar ban
    glBegin(GL_QUAD_STRIP);

    for (i = 0; i <= segmen; i++)
    {
        sudut = 2.0f * PI * i / segmen;

        px = radius * cos(sudut);
        py = radius * sin(sudut);

        glNormal3f(cos(sudut), sin(sudut), 0.0f);

        glVertex3f(px, py, -tebal / 2.0f);
        glVertex3f(px, py,  tebal / 2.0f);
    }

    glEnd();

    // Tutup depan roda
    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, tebal / 2.0f);

    for (i = 0; i <= segmen; i++)
    {
        sudut = 2.0f * PI * i / segmen;

        px = radius * cos(sudut);
        py = radius * sin(sudut);

        glVertex3f(px, py, tebal / 2.0f);
    }

    glEnd();

    // Tutup belakang roda
    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, -tebal / 2.0f);

    for (i = segmen; i >= 0; i--)
    {
        sudut = 2.0f * PI * i / segmen;

        px = radius * cos(sudut);
        py = radius * sin(sudut);

        glVertex3f(px, py, -tebal / 2.0f);
    }

    glEnd();

    // Velg depan
    glColor3f(0.65f, 0.65f, 0.65f);

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, tebal / 2.0f + 0.01f);

    for (i = 0; i <= segmen; i++)
    {
        sudut = 2.0f * PI * i / segmen;

        px = radius * 0.45f * cos(sudut);
        py = radius * 0.45f * sin(sudut);

        glVertex3f(px, py, tebal / 2.0f + 0.01f);
    }

    glEnd();

    // Velg belakang
    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, -tebal / 2.0f - 0.01f);

    for (i = segmen; i >= 0; i--)
    {
        sudut = 2.0f * PI * i / segmen;

        px = radius * 0.45f * cos(sudut);
        py = radius * 0.45f * sin(sudut);

        glVertex3f(px, py, -tebal / 2.0f - 0.01f);
    }

    glEnd();
}

void Mobil()
{
    // Badan utama mobil
    glPushMatrix();
    glColor3f(0.8f, 0.05f, 0.05f);
    glTranslatef(0.0f, 1.2f, 0.0f);
    Balok(6.0f, 1.2f, 2.4f);
    glPopMatrix();

    // Kabin mobil
    glPushMatrix();
    glColor3f(0.1f, 0.15f, 0.8f);
    glTranslatef(0.4f, 2.2f, 0.0f);
    Balok(2.8f, 1.2f, 2.0f);
    glPopMatrix();

    // Kap depan
    glPushMatrix();
    glColor3f(0.9f, 0.1f, 0.1f);
    glTranslatef(-2.0f, 1.75f, 0.0f);
    Balok(2.0f, 0.5f, 2.2f);
    glPopMatrix();

    // Bagasi belakang
    glPushMatrix();
    glColor3f(0.9f, 0.1f, 0.1f);
    glTranslatef(2.3f, 1.75f, 0.0f);
    Balok(1.5f, 0.5f, 2.2f);
    glPopMatrix();

    // Kaca depan
    glPushMatrix();
    glColor3f(0.2f, 0.7f, 0.9f);
    glTranslatef(-1.05f, 2.25f, 0.0f);
    Balok(0.12f, 0.7f, 1.7f);
    glPopMatrix();

    // Kaca belakang
    glPushMatrix();
    glColor3f(0.2f, 0.7f, 0.9f);
    glTranslatef(1.85f, 2.25f, 0.0f);
    Balok(0.12f, 0.7f, 1.7f);
    glPopMatrix();

    // Kaca samping kanan
    glPushMatrix();
    glColor3f(0.2f, 0.7f, 0.9f);
    glTranslatef(0.4f, 2.25f, 1.05f);
    Balok(1.6f, 0.7f, 0.12f);
    glPopMatrix();

    // Kaca samping kiri
    glPushMatrix();
    glColor3f(0.2f, 0.7f, 0.9f);
    glTranslatef(0.4f, 2.25f, -1.05f);
    Balok(1.6f, 0.7f, 0.12f);
    glPopMatrix();

    // Bumper depan
    glPushMatrix();
    glColor3f(0.15f, 0.15f, 0.15f);
    glTranslatef(-3.2f, 0.9f, 0.0f);
    Balok(0.25f, 0.35f, 2.6f);
    glPopMatrix();

    // Bumper belakang
    glPushMatrix();
    glColor3f(0.15f, 0.15f, 0.15f);
    glTranslatef(3.2f, 0.9f, 0.0f);
    Balok(0.25f, 0.35f, 2.6f);
    glPopMatrix();

    // Lampu depan kanan
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.2f);
    glTranslatef(-3.15f, 1.25f, 0.65f);
    Balok(0.12f, 0.25f, 0.45f);
    glPopMatrix();

    // Lampu depan kiri
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.2f);
    glTranslatef(-3.15f, 1.25f, -0.65f);
    Balok(0.12f, 0.25f, 0.45f);
    glPopMatrix();

    // Lampu belakang kanan
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(3.15f, 1.25f, 0.65f);
    Balok(0.12f, 0.25f, 0.45f);
    glPopMatrix();

    // Lampu belakang kiri
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(3.15f, 1.25f, -0.65f);
    Balok(0.12f, 0.25f, 0.45f);
    glPopMatrix();

    // Roda depan kanan
    glPushMatrix();
    glTranslatef(-2.0f, 0.65f, 1.35f);
    Roda(0.65f, 0.45f, 36);
    glPopMatrix();

    // Roda depan kiri
    glPushMatrix();
    glTranslatef(-2.0f, 0.65f, -1.35f);
    Roda(0.65f, 0.45f, 36);
    glPopMatrix();

    // Roda belakang kanan
    glPushMatrix();
    glTranslatef(2.0f, 0.65f, 1.35f);
    Roda(0.65f, 0.45f, 36);
    glPopMatrix();

    // Roda belakang kiri
    glPushMatrix();
    glTranslatef(2.0f, 0.65f, -1.35f);
    Roda(0.65f, 0.45f, 36);
    glPopMatrix();
}

void display()
{
    moveCamera();

    if (deltaAngle != 0.0f)
    {
        angle += deltaAngle;
        orientMe(angle);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setCamera();

    // Grid tidak memakai lighting karena hanya garis
    glDisable(GL_LIGHTING);
    Grid();
    glEnable(GL_LIGHTING);

    Mobil();

    glutSwapBuffers();
    glFlush();
}

void pressKey(int key, int xPos, int yPos)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            deltaMoveForward = 1;
            break;

        case GLUT_KEY_DOWN:
            deltaMoveForward = -1;
            break;

        case GLUT_KEY_LEFT:
            deltaMoveSide = -1;
            break;

        case GLUT_KEY_RIGHT:
            deltaMoveSide = 1;
            break;
    }
}

void releaseKey(int key, int xPos, int yPos)
{
    switch (key)
    {
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            deltaMoveForward = 0;
            break;

        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            deltaMoveSide = 0;
            break;
    }
}

void keyboardPress(unsigned char key, int xPos, int yPos)
{
    switch (key)
    {
        case 'w':
        case 'W':
            deltaMoveForward = 1;
            break;

        case 's':
        case 'S':
            deltaMoveForward = -1;
            break;

        case 'a':
        case 'A':
            deltaAngle = -0.01f;
            break;

        case 'd':
        case 'D':
            deltaAngle = 0.01f;
            break;

        case 'q':
        case 'Q':
            deltaMoveVertical = 1;
            break;

        case 'e':
        case 'E':
            deltaMoveVertical = -1;
            break;

        case 27:
            exit(0);
            break;
    }
}

void keyboardRelease(unsigned char key, int xPos, int yPos)
{
    switch (key)
    {
        case 'w':
        case 'W':
        case 's':
        case 'S':
            deltaMoveForward = 0;
            break;

        case 'a':
        case 'A':
            if (deltaAngle < 0.0f)
                deltaAngle = 0.0f;
            break;

        case 'd':
        case 'D':
            if (deltaAngle > 0.0f)
                deltaAngle = 0.0f;
            break;

        case 'q':
        case 'Q':
        case 'e':
        case 'E':
            deltaMoveVertical = 0;
            break;
    }
}

void lighting()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
}

void init(void)
{
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_SMOOTH);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Muhammad Fahri (24060124120037)");

    glutIgnoreKeyRepeat(1);

    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    glutKeyboardFunc(keyboardPress);
    glutKeyboardUpFunc(keyboardRelease);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);

    lighting();
    init();

    glutMainLoop();

    return 0;
}
