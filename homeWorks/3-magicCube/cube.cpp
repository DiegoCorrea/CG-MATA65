# include <stdio.h>
# include <GL/glut.h>
# define CUBE_DIMENSION 2

const GLfloat edgeLength = 2.0;
const int rotateAngle = 45;

int numberOfCubes = CUBE_DIMENSION*CUBE_DIMENSION*CUBE_DIMENSION;

static int left_angle_x = 0, right_angle_x = 0,
    top_angle_y = 0, bottom_angle_y = 0,
    back_angle_z = 0, front_angle_z = 0;

struct RED_rgb {
  static constexpr GLfloat R = 1.0f;
  static constexpr GLfloat G = 0.0f;
  static constexpr GLfloat B = 0.0f;
} RED;
struct BLACK_rgb {
  static constexpr GLfloat R = 0.0f;
  static constexpr GLfloat G = 0.0f;
  static constexpr GLfloat B = 0.0f;
} BLACK;
struct GREEN_rgb {
  static constexpr GLfloat R = 0.28f;
  static constexpr GLfloat G = 0.44f;
  static constexpr GLfloat B = 0.2f;
} GREEN;
struct BLUE_rgb {
  static constexpr GLfloat R = 0.11f;
  static constexpr GLfloat G = 0.49f;
  static constexpr GLfloat B = 0.95f;
} BLUE;
struct WHITE_rgb {
  static constexpr GLfloat R = 0.63f;
  static constexpr GLfloat G = 0.13f;
  static constexpr GLfloat B = 0.94f;
} WHITE;
struct YELLOW_rgb {
  static constexpr GLfloat R = 0.93f;
  static constexpr GLfloat G = 0.93f;
  static constexpr GLfloat B = 0.0f;
} YELLOW;

void startingFieldOfView() {
  glMatrixMode(GL_PROJECTION);
  glOrtho(-10.0, 10.0, -10.0, 10.0, -5.0, 5.0);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void makeCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, int cubeID) {
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
  glPushMatrix();

  if(centerX > 0){
    glRotatef(right_angle_x, 1, 0, 0);
  } else {
    glRotatef(left_angle_x, 1, 0, 0);
  }
  if(centerY > 0){
    glRotatef(top_angle_y, 0, 1, 0);
  } else {
    glRotatef(bottom_angle_y, 0, 1, 0);
  }
  if(centerZ > 0){
    glRotatef(front_angle_z, 0, 0, 1);
  } else {
    glRotatef(back_angle_z, 0, 0, 1);
  }
  printf("Cube %d: (%0.1f,%0.1f,%0.1f)\n", cubeID, centerX, centerY, centerZ);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);

  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, faces);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glPopMatrix();
}

void drawingMagicCube(void) {
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  int cubeID = 0;
  for(int z = -(CUBE_DIMENSION/2); z <= CUBE_DIMENSION/2; z+=2){
    for(int y = -(CUBE_DIMENSION/2); y <= CUBE_DIMENSION/2; y+=2){
      for(int x = -(CUBE_DIMENSION/2); x <= CUBE_DIMENSION/2; x+=2){
        makeCube((x*(edgeLength/2))*1.0f, (y*(edgeLength/2))*1.0f, (z*(edgeLength/2))*1.0f,cubeID);
        cubeID++;
      }
    }
  }
  glPopMatrix();
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
    // X
    case 'W':
      if((top_angle_y % 90 == 0) && (back_angle_z % 90 == 0) && (bottom_angle_y % 90 == 0) && (front_angle_z % 90 == 0)) {
        left_angle_x += rotateAngle;
        printf("\n++ Key read: {left_angle_x} %d\n", left_angle_x);
        if (abs(left_angle_x) % 360 == 0) {
          left_angle_x = 0;
        }
        glutPostRedisplay();
      }
    break;
    case 'w':
      if((top_angle_y % 90 == 0) && (back_angle_z % 90 == 0) && (bottom_angle_y % 90 == 0) && (front_angle_z % 90 == 0)) {
        left_angle_x -= rotateAngle;
        printf("\n++ Key read: {left_angle_x} %d\n", left_angle_x);
        if (abs(left_angle_x) % 360 == 0) {
          left_angle_x = 0;
        }
        glutPostRedisplay();
      }
    break;
    case 'S':
      if((top_angle_y % 90 == 0) && (back_angle_z % 90 == 0) && (bottom_angle_y % 90 == 0) && (front_angle_z % 90 == 0)) {
        right_angle_x += rotateAngle;
        printf("\n++ Key read: {right_angle_x} %d\n", right_angle_x);
        if (abs(right_angle_x) % 360 == 0) {
          right_angle_x = 0;
        }
        glutPostRedisplay();
      }
    break;
    case 's':
      if((top_angle_y % 90 == 0) && (back_angle_z % 90 == 0) && (bottom_angle_y % 90 == 0) && (front_angle_z % 90 == 0)) {
        right_angle_x -= rotateAngle;
        printf("\n++ Key read: {right_angle_x} %d\n", right_angle_x);
        if (abs(right_angle_x) % 360 == 0) {
          right_angle_x = 0;
        }
        glutPostRedisplay();
      }
    break;
    // Y
    case 'A':
      if ((left_angle_x % 90 == 0) && (back_angle_z % 90 == 0) && (right_angle_x % 90 == 0) && (front_angle_z % 90 == 0)) {
        top_angle_y += rotateAngle;
        printf("\n++ Key read: {top_angle_y} %d\n", top_angle_y);
        if (abs(top_angle_y) % 360 == 0) {
          top_angle_y = 0;
        }
        glutPostRedisplay();
      }
    break;
    case 'a':
      if ((left_angle_x % 90 == 0) && (back_angle_z % 90 == 0) && (right_angle_x % 90 == 0) && (front_angle_z % 90 == 0)) {
        top_angle_y -= rotateAngle;
        printf("\n++ Key read: {top_angle_y} %d\n", top_angle_y);
        if (abs(top_angle_y) % 360 == 0) {
          top_angle_y = 0;
        }
        glutPostRedisplay();
      }
    break;
    case 'D':
      if ((left_angle_x % 90 == 0) && (back_angle_z % 90 == 0) && (right_angle_x % 90 == 0) && (front_angle_z % 90 == 0)) {
        bottom_angle_y += rotateAngle;
        printf("\n++ Key read: {bottom_angle_y} %d\n", bottom_angle_y);
        if (abs(bottom_angle_y) % 360 == 0) {
          bottom_angle_y = 0;
        }
        glutPostRedisplay();
      }
    break;
    case 'd':
      if ((left_angle_x % 90 == 0) && (back_angle_z % 90 == 0) && (right_angle_x % 90 == 0) && (front_angle_z % 90 == 0)) {
        bottom_angle_y -= rotateAngle;
        printf("\n++ Key read: {bottom_angle_y} %d\n", bottom_angle_y);
        if (abs(bottom_angle_y) % 360 == 0) {
          bottom_angle_y = 0;
        }
        glutPostRedisplay();
      }
    break;
    // Z
    case 'Q':
      if ((left_angle_x % 90 == 0) && (top_angle_y % 90 == 0) && (right_angle_x % 90 == 0) && ( bottom_angle_y % 90 == 0)) {
        back_angle_z += rotateAngle;
        printf("\n++ Key read: {back_angle_z} %d\n", back_angle_z);
        if (abs(back_angle_z) % 360 == 0) {
          back_angle_z = 0;
        }
        glutPostRedisplay();
      }
    break;
    case 'q':
      if ((left_angle_x % 90 == 0) && (top_angle_y % 90 == 0) && (right_angle_x % 90 == 0) && ( bottom_angle_y % 90 == 0)) {
        back_angle_z -= rotateAngle;
        printf("\n++ Key read: {back_angle_z} %d\n", back_angle_z);
        if (abs(back_angle_z) % 360 == 0) {
          back_angle_z = 0;
        }
        glutPostRedisplay();
      }
    break;
    case 'E':
      if ((left_angle_x % 90 == 0) && (top_angle_y % 90 == 0) && (right_angle_x % 90 == 0) && ( bottom_angle_y % 90 == 0)) {
        front_angle_z += rotateAngle;
        printf("\n++ Key read: {front_angle_z} %d\n", front_angle_z);
        if (abs(front_angle_z) % 360 == 0) {
          front_angle_z = 0;
        }
        glutPostRedisplay();
      }
    break;
    case 'e':
      if ((left_angle_x % 90 == 0) && (top_angle_y % 90 == 0) && (right_angle_x % 90 == 0) && ( bottom_angle_y % 90 == 0)) {
        front_angle_z -= rotateAngle;
        printf("\n++ Key read: {front_angle_z} %d\n", front_angle_z);
        if (abs(front_angle_z) % 360 == 0) {
          front_angle_z = 0;
        }
        glutPostRedisplay();
      }
    break;

    case 27:
      exit(0);
  }
}
