# include <GL/glut.h>
int angle_x = 0, angle_y = 0, angle_z = 0;

void startingFieldOfView() {

  glMatrixMode(GL_PROJECTION);

  glOrtho(-10.0, 10.0, -10.0, 10.0, -5.0, 5.0);

  glClearColor(1.0, 1.0, 1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
}

void drawingCube() {
  static GLint vertices[8*8*3] = { 
    // Cube 0
    -2.1, -2.1, -2.1,   // v 0
    -2.1, -0.1, -2.1,   // v 1
    -0.1, -0.1, -2.1,   // v 2
    -0.1, -2.1, -2.1,   // v 3
    -2.1, -2.1, -0.1,   // v 4
    -2.1, -0.1, -0.1,   // v 5
    -0.1, -0.1, -0.1,   // v 6
    -0.1, -2.1, -0.1,   // v 7
    // Cube 1
    0.1, -2.1, -2.1,    // v 8
    0.1, -0.1, -2.1,    // v 9
    2.1, -0.1, -2.1,    // v 10
    2.1, -2.1, -2.1,    // v 11
    0.1, -2.1, -0.1,    // v 12
    0.1, -0.1, -0.1,    // v 13
    2.1, -0.1, -0.1,    // v 14
    2.1, -2.1, -0.1,    // v 15
    // Cube 2
    -2.1, 0.1, -2.1,   // v 16
    -2.1, 2.1, -2.1,   // v 17
    -0.1, 2.1, -2.1,   // v 18
    -0.1, 0.1, -2.1,   // v 19
    -2.1, 0.1, -0.1,   // v 20
    -2.1, 2.1, -0.1,   // v 21
    -0.1, 2.1, -0.1,   // v 22
    -0.1, 0.1, -0.1,   // v 23
    // Cube 3
    0.1, 0.1, -2.1,    // v 24
    0.1, 2.1, -2.1,    // v 25
    2.1, 2.1, -2.1,    // v 26
    2.1, 0.1, -2.1,    // v 27
    0.1, 0.1, -0.1,    // v 28
    0.1, 2.1, -0.1,    // v 29
    2.1, 2.1, -0.1,    // v 30
    2.1, 0.1, -0.1,    // v 31
    // Cube 4
    -2.1, -2.1, 0.1,  // v 32
    -2.1, -0.1, 0.1,  // v 33
    -0.1, -0.1, 0.1,  // v 34
    -0.1, -2.1, 0.1,  // v 35
    -2.1, -2.1, 2.1,  // v 36 
    -2.1, -0.1, 2.1,  // v 37 
    -0.1, -0.1, 2.1,  // v 38 
    -0.1, -2.1, 2.1,  // v 39 
    // Cube 5
    0.1, -2.1, 0.1,   // v 40
    0.1, -0.1, 0.1,   // v 41
    2.1, -0.1, 0.1,   // v 42
    2.1, -2.1, 0.1,   // v 43
    0.1, -2.1, 2.1,   // v 44
    0.1, -0.1, 2.1,   // v 45
    2.1, -0.1, 2.1,   // v 46
    2.1, -2.1, 2.1,   // v 47
    // Cube 6
    -2.1, 0.1, 0.1,   // v 48
    -2.1, 2.1, 0.1,   // v 49
    -0.1, 2.1, 0.1,   // v 50
    -0.1, 0.1, 0.1,   // v 51
    -2.1, 0.1, 2.1,   // v 52
    -2.1, 2.1, 2.1,   // v 53
    -0.1, 2.1, 2.1,   // v 54
    -0.1, 0.1, 2.1,   // v 55
    // Cube 7
    0.1, 0.1, 0.1,    // v 56
    0.1, 2.1, 0.1,    // v 57
    2.1, 2.1, 0.1,    // v 58
    2.1, 0.1, 0.1,    // v 59
    0.1, 0.1, 2.1,    // v 60
    0.1, 2.1, 2.1,    // v 61
    2.1, 2.1, 2.1,    // v 62
    2.1, 0.1, 2.1     // v 63
  };
  static GLubyte faces[6*8*4] = { 
    // Cube 0
    0, 1, 2, 3,       // Face 0 Color Red
    5, 4, 7, 6,       // Face 1 Color Black
    0, 4, 5, 1,       // Face 2 Color Blue
    6, 7, 3, 2,       // Face 3 Color Black
    1, 5, 6, 2,       // Face 4 Color Black
    0, 3, 7, 4,       // Face 5 Color White
    // Cube 1
    9, 10, 11, 8,     // Face 0 Color Red
    13, 12, 15, 14,   // Face 1 Color Black
    9, 8, 12, 13,     // Face 2 Color Black
    14, 15, 11, 10,   // Face 3 Color Green
    9, 13, 14, 10,    // Face 4 Color Black
    8, 11, 15, 12,    // Face 5 Color White
    // Cube 2
    17, 18, 19, 16,   // Face 0 Color Red
    20, 23, 22, 21,   // Face 1 Color Black
    17, 16, 20, 21,   // Face 2 Color Blue
    18, 22, 19, 18,   // Face 3 Color Black
    17, 21, 22, 18,   // Face 4 Color Yellow
    16, 19, 23, 20,   // Face 5 Color Black
    // Cube 3
    24, 25, 26, 27,   // Face 0 Color Red
    28, 31, 30, 29,   // Face 1 Color Black
    25, 24, 28, 29,   // Face 2 Color Black
    30, 31, 27, 26,   // Face 3 Color Green
    25, 29, 30, 26,   // Face 4 Color Black
    24, 27, 31, 28,    // Face 5 Color Yellow
    // Cube 4
    32, 33, 34, 35,       // Face 0 Color Red
    36, 39, 38, 37,       // Face 1 Color Black
    32, 36, 37, 33,       // Face 2 Color Blue
    38, 39, 35, 34,       // Face 3 Color Black
    33, 37, 38, 34,       // Face 4 Color Black
    32, 35, 39, 36,       // Face 5 Color White
    // Cube 5
    40, 41, 42, 43,     // Face 0 Color Red
    44, 47, 46, 45,   // Face 1 Color Black
    44, 45, 41, 40,     // Face 2 Color Black
    46, 47, 43, 42,   // Face 3 Color Green
    41, 45, 46, 42,    // Face 4 Color Black
    40, 43, 47, 44,    // Face 5 Color White
    // Cube 6
    48, 49, 50, 51,   // Face 0 Color Red
    52, 55, 54, 53,   // Face 1 Color Black
    49, 48, 52, 53,   // Face 2 Color Blue
    54, 55, 51, 50,   // Face 3 Color Black
    49, 53, 54, 50,   // Face 4 Color Yellow
    48, 51, 55, 52,   // Face 5 Color Black
    // Cube 7
    56, 57, 58, 59,   // Face 0 Color Red
    61, 60, 63, 62,   // Face 1 Color Black
    57, 56, 60, 61,   // Face 2 Color Black
    62, 63, 59, 58,   // Face 3 Color Green
    57, 61, 62, 58,   // Face 4 Color Black
    56, 59, 63, 60    // Face 5 Color Yellow
  };
  static GLfloat colors[8*8*3] = { 
    //Cube 0
    1.0, 0.0, 0.0,      // v 0 Color Red
    1.0, 0.0, 0.0,      // v 1 Color Red
    1.0, 0.0, 0.0,      // v 2 Color Red
    1.0, 0.0, 0.0,      // v 3 Color Red
    1.0, 0.0, 0.0,      // v 4 Color Red
    1.0, 0.0, 0.0,      // v 5 Color Red
    1.0, 0.0, 0.0,      // v 6 Color Red
    1.0, 0.0, 0.0,      // v 7 Color Red
    //Cube 1
    1.0, 0.0, 0.0,      // v 8 Color Red
    0.11, 0.49, 0.95,   // v 9 Color Blue
    1.0, 1.0, 1.0,      // v 10 Color White
    0.2, 0.44, 0.28,    // v 11 Color Green
    0.11, 0.49, 0.95,   // v 12 Color Blue
    0.0, 0.0, 0.0,      // v 13 Color Black
    0.2, 0.44, 0.28,    // v 14 Color Green
    0.11, 0.49, 0.95,   // v 15 Color Blue
    // Cube 2
    0.93, 0.93, 0.0,    // v 16 Color Yellow
    0.2, 0.44, 0.28,    // v 17 Color Green
    1.0, 1.0, 1.0,      // v 10 Color White
    0.2, 0.44, 0.28,    // v 11 Color Green
    0.11, 0.49, 0.95,   // v 12 Color Blue
    0.0, 0.0, 0.0,      // v 13 Color Black
    0.2, 0.44, 0.28,    // v 14 Color Green
    0.11, 0.49, 0.95,   // v 15 Color Blue
    // Cube 3
    0.93, 0.93, 0.0,    // v 16 Color Yellow
    1.0, 1.0, 1.0,      // v 10 Color White
    0.2, 0.44, 0.28,    // v 11 Color Green
    0.11, 0.49, 0.95,   // v 12 Color Blue
    0.0, 0.0, 0.0,      // v 13 Color Black
    0.2, 0.44, 0.28,    // v 14 Color Green
    0.11, 0.49, 0.95,   // v 15 Color Blue
    0.93, 0.93, 0.0,     // v 16 Color Yellow
    //Cube 0
    1.0, 0.0, 0.0,      // v 0 Color Red
    1.0, 0.0, 0.0,      // v 1 Color Red
    1.0, 0.0, 0.0,      // v 2 Color Red
    1.0, 0.0, 0.0,      // v 3 Color Red
    1.0, 0.0, 0.0,      // v 4 Color Red
    1.0, 0.0, 0.0,      // v 5 Color Red
    1.0, 0.0, 0.0,      // v 6 Color Red
    1.0, 0.0, 0.0,      // v 7 Color Red
    //Cube 1
    1.0, 0.0, 0.0,      // v 8 Color Red
    0.11, 0.49, 0.95,   // v 9 Color Blue
    1.0, 1.0, 1.0,      // v 10 Color White
    0.2, 0.44, 0.28,    // v 11 Color Green
    0.11, 0.49, 0.95,   // v 12 Color Blue
    0.0, 0.0, 0.0,      // v 13 Color Black
    0.2, 0.44, 0.28,    // v 14 Color Green
    0.11, 0.49, 0.95,   // v 15 Color Blue
    // Cube 2
    0.93, 0.93, 0.0,    // v 16 Color Yellow
    0.2, 0.44, 0.28,    // v 17 Color Green
    1.0, 1.0, 1.0,      // v 10 Color White
    0.2, 0.44, 0.28,    // v 11 Color Green
    0.11, 0.49, 0.95,   // v 12 Color Blue
    0.0, 0.0, 0.0,      // v 13 Color Black
    0.2, 0.44, 0.28,    // v 14 Color Green
    0.11, 0.49, 0.95,   // v 15 Color Blue
    // Cube 3
    0.93, 0.93, 0.0,    // v 16 Color Yellow
    1.0, 1.0, 1.0,      // v 10 Color White
    0.2, 0.44, 0.28,    // v 11 Color Green
    0.11, 0.49, 0.95,   // v 12 Color Blue
    0.0, 0.0, 0.0,      // v 13 Color Black
    0.2, 0.44, 0.28,    // v 14 Color Green
    0.11, 0.49, 0.95,   // v 15 Color Blue
    0.93, 0.93, 0.0     // v 16 Color Yellow
  };

  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glRotatef(angle_x, 1, 0, 0);
  glRotatef(angle_y, 0, 1, 0);


  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_INT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);

  glDrawElements(GL_QUADS, 192, GL_UNSIGNED_BYTE, faces);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glFlush();
}

void handleKeyboard(unsigned char key, int x, int y) {
  switch(key) {
    case 'w': 
      angle_x+=5;
      glutPostRedisplay();
    break;
    case 's': 
      angle_x-=5;
      glutPostRedisplay();
    break;
    case 'a': 
      angle_y+=5;
      glutPostRedisplay();
    break;
    case 'd': 
      angle_y-=5;
      glutPostRedisplay();
    break;
    case 27:
      exit(0);
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutCreateWindow("Universal Magic Cube");

  glutDisplayFunc(drawingCube);  

  startingFieldOfView();
  
  glutKeyboardFunc(handleKeyboard);

  glutMainLoop();

  return 0;
}