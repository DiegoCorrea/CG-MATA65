#include <GL/glut.h>

void Inicializa(){
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glClearColor(0.0, 0.0, 1.0, 1.0);
}

void Desenha(){
	GLfloat light_position[] = { -1.0, 1.0, -1.0, 0.0 };
	GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
	GLfloat mat_diffuse[]={0.0, 1.0, 0.0, 1.0};

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
		glColor3f(1.0, 0.7, 0.0);
		glutSolidSphere(1.0, 20, 16);
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
