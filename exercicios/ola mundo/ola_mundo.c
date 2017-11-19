#include <GL/glut.h>

void Inicializa(){
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glClearColor(0.0, 0.0, 1.0, 1.0);
}

void Desenha(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.7, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(0.0, -0.5, 0.0);
	glEnd();
	glFlush();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Olá Mundo!");
	glutDisplayFunc(Desenha);
	Inicializa();
	glutMainLoop();
	return 0;
}