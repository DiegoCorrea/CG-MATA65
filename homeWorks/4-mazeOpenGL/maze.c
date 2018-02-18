# include <stdio.h>
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
# include <stdbool.h>
# include "load_texture.h"

int DIMENSION_X = 0, DIMENSION_Z = 0;
int **MAP;

double PERSON_X = 0.0, PERSON_Z = 0.0;

double edgeLength = 1.0;
double viewDistance = 5.0;

bool MAP_VIEW_MODE = false;
int WALL = 1, PLAYER = 2, EXIT_GAME = 3, FLOOR = 4;

GLuint WALL_IMG, FLOOR_IMG, ROOF_IMG;

void initWindow(int argc, char* argv[]);
void startingFieldOfView();
void reshapeWindow(int w, int h);
void handleKeyboard(unsigned char key, int x, int y);
void readEntry(int argc, char** argv);


void createFlorBlock(double x, double y, double z);
void createSideWallBlock(double x, double y, double z);
void createDownWallBlock(double x, double y, double z);

void makeWall();
void makeFloor();
void makeRoof();
void makeWorld();

int main(int argc, char** argv) {
  if(argc == 1) {
    printf("Um arquivo de entrada é necessario\n");
    exit(EXIT_FAILURE);
  }
  readEntry(argc, argv);

  initWindow(argc, argv);

  WALL_IMG = loadBMP("wall.bmp");

  FLOOR_IMG = loadBMP("floor.bmp");
  
  ROOF_IMG = loadBMP("roof.bmp");

  glutDisplayFunc(makeWorld);
  glutKeyboardFunc(handleKeyboard);

  startingFieldOfView();

  glutMainLoop();

  exit(EXIT_SUCCESS);
}
/******************************************************************************/
void handleKeyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'a':
      PERSON_X -= 0.1;
      glLoadIdentity();
      gluLookAt(PERSON_X, edgeLength/2, PERSON_Z, PERSON_X, edgeLength/2, PERSON_Z + viewDistance, 0, 1, 0);
      glutPostRedisplay();
    break;
    case 'd':
      PERSON_X += 0.1;
      glLoadIdentity();
      gluLookAt(PERSON_X, edgeLength/2, PERSON_Z, PERSON_X, edgeLength/2, PERSON_Z + viewDistance, 0, 1, 0);
      glutPostRedisplay();
    break;
    case 'w':
      PERSON_Z += 0.1;
      glLoadIdentity();
      gluLookAt(PERSON_X, edgeLength/2, PERSON_Z, PERSON_X + viewDistance, edgeLength/2, PERSON_Z, 0, 1, 0);
      glutPostRedisplay();
    break;
    case 's':
      PERSON_Z -= 0.1;
      glLoadIdentity();
      gluLookAt(PERSON_X, edgeLength/2, PERSON_Z, PERSON_X + viewDistance, edgeLength/2, PERSON_Z, 0, 1, 0);
      glutPostRedisplay();
    break;
    case 'v':
      if (MAP_VIEW_MODE){
        MAP_VIEW_MODE = false;
        glLoadIdentity();
        gluLookAt(PERSON_X, edgeLength/2, PERSON_Z, PERSON_X, edgeLength/2, PERSON_Z + viewDistance, 0, 1, 0);
        glutPostRedisplay();
      } else {
        MAP_VIEW_MODE = true;
        glLoadIdentity();
        gluLookAt((DIMENSION_X/2.0), ((edgeLength*10.0)/2.0), (DIMENSION_Z/2.0), (DIMENSION_X/2.0), 0.0, (DIMENSION_Z/2.0), 0, 0, DIMENSION_Z/2.0);
        glutPostRedisplay();
      }
    break;
    case 27:
      exit(EXIT_SUCCESS);
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

void startingFieldOfView() {
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  glFrustum(-100.0, 100.0, -100.0, 100.0, 100.0, -100.0);

  glClearColor(1.0, 1.0, 1.0, 1.0);

  glEnable(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_DEPTH_TEST);
}
/* **************************************************************************** */

void readEntry(int argc, char* argv[]) {
  FILE *fl_input;
  fl_input = fopen(argv[1], "r" );

  fscanf(fl_input, "%d %d", &DIMENSION_Z, &DIMENSION_X);
  printf("DIMENSION X: %d -- DIMENSION Z: %d\n",DIMENSION_X, DIMENSION_Z );

  MAP = (int **) malloc(DIMENSION_Z * sizeof(int *));
  for(int i = 0; i < DIMENSION_Z; i++) {
    MAP[i] = (int *) malloc(DIMENSION_X * sizeof(int));
    for(int j = 0, bufferFile = 0; j < DIMENSION_X; j++) {
      fscanf(fl_input, "%d ", &bufferFile);
      printf("%d ", bufferFile);
      MAP[i][j] = bufferFile;
      if (bufferFile == 2) {
        PERSON_X = j;
        PERSON_Z = i;
      }
    }
    printf("\n");
  }
  printf("PERSON X: %f --- Z: %f\n", PERSON_X, PERSON_Z);
  fclose( fl_input );
}


// --------------------- FLOOR ---------------------//
void createFloorBlock(double x, double y, double z) {
  GLuint textureID = FLOOR_IMG;

  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x, y, z);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x, y, z + edgeLength);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x + edgeLength, y, z + edgeLength);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x + edgeLength, y, z);
  glEnd();

  printf("----- { Create Floor Block } -----\n");
  printf("(%f, %f, %f)\n", x, y, z);
  printf("(%f, %f, %f)\n", x, y, z + edgeLength);
  printf("(%f, %f, %f)\n", x + edgeLength, y, z + edgeLength);
  printf("(%f, %f, %f)\n", x + edgeLength, y, z);
  printf("----- -----\n\n");
}

void makeFloor() {
  printf("--------------------------------\n");
  printf("============= FLOOR =============\n");
  printf("--------------------------------\n");
  for(double z = 0.0; z < (DIMENSION_Z - 1); z += 1.0) {
    for(double x = 0.0; x < (DIMENSION_X - 1); x += 1.0) {
      createFloorBlock(x * edgeLength, 0, z * edgeLength);
    }
  }
}

// --------------------- WALL ---------------------//
void createSideWallBlock(double x, double y, double z) {
  GLuint textureID = WALL_IMG;

  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x, y, z);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x + edgeLength, y, z);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x + edgeLength, y + edgeLength, z);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x, y + edgeLength, z);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
    glVertex3f(x, y, z);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x, y + edgeLength, z);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x + edgeLength, y + edgeLength, z);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x + edgeLength, y, z);
  glEnd();

  printf("----- { Create Side Wall Block } -----\n");
  printf("(%f, %f, %f)\n", x, y, z);
  printf("(%f, %f, %f)\n", x + edgeLength, y, z);
  printf("(%f, %f, %f)\n", x + edgeLength, y + edgeLength, z);
  printf("(%f, %f, %f)\n", x, y + edgeLength, z);
  printf("----- -----\n");
  printf("(%f, %f, %f)\n", x, y, z);
  printf("(%f, %f, %f)\n", x, y + edgeLength, z);
  printf("(%f, %f, %f)\n", x + edgeLength, y + edgeLength, z);
  printf("(%f, %f, %f)\n", x + edgeLength, y, z);  
  printf("----- -----\n\n");
}

void createDownWallBlock(double x, double y, double z) {
  GLuint textureID = WALL_IMG;


  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x, y, z);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x, y + edgeLength, z);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x, y + edgeLength, z + edgeLength);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x, y, z + edgeLength);
  glEnd();

  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x, y, z);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x, y, z + edgeLength);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x, y + edgeLength, z + edgeLength);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x, y + edgeLength, z);
  glEnd();

  printf("----- { Create Down Wall Block } -----\n");
  printf("(%f, %f, %f)\n", x, y, z);
  printf("(%f, %f, %f)\n", x, y + edgeLength, z);
  printf("(%f, %f, %f)\n", x, y + edgeLength, z + edgeLength);
  printf("(%f, %f, %f)\n", x, y, z + edgeLength);  
  printf("----- -----\n");
  printf("(%f, %f, %f)\n", x, y, z);
  printf("(%f, %f, %f)\n", x, y, z + edgeLength);
  printf("(%f, %f, %f)\n", x, y + edgeLength, z + edgeLength);
  printf("(%f, %f, %f)\n", x, y + edgeLength, z);  
  printf("----- -----\n\n");
}

void makeWall(){
  printf("--------------------------------\n");
  printf("============= WALL =============\n");
  printf("--------------------------------\n");
  for(double z = 0.0; z < DIMENSION_Z; z += 1.0) {
    for(double x = 0.0; x < DIMENSION_X ; x += 1.0) {
      if ((int)(x+1.0) < DIMENSION_X && MAP[(int)z][(int)x] == WALL && MAP[(int)z][(int)x+1] == WALL) {
        createSideWallBlock(x, 0.0, z);
      }
      if ((int)(z+1.0) < DIMENSION_Z && MAP[(int)z][(int)x] == WALL && MAP[(int)z+1][(int)x] == WALL) {
        createDownWallBlock(x, 0.0, z);
      }
    }
  }
}

// --------------------- ROOF ---------------------//
void createRoofBlock(double x, double y, double z) {
  GLuint textureID = ROOF_IMG;

  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x, y, z);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x + edgeLength, y, z);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x + edgeLength, y, z + edgeLength);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x, y, z + edgeLength);
  glEnd();

  printf("----- { Create Roof Block } -----\n");
  printf("(%f, %f, %f)\n", x, y, z);
  printf("(%f, %f, %f)\n", x + edgeLength, y, z);
  printf("(%f, %f, %f)\n", x + edgeLength, y, z + edgeLength);
  printf("(%f, %f, %f)\n", x, y, z + edgeLength);
  printf("----- -----\n\n");
}

void makeRoof() {
  printf("--------------------------------\n");
  printf("============= ROOF =============\n");
  printf("--------------------------------\n");
  for(double z = 0.0; z < (DIMENSION_Z - 1); z += 1.0) {
    for(double x = 0.0; x < (DIMENSION_X - 1); x += 1.0) {
      createRoofBlock(x * edgeLength, edgeLength, z * edgeLength);
    }
  }
}

// --------------------- PLAYER LOCATION ---------------------//
void createPlayerSphere() {
  
}

// --------------------- Maze The Devil ---------------------//
void makeWorld(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
    if (!MAP_VIEW_MODE) {
      gluLookAt(PERSON_X, edgeLength/2, PERSON_Z, 0, 0, PERSON_Z + viewDistance, 0, 1, 0);
      makeRoof();
    }
    makeFloor();
    makeWall();
  glFlush();
}