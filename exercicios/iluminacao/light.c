# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>

int lightPosition_z = 0;
int lightPosition_x = 0;
const int angleRotate = 45;
GLfloat light_position[] = { 1.0, 1.0, 0.0, 0.0 };

void init(void) {
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

void display(void) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glPushMatrix();
        glRotatef(lightPosition_z, 0, 0, 1);
        glRotatef(lightPosition_x, 1, 0, 0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
      glPopMatrix();
     glutSolidSphere (1.0, 20, 16);
   glFlush();
}

void reshape (int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void handleKeyboard(unsigned char key, int x, int y);
int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
   glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2,
                        (glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
   glutCreateWindow("Esfera de luz");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(handleKeyboard);
   glutMainLoop();
   return 0;
}

void handleKeyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'a':
      lightPosition_z += angleRotate;
      glutPostRedisplay();
    break;
    case 'd':
      lightPosition_z -= angleRotate;
      glutPostRedisplay();
    break;
    case 'w':
      lightPosition_x += angleRotate;
      glutPostRedisplay();
    break;
    case 's':
      lightPosition_x -= angleRotate;
      glutPostRedisplay();
    break;
    case 27:
      exit(0);
  }
}
