# include <stdio.h>
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>

int DIMENSION_X = 0, DIMENSION_Y = 0;
int *MAP;
int PERSON_X = 0, PERSON_Y = 0;

void initWindow(int argc, char* argv[]);
void reshapeWindow(int w, int h);
void handleKeyboard(unsigned char key, int x, int y);
void readEntry(int argc, char** argv);
int main(int argc, char** argv) {

    /*
    readEntry(argc, argv);
    initWindow(argc, argv);

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyboard);

    glutMainLoop();
    */

    exit(EXIT_SUCCESS);
}
/******************************************************************************/
void handleKeyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'a':
      glutPostRedisplay();
    break;
    case 'd':
      glutPostRedisplay();
    break;
    case 'w':
      glutPostRedisplay();
    break;
    case 's':
      glutPostRedisplay();
    break;
    case 27:
      exit(0);
  }
}

void initWindow(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize (glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
  glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2,
                      (glutGet(GLUT_SCREEN_HEIGHT)-480)/2);

  if(glutCreateWindow("Maze - The Hunter") < 1) {
    exit(EXIT_FAILURE);
  }
  glutReshapeFunc(reshapeWindow);
}

void reshapeWindow(int w, int h) {
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
/******************************************************************************/

void readEntry(int argc, char** argv) {

}
