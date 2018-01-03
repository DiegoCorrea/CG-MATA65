# include <GL/glut.h>
# define CUBE_DIMENSION 2

const GLfloat edgeLength = 2.0;

int numberOfCubes = CUBE_DIMENSION*CUBE_DIMENSION*CUBE_DIMENSION;

int angle_x = 0, angle_y = 0, angle_z = 0;

struct RED_rgb {
  static const GLfloat R = 1.0f;
  static const GLfloat G = 0.0f;
  static const GLfloat B = 0.0f;
} RED;
struct BLACK_rgb {
  static const GLfloat R = 0.0f;
  static const GLfloat G = 0.0f;
  static const GLfloat B = 0.0f;
} BLACK;
struct GREEN_rgb {
  static const GLfloat R = 0.28f;
  static const GLfloat G = 0.44f;
  static const GLfloat B = 0.2f;
} GREEN;
struct BLUE_rgb {
  static const GLfloat R = 0.11f;
  static const GLfloat G = 0.49f;
  static const GLfloat B = 0.95f;
} BLUE;
struct WHITE_rgb {
  static const GLfloat R = 0.63f;
  static const GLfloat G = 0.13f;
  static const GLfloat B = 0.94f;
} WHITE;
struct YELLOW_rgb {
  static const GLfloat R = 0.93f;
  static const GLfloat G = 0.93f;
  static const GLfloat B = 0.0f;
} YELLOW;

void startingFieldOfView() {
  glMatrixMode(GL_PROJECTION);

  glOrtho(-10.0, 10.0, -10.0, 10.0, -5.0, 5.0);

  glClearColor(1.0, 1.0, 1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
}
void makeCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ) {
  GLfloat halfEdgeLength = edgeLength * 0.5f;

  GLfloat vertices[3*4*6] = { 
    centerX - halfEdgeLength, centerY - halfEdgeLength, centerZ - halfEdgeLength,   // v A 0
    centerX - halfEdgeLength, centerY + halfEdgeLength, centerZ - halfEdgeLength,   // v B 1
    centerX + halfEdgeLength, centerY + halfEdgeLength, centerZ - halfEdgeLength,   // v C 2
    centerX + halfEdgeLength, centerY - halfEdgeLength, centerZ - halfEdgeLength,   // v D 3

    centerX - halfEdgeLength, centerY - halfEdgeLength, centerZ + halfEdgeLength,   // v E 4
    centerX + halfEdgeLength, centerY - halfEdgeLength, centerZ + halfEdgeLength,   // v F 5
    centerX + halfEdgeLength, centerY + halfEdgeLength, centerZ + halfEdgeLength,   // v G 6
    centerX - halfEdgeLength, centerY + halfEdgeLength, centerZ + halfEdgeLength,   // v H 7
    
    centerX - halfEdgeLength, centerY - halfEdgeLength, centerZ - halfEdgeLength,   // v A 8
    centerX - halfEdgeLength, centerY - halfEdgeLength, centerZ + halfEdgeLength,   // v E 9
    centerX - halfEdgeLength, centerY + halfEdgeLength, centerZ + halfEdgeLength,   // v H 10
    centerX - halfEdgeLength, centerY + halfEdgeLength, centerZ - halfEdgeLength,   // v B 11

    centerX + halfEdgeLength, centerY + halfEdgeLength, centerZ - halfEdgeLength,   // v C 12
    centerX + halfEdgeLength, centerY + halfEdgeLength, centerZ + halfEdgeLength,   // v G 13
    centerX + halfEdgeLength, centerY - halfEdgeLength, centerZ + halfEdgeLength,   // v F 14
    centerX + halfEdgeLength, centerY - halfEdgeLength, centerZ - halfEdgeLength,   // v D 15

    centerX - halfEdgeLength, centerY + halfEdgeLength, centerZ - halfEdgeLength,   // v B 16
    centerX - halfEdgeLength, centerY + halfEdgeLength, centerZ + halfEdgeLength,   // v H 17
    centerX + halfEdgeLength, centerY + halfEdgeLength, centerZ + halfEdgeLength,   // v G 18
    centerX + halfEdgeLength, centerY + halfEdgeLength, centerZ - halfEdgeLength,   // v C 19

    centerX - halfEdgeLength, centerY - halfEdgeLength, centerZ - halfEdgeLength,   // v A 20
    centerX + halfEdgeLength, centerY - halfEdgeLength, centerZ - halfEdgeLength,   // v D 21
    centerX + halfEdgeLength, centerY - halfEdgeLength, centerZ + halfEdgeLength,   // v F 22
    centerX - halfEdgeLength, centerY - halfEdgeLength, centerZ + halfEdgeLength    // v E 23
  };
  GLubyte faces[6*4] = { 
    // Cube 0
    0, 1, 2, 3,       // Face BACK
    4, 5, 6, 7,       // Face FRONT
    8, 9, 10, 11,     // Face LEFT
    12, 13, 14, 15,   // Face RIGHT
    16, 17, 18, 19,   // Face TOP
    20, 21, 22, 23    // Face BOTTOM
  };
  GLfloat colors[3*4*6] = { 
    RED.R, RED.G, RED.B,
    RED.R, RED.G, RED.B,
    RED.R, RED.G, RED.B,
    RED.R, RED.G, RED.B,
    BLUE.R, BLUE.G, BLUE.B,
    BLUE.R, BLUE.G, BLUE.B,
    BLUE.R, BLUE.G, BLUE.B,
    BLUE.R, BLUE.G, BLUE.B,
    GREEN.R, GREEN.G, GREEN.B,
    GREEN.R, GREEN.G, GREEN.B,
    GREEN.R, GREEN.G, GREEN.B,
    GREEN.R, GREEN.G, GREEN.B,
    WHITE.R, WHITE.G, WHITE.B, 
    WHITE.R, WHITE.G, WHITE.B, 
    WHITE.R, WHITE.G, WHITE.B, 
    WHITE.R, WHITE.G, WHITE.B, 
    BLACK.R, BLACK.G, BLACK.B, 
    BLACK.R, BLACK.G, BLACK.B, 
    BLACK.R, BLACK.G, BLACK.B, 
    BLACK.R, BLACK.G, BLACK.B, 
    YELLOW.R, YELLOW.G, YELLOW.B, 
    YELLOW.R, YELLOW.G, YELLOW.B, 
    YELLOW.R, YELLOW.G, YELLOW.B, 
    YELLOW.R, YELLOW.G, YELLOW.B
  };
  glLoadIdentity();

  glRotatef(angle_x, 1, 0, 0);
  glRotatef(angle_y, 0, 1, 0);
  glRotatef(angle_z, 0, 0, 1);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);

  glDrawElements(GL_QUADS, 72, GL_UNSIGNED_BYTE, faces);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}
void drawingMagicCube(void) {
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for(int z = -(CUBE_DIMENSION/2); z <= CUBE_DIMENSION/2; z+=2){
    for(int y = -(CUBE_DIMENSION/2); y <= CUBE_DIMENSION/2; y+=2){
      for(int x = -(CUBE_DIMENSION/2); x <= CUBE_DIMENSION/2; x+=2){
        makeCube((x*edgeLength/2)*1.0f, (y*edgeLength/2)*1.0f, (z*edgeLength/2)*1.0f);
      }
    }
  }
  glFlush();
}

void handleKeyboard(unsigned char key, int x, int y);
void drawingCube();
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize (glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT)); 
  glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2,
                       (glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
  glutCreateWindow("Universal Magic Cube");

  glutDisplayFunc(drawingMagicCube);  

  startingFieldOfView();
  
  glutKeyboardFunc(handleKeyboard);

  glutMainLoop();

  return 0;
}
void handleKeyboard(unsigned char key, int x, int y) {
  switch(key) {
    case 'w': 
      if (angle_y % 90 == 0 && angle_z % 90 == 0) {
        angle_x+=5;
        glutPostRedisplay();
        if (abs(angle_x) % 360 == 0) {
          angle_x = 0;
        }
      }
    break;
    case 's': 
      if (angle_y % 90 == 0 && angle_z % 90 == 0) {
        angle_x-=5;
        glutPostRedisplay();
        if (abs(angle_x) % 360 == 0) {
          angle_x = 0;
        }
      }
    break;
    case 'a': 
      if (angle_x % 90 == 0 && angle_z % 90 == 0) {
        angle_y+=5;
        glutPostRedisplay();
        if (abs(angle_y) % 360 == 0) {
          angle_y = 0;
        }
      }
    break;
    case 'd': 
      if (angle_x % 90 == 0 && angle_z % 90 == 0) {
        angle_y-=5;
        glutPostRedisplay();
        if (abs(angle_y) % 360 == 0) {
          angle_y = 0;
        }
      }
    break;
    case 'q': 
      if (angle_x % 90 == 0 && angle_y % 90 == 0) {
        angle_z+=5;
        glutPostRedisplay();
        if (abs(angle_z) % 360 == 0) {
          angle_z = 0;
        }
      }
    break;
    case 'e': 
      if (angle_x % 90 == 0 && angle_y % 90 == 0) {
        angle_z-=5;
        glutPostRedisplay();
        if (abs(angle_z) % 360 == 0) {
          angle_z = 0;
        }
      }
    break;
    case 27:
      exit(0);
  }
}
