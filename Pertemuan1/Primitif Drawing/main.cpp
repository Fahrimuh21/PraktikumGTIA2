#include <gl/glut.h> 

void Point (void){
	//membersihkan layar dan men-set dalam format warna 
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.75, 0.0, 0.25);
	//memastikan seluruh perintah tereksekusi
	glEnd();
	glFlush();
} 

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize (900,1600);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Titik");
	glutDisplayFunc (Point);
	glClearColor (0.0f,0.0f, 1.0f, 1.0f); 
	glutMainLoop(); 
	return 0;
}
