#include <GL/glut.h>

void Inicializa(){
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glClearColor(0.0, 0.0, 1.0, 1.0);
}

void Desenha(){
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		glBegin(GL_TRIANGLES);
			glNormal3f(0.5, 0.5, 0.0);
			glVertex3f(0.5, 0.5, 0.0);
			glNormal3f(-0.5, 0.5, 0.0);
			glVertex3f(-0.5, 0.5, 0.0);
			glNormal3f(0.0, -0.5, 0.0);
			glVertex3f(0.0, -0.5, 0.0);
		glEnd();
	glPopMatrix();
	glutSwapBuffers();
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
