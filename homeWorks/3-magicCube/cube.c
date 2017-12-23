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
  static GLint vertices[9*2*3] = { 
    -1, -1, -1, // v 0
    0, -1, -1,  // v 1
    1, -1, -1,  // v 2
    -1, 0, -1,  // v 3
    0, 0, -1,   // v 4
    1, 0, -1,   // v 5
    -1, 1, -1,  // v 6
    0, 1, -1,   // v 7
    1, 1, -1,   // v 8
    -1, -1, 0,  // v 9
    0, -1, 0,   // v 10
    1, -1, 0,   // v 11
    -1, 0, 0,   // v 12
    0, 0, 0,    // v 13
    1, 0, 0,    // v 14
    -1, 1, 0,   // v 15
    0, 1, 0,    // v 16
    1, 1, 0     // v 17
  };
  static GLubyte faces[6*4*4] = { 
    // Cube 1
    0, 3, 4, 1,     // Face 1 Color Red
    9, 10, 13, 12,  // Face 2 Color Black
    0, 9, 12, 3,    // Face 3 Color Blue
    13, 10, 1, 4,   // Face 4 Color Black
    3, 12, 13, 4,   // Face 5 Color Black
    0, 1, 10, 9,    // Face 6 Color White
    // Cube 2
    1, 4, 5, 2,     // Face 1 Color Red
    10, 11, 14, 13, // Face 2 Color Black
    1, 10, 13, 4,   // Face 3 Color Black
    11, 2, 5, 14,   // Face 4 Color Green
    4, 13, 14, 5,   // Face 5 Color Black
    1, 2, 11, 10,   // Face 6 Color White
    // Cube 3
    3, 6, 7, 4,     // Face 1 Color Red
    12, 13, 16, 15, // Face 2 Color Black
    3, 12, 15, 6,   // Face 3 Color Blue
    16, 13, 4, 7,   // Face 4 Color Black
    6, 15, 16, 7,   // Face 5 Color Yellow
    3, 4, 13, 12,   // Face 6 Color Black
    // Cube 4
    7, 8, 5, 4,     // Face 1 Color Red
    16, 13, 14, 17, // Face 2 Color Black
    7, 4, 13, 16,   // Face 3 Color Black
    17, 14, 5, 8,   // Face 4 Color Green
    16, 17, 8, 7,   // Face 5 Color Black
    13, 4, 5, 14    // Face 6 Color Yellow
    //
  };
  static GLfloat cores[9*2*3] = { 
    1.0, 0.0, 0.0,      // v 0 Color Red
    1.0, 0.0, 0.0,      // v 1 Color Red
    1.0, 0.0, 0.0,      // v 2 Color Red
    1.0, 0.0, 0.0,      // v 3 Color Red
    1.0, 0.0, 0.0,      // v 4 Color Red
    1.0, 0.0, 0.0,      // v 5 Color Red
    1.0, 0.0, 0.0,      // v 6 Color Red
    1.0, 0.0, 0.0,      // v 7 Color Red
    1.0, 0.0, 0.0,      // v 8 Color Red
    0.11, 0.49, 0.95,   // v 9 Color Blue
    1.0, 1.0, 1.0,      // v 10 Color White
    0.2, 0.44, 0.28,    // v 11 Color Green
    0.11, 0.49, 0.95,   // v 12 Color Blue
    0.0, 0.0, 0.0,      // v 13 Color Black
    0.2, 0.44, 0.28,    // v 14 Color Green
    0.11, 0.49, 0.95,   // v 15 Color Blue
    0.93, 0.93, 0.0,    // v 16 Color Yellow
    0.2, 0.44, 0.28     // v 17 Color Green
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
      angulo_x++;
      glutPostRedisplay();
    break;
    case 'a': 
      angulo_y++;
      glutPostRedisplay();
    break;
    case 'd': 
      angulo_y++;
      glutPostRedisplay();
    break;
  }
}

// Programa principal
int main(int argc, char** argv){

  // Inicia GLUT e processa argumentos passados por linha de comandos
  glutInit(&argc, argv);

  // Avisa a GLUT que tipo de modo de exibicao deve ser usado quando a janela eh criada
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  // Cria uma janela GLUT que permite a execucao de comandos OpenGL
  glutCreateWindow("Cubo!");

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