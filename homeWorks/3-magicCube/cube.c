// OpenGL Utility Toolkit
#include <GL/glut.h>
int angulo_x = 0, angulo_y = 0;
// Apenas requerido pelas aplicacoes em windows
//#include <windows.h>

// Inicializacoes de OpenGL que devem ser
// executadas antes da exibicao do desenho
void Inicializa() {

  // Define a janela de visualizacao
  glMatrixMode(GL_PROJECTION);

  // Define o sistema de coordenadas
  //glFrustum(-10.0, 10.0, -10.0, 10.0, 1.0, 30.0);
  glOrtho(-5.0, 5.0, -5.0, 5.0, -3.0, 3.0);

  // Define a cor de fundo da janela como azul
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
}
// Funcao callback chamada para fazer o desenho
void Desenha() {
  static GLint vertices[8*4*3] = { 
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
  };
  static GLubyte faces[6*4*4] = { 
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
    24, 27, 31, 28    // Face 5 Color Yellow
    //
  };
  static GLfloat cores[8*4*3] = { 
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
    0.2, 0.44, 0.28,     // v 17 Color Green
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
    0.93, 0.93, 0.0    // v 16 Color Yellow
  };

  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glRotatef(angulo_x, 1, 0, 0);
  glRotatef(angulo_y, 0, 1, 0);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_INT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, cores);

  glDrawElements(GL_QUADS, 96, GL_UNSIGNED_BYTE, faces);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glFlush();
}

void keyboard(unsigned char key, int x, int y){
  switch(key) {
    case 'w': 
      angulo_x++;
      glutPostRedisplay();
    break;
    case 's': 
      angulo_x--;
      glutPostRedisplay();
    break;
    case 'a': 
      angulo_y++;
      glutPostRedisplay();
    break;
    case 'd': 
      angulo_y--;
      glutPostRedisplay();
    break;
    case 27:
      exit(0);
  }
}

// Programa principal
int main(int argc, char** argv){

  // Inicia GLUT e processa argumentos passados por linha de comandos
  glutInit(&argc, argv);

  // Avisa a GLUT que tipo de modo de exibicao deve ser usado quando a janela eh criada
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  // Cria uma janela GLUT que permite a execucao de comandos OpenGL
  glutCreateWindow("Universal Magic Cube");

  // Define a funcao responsavel por redesenhar a janela OpenGL sempre que necessario
  glutDisplayFunc(Desenha);  

  

  // Inicializacoes de OpenGL executadas antes da exibicao do desenho
  Inicializa();
  glutKeyboardFunc(keyboard);
  // Inicia o processamento de eventos de GLUT. O controle do programa
  // passa a GLUT, que inicia o gerenciamento dos eventos
  glutMainLoop();

  return 0;
}