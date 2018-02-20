# include <stdio.h>
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
# include <stdbool.h>
# include <math.h>
# include "load_texture.h"

int WALL = 1, PLAYER_START_POSITION = 2, EXIT_GAME = 3, FLOOR = 4;
int DIMENSION_X = 0, DIMENSION_Z = 0;
int **MAP;

double MOVIMENT = 0.1;
int ANGLE_MOVIMENT = 10;

double edgeLength = 1.0;
double viewDistance = 0.0;

bool MAP_VIEW_MODE = false;

struct Player {
  int angle;
  double Eye_x;
  double Eye_y;
  double Eye_z;
  double obj_x;
  double obj_y;
  double obj_z;

  double color_R;
  double color_G;
  double color_B;
  double color_opacity;
} PLAYER;

struct Sun {
  double light_x;
  double light_y;
  double light_z;
  double light_opacity;

  double color_R;
  double color_G;
  double color_B;
  double color_opacity;
} SUN;

struct Texture {
  GLuint wall_ID;
  GLuint floor_ID;
  GLuint roof_ID;
} TEXTURES;

void initWindow(int argc, char* argv[]);
void startingFieldOfView();
void reshapeWindow(int w, int h);

void SpecialKeys(int key, int x, int y);
void handleKeyboard(unsigned char key, int x, int y);

void loadTexture();
void readEntry(int argc, char** argv);
void setVariables();

bool wallSideShock();

void createSun();
void createPlayer();
void createPlayerSphere();

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

  setVariables();

  initWindow(argc, argv);

  startingFieldOfView();

  loadTexture();

  glutDisplayFunc(makeWorld);

  glutKeyboardFunc(handleKeyboard);
  glutSpecialFunc(SpecialKeys);

  glutMainLoop();

  exit(EXIT_SUCCESS);
}
/******************************************************************************/
void readEntry(int argc, char* argv[]) {
  FILE *fl_input;
  fl_input = fopen(argv[1], "r" );

  fscanf(fl_input, "%d %d", &DIMENSION_Z, &DIMENSION_X);

  MAP = (int **) malloc(DIMENSION_Z * sizeof(int *));
  for(int i = 0; i < DIMENSION_Z; i++) {
    MAP[i] = (int *) malloc(DIMENSION_X * sizeof(int));
    for(int j = 0, bufferFile = 0; j < DIMENSION_X; j++) {
      fscanf(fl_input, "%d ", &bufferFile);
      MAP[i][j] = bufferFile;
    }
  }
  fclose( fl_input );
}

void initWindow(int argc, char* argv[]) {
  glutInit(&argc, argv);
  
  glutInitDisplayMode(
    GLUT_SINGLE
    | GLUT_RGB
    | GLUT_DEPTH
  );

  glutInitWindowSize(
    glutGet(GLUT_SCREEN_WIDTH),
    glutGet(GLUT_SCREEN_HEIGHT)
  );

  glutInitWindowPosition(
    (glutGet(GLUT_SCREEN_WIDTH)-640)/2,
    (glutGet(GLUT_SCREEN_HEIGHT)-480)/2
  );

  if(glutCreateWindow("Maze - The Hunter") < 1) {
    exit(EXIT_FAILURE);
  }
}

void startingFieldOfView() {
  glMatrixMode(GL_PROJECTION);

  if (DIMENSION_Z > DIMENSION_X) {
    glFrustum(
      -DIMENSION_Z/2, DIMENSION_Z/2,
      -DIMENSION_Z/2, DIMENSION_Z/2,
      0.0, DIMENSION_Z
    );
  } else {
    glFrustum(
      -DIMENSION_X/2, DIMENSION_X/2,
      -DIMENSION_X/2, DIMENSION_X/2,
      0.0, DIMENSION_X
    );
  }

  glMatrixMode(GL_MODELVIEW);
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glEnable(GL_TEXTURE_2D);

  glEnable(GL_DEPTH_TEST);
}
/* **************************************************************************** */
void loadTexture() {
  unsigned char* data;
  unsigned int width, height;
  glEnable(GL_TEXTURE_2D);


  data = loadBMP("wall.bmp", &width, &height);
  glGenTextures(1, &TEXTURES.wall_ID);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, TEXTURES.wall_ID);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  printf("{Texture} Wall - Width: %d --=-- Height: %d\n", width, height);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


  data = loadBMP("floor.bmp", &width, &height);
  glGenTextures(1, &TEXTURES.floor_ID);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, TEXTURES.floor_ID);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  printf("{Texture} Floor - Width: %d --=-- Height: %d\n", width, height);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


  data = loadBMP("roof.bmp", &width, &height);
  glGenTextures(1, &TEXTURES.roof_ID);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, TEXTURES.roof_ID);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  printf("{Texture} Roof - Width: %d --=-- Height: %d\n", width, height);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void setVariables() {
  printf("**********************************\n");
  printf("============== MAZE ==============\n");
  printf("**********************************\n");

  for(int i = 0; i < DIMENSION_Z; i++) {
    for(int j = 0; j < DIMENSION_X; j++) {
      printf("%d ", MAP[i][j]);
      if (MAP[i][j] == PLAYER_START_POSITION) {
        PLAYER.Eye_x = (double)j;
        PLAYER.Eye_y = (double)edgeLength/2.0;
        PLAYER.Eye_z = (double)i;
      }
    }
    printf("\n");
  }
  viewDistance = DIMENSION_Z/2.0;
  
  PLAYER.angle = 0;
  PLAYER.color_R = 1.0;
  PLAYER.color_G = 0.0;
  PLAYER.color_B = 0.0;
  PLAYER.color_opacity = 1.0;

  SUN.light_x = DIMENSION_X/2.0;
  SUN.light_z = DIMENSION_Z/2.0;
  SUN.light_y = 10*edgeLength;
  SUN.light_opacity = 1.0;

  SUN.color_R = 1.0;
  SUN.color_G = 1.0;
  SUN.color_B = 1.0;
  SUN.color_opacity = 1.0;

  printf("DIMENSION X: %d -- DIMENSION Z: %d\n",DIMENSION_X, DIMENSION_Z );
  printf("PLAYER CAM: (%.3f, %.3f, %.3f)\n", PLAYER.Eye_x, PLAYER.Eye_y, PLAYER.Eye_z);
}
/* **************************************************************************** */

void SpecialKeys(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_LEFT:
      PLAYER.angle -= ANGLE_MOVIMENT;
      if(abs(PLAYER.angle) >= 360)
        PLAYER.angle = 0;
      glutPostRedisplay();
    break;
    case GLUT_KEY_RIGHT:
      PLAYER.angle += ANGLE_MOVIMENT;
      if(abs(PLAYER.angle) >= 360)
        PLAYER.angle = 0;
      glutPostRedisplay();
    break;
    case GLUT_KEY_UP:
      if(abs(PLAYER.angle) >= 0 && abs(PLAYER.angle) < 90) {
        PLAYER.Eye_x += MOVIMENT;
      } else if(abs(PLAYER.angle) >= 90 && abs(PLAYER.angle) < 180) {
        PLAYER.Eye_z += MOVIMENT;
      } else if(abs(PLAYER.angle) >= 190 && abs(PLAYER.angle) < 270) {
        PLAYER.Eye_x -= MOVIMENT;
      } else {
        PLAYER.Eye_z -= MOVIMENT;
      }
      glutPostRedisplay();
    break;
    case GLUT_KEY_DOWN:
      if(abs(PLAYER.angle) >= 0 && abs(PLAYER.angle) < 90) {
        PLAYER.Eye_x -= MOVIMENT;
      } else if(abs(PLAYER.angle) >= 90 && abs(PLAYER.angle) < 180) {
        PLAYER.Eye_z -= MOVIMENT;
      } else if(abs(PLAYER.angle) >= 190 && abs(PLAYER.angle) < 270) {
        PLAYER.Eye_x += MOVIMENT;
      } else {
        PLAYER.Eye_z += MOVIMENT;
      }
      glutPostRedisplay();
    break;
  }
}

void handleKeyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'v':
      if (MAP_VIEW_MODE) {
        MAP_VIEW_MODE = false;
        glutPostRedisplay();
      } else {
        MAP_VIEW_MODE = true;
        gluLookAt(
          SUN.light_x, SUN.light_y, SUN.light_z,
          PLAYER.Eye_x, PLAYER.Eye_y, PLAYER.Eye_z,
          0, 0, 1
        );
        glutPostRedisplay();
      }
    break;
    case 27:
      exit(EXIT_SUCCESS);
  }
}
// --------------------- SUN ---------------------//
void createSun() {
  GLfloat light_position[] = { SUN.light_x, SUN.light_y, SUN.light_z, SUN.light_opacity };
  GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glClearColor (SUN.color_R, SUN.color_G, SUN.color_B, SUN.color_opacity);

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_diffuse);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse);

  glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glPopMatrix();
  glutSwapBuffers();
  glFlush();
}

// --------------------- FLOOR ---------------------//
void createFloorBlock(double x, double y, double z) {
  glPushMatrix();
    glActiveTexture(GL_TEXTURE1);

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
  glPopMatrix();
}

void makeFloor() {
  printf("--------------------------------\n");
  printf("============= FLOOR ============\n");
  printf("--------------------------------\n");
  for(double z = 0.0; z < (DIMENSION_Z - 1); z += 1.0) {
    for(double x = 0.0; x < (DIMENSION_X - 1); x += 1.0) {
      createFloorBlock(x * edgeLength, 0, z * edgeLength);
    }
  }
}

// --------------------- WALL ---------------------//
void createSideWallBlock(double x, double y, double z) {
  glPushMatrix();
    glActiveTexture(GL_TEXTURE0);

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
  glPopMatrix();
}

void createDownWallBlock(double x, double y, double z) {
  glPushMatrix();
    glActiveTexture(GL_TEXTURE0);

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
  glPopMatrix();
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
  glPushMatrix();
    glActiveTexture(GL_TEXTURE2);

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
  glPopMatrix();
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

// --------------------- PLAYER LOCATION --------------------- //
void createPlayerSphere() {
  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(PLAYER.Eye_x, 0, 0);
    glTranslatef(0, 0, PLAYER.Eye_z);
    glutSolidSphere(1.0, 5, 4);
  glPopMatrix();
}

void createPlayer() {
  glPushMatrix();
    gluLookAt(
      PLAYER.Eye_x, PLAYER.Eye_y, PLAYER.Eye_z,
      PLAYER.Eye_x + viewDistance, PLAYER.Eye_y, PLAYER.Eye_z + viewDistance,
      0, 1, 0
    );
  glPopMatrix();
}

// --------------------- Maze The Devil --------------------- //
void makeWorld() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glPushMatrix();
    if(!MAP_VIEW_MODE) {
      makeRoof();
      createPlayer();
    } else {
      createPlayerSphere();
    }
    makeFloor();
    makeWall();
    createSun();
  glPopMatrix();
  glutSwapBuffers();
  glFlush();
}