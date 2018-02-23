# include <GL/glut.h>
# include "load_texture.h"
double z = 2.0;

void Inicializa(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, z, 0, 0, 0, 0, 1, 0);
	glEnable(GL_DEPTH_TEST);
}
void handleKeyboard(unsigned char key, int x, int y){
	switch (key) {
		case 'w':
				z +=	0.1;
			break;
			case 's':
				z -= 0.1;
			break;
	}
	glLoadIdentity();
	gluLookAt(0, 0, z, 0, 0, 0, 0, 1, 0);
	glutPostRedisplay();
}
void Desenha(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLuint textureID = loadBMP("img_test_128x128.bmp");
	glBegin(GL_TRIANGLES);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(0.5, 0.5, 0.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-0.5, 0.5, 0.0);
		glTexCoord2f(0.5, 0.0);
		glVertex3f(0.0, -0.5, 0.0);
	glEnd();

	textureID = loadBMP("parede_512x512.bmp");
	glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(0.5, 0.5, -1.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-0.5, 0.5, -1.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-0.5, -0.5, -1.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(0.5, -0.5, -1.0);
	glEnd();


	glFlush();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(
		glutGet(GLUT_SCREEN_WIDTH),
		glutGet(GLUT_SCREEN_HEIGHT)
	);
  glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH)-640)/2,
	  (glutGet(GLUT_SCREEN_HEIGHT)-480)/2
	);
  glutCreateWindow("Maze - The Hunter");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(handleKeyboard);
	Inicializa();
	glutMainLoop();
	return 0;
}
