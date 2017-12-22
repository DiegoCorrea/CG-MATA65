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
  glClearColor(0.0, 0.0, 1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
}
// Funcao callback chamada para fazer o desenho
void Desenha() {
  static GLint vertices[8*3] = { 
    -1, -1, -1, 
    1, -1, -1, 
    1, 1, -1, 
    -1, 1, -1,
    -1, -1, 1, 
    1, -1, 1, 
    1, 1, 1, 
    -1, 1, 1
  };
  static GLubyte faces[6*4] = { 
    0, 3, 2, 1,
    4, 5, 6, 7, 
    0, 4, 7, 3, 
    1, 2, 6, 5,
    0, 1, 5, 4,
    2, 3, 7, 6

  };
  static GLfloat cores[8*3] = { 
    1.0, 1.0, 1.0, 
    0.5, 0.5, 0.5, 
    0.25, 0.25, 0.25, 
    0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 
    0.5, 0.5, 0.5, 
    0.25, 0.25, 0.25, 
    0.0, 0.0, 0.0
  };

  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glRotatef(angulo_x, 1, 0, 0);
  glRotatef(angulo_y, 0, 1, 0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_INT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, cores);

  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, faces);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glFlush();
}

void keyboard(unsigned char key, int x, int y){
  switch(key) {
    case 'x': 
      angulo_x++;
      glutPostRedisplay();
    break;
    case 'y': 
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