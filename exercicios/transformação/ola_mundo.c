// OpenGL Utility Toolkit
#include <GL/glut.h>

// Apenas requerido pelas aplicacoes em windows
//#include <windows.h>

// Inicializacoes de OpenGL que devem ser
// executadas antes da exibicao do desenho
void Inicializa(){

  // Define a janela de visualizacao
  glMatrixMode(GL_PROJECTION);

  // Define o sistema de coordenadas
  glFrustum(-10.0, 10.0, -10.0, 10.0, 1.0, 30.0);
  //glOrtho(-10.0, 10.0, -10.0, 10.0, 1.0, 3.0);

  // Define a cor de fundo da janela como azul
  glClearColor(0.0, 0.0, 1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
}

void DesenhaTransformacao(){

  // Limpa a janela de visualizacao com a cor
  // de fundo especificada
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  // Define a cor de desenho como vermelho
  glColor3f(1.0, 0.56, 0.0);

  gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glRotatef(45, 0, 0, 1);
  glTranslatef(0.5, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  glutSolidCube(8);
  // Executa os comandos OpenGL para renderizacao
  glFlush();
}

// Funcao callback chamada para fazer o desenho
void Desenha(){

  // Limpa a janela de visualizacao com a cor
  // de fundo especificada
  glClear(GL_COLOR_BUFFER_BIT);

  // Define a cor de desenho como vermelho
  glColor3f(1.0, 0.56, 0.0);
  glRotatef(45, 0, 0, 1);
  glTranslatef(0.5, 0, 0);
  glScalef(0.5, 0.5, 0.5);


  // Desenha um triangulo
  glBegin(GL_QUADS);
    glVertex3f(5.0, 5.0, 5.0);
    glVertex3f(-5.0, 5.0, 5.0);
    glVertex3f(-5.0, -5.0, 5.0);
    glVertex3f(5.0, -5.0, 5.0);

    //
    glVertex3f(5.0, 5.0, -5.0);
    glVertex3f(5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f(-5.0, 5.0, -5.0);

    //
    glVertex3f(-5.0, 5.0, 5.0);
    glVertex3f(-5.0, 5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0, 5.0);

    //
    glVertex3f(5.0, 5.0, 5.0);
    glVertex3f(5.0, -5.0, 5.0);
    glVertex3f(5.0, -5.0, -5.0);
    glVertex3f(5.0, 5.0, -5.0);

    //
    glVertex3f(-5.0, 5.0, -5.0);
    glVertex3f(-5.0, 5.0, 5.0);
    glVertex3f(5.0, 5.0, 5.0);
    glVertex3f(5.0, 5.0, -5.0);

    //
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f(5.0, -5.0, -5.0);
    glVertex3f(5.0, -5.0, 5.0);
    glVertex3f(-5.0, -5.0, 5.0);
  glEnd();

  // Executa os comandos OpenGL para renderizacao
  glFlush();
}

// Programa principal
int main(int argc, char** argv){

  // Inicia GLUT e processa argumentos passados por linha de comandos
  glutInit(&argc, argv);

  // Avisa a GLUT que tipo de modo de exibicao deve ser usado quando a janela eh criada
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  // Cria uma janela GLUT que permite a execucao de comandos OpenGL
  glutCreateWindow("Ola Mundo!");

  // Define a funcao responsavel por redesenhar a janela OpenGL sempre que necessario
  glutDisplayFunc(DesenhaTransformacao);
  

  // Inicializacoes de OpenGL executadas antes da exibicao do desenho
  Inicializa();

  // Inicia o processamento de eventos de GLUT. O controle do programa
  // passa a GLUT, que inicia o gerenciamento dos eventos
  glutMainLoop();

  return 0;
}