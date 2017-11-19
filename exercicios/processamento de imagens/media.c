# include <GL/glut.h>
# include <stdlib.h>
# include <stdio.h>

// BMP
int channels = 3;           // RGB channels
unsigned char header[54];   // Each BMP file begins by a 54-bytes header
unsigned int dataPos;       // Position in the file where the actual data begins
unsigned int width, height; // Image width and height
unsigned int imageSize;     // width*height*channels
unsigned char* data;        // Actual RGB data
unsigned char* data_filter; // Actual RGB data
int mask_filter[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

void filtering(){
  data_filter = (unsigned char *)malloc(imageSize);

  int i,j;

  for(i = 0; i < width * height ; i++){
    int index = i*3;
    int m0, m1, m2, m3, m4, m5, m6, m7, m8;
    
    m0 = index-(3*width+3);
    m1 = index-(3*width);
    m2 = index-(3*width-3);
    m3 = index-3;
    m4 = index;
    m5 = index+3;
    m6 = index-(3*width-3);
    m7 = index-(3*width);
    m8 = index-(3*width+3);

    if (m0 > imageSize || m0 < 0)
      m0=m4;
    if (m1 > imageSize || m1 < 0)
      m1=m4;
    if (m2 > imageSize || m2 < 0)
      m2=m4;
    if (m3 > imageSize || m3 < 0)
      m3=m4;
    if (m5 > imageSize || m5 < 0)
      m5=m4;
    if (m6 > imageSize || m6 < 0)
      m6=m4;
    if (m7 > imageSize || m7 < 0)
      m7=m4;
    if (m8 > imageSize || m8 < 0)
      m8=m4;

    m0 = data[m0];
    m1 = data[m1];
    m2 = data[m2];
    m3 = data[m3];
    m4 = data[m4];
    m5 = data[m5];
    m6 = data[m6];
    m7 = data[m7];
    m8 = data[m8];
    
    int pv = (m0*mask_filter[0]+
            m1*mask_filter[1]+
            m2*mask_filter[2]+
            m3*mask_filter[3]+
            m4*mask_filter[4]+
            m5*mask_filter[5]+
            m6*mask_filter[6]+
            m7*mask_filter[7]+
            m8*mask_filter[8])/9.0;

    if(pv<0) pv=0;
    unsigned char R = (unsigned char)pv;
    data_filter[index]=R;
    data_filter[index+1]=R;
    data_filter[index+2]=R;
  }
}

int loadBMP( const char * imagepath){

  // Open the file
  FILE * file = fopen(imagepath,"rb");
  if (!file){printf("Image could not be opened\n"); return 0;}

  if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    return 0;
  }

  if ( header[0]!='B' || header[1]!='M' ){
    printf("Not a correct BMP file\n");
    return 0;
  }

  // Read ints from the byte array
  dataPos    = *(int*)&(header[0x0A]);
  imageSize  = *(int*)&(header[0x22]);
  width      = *(int*)&(header[0x12]);
  height     = *(int*)&(header[0x16]);

  // Some BMP files are misformatted, guess missing information
  if (imageSize==0)    imageSize=width*height*channels; // 3 channels : one byte for each Red, Green and Blue component
  if (dataPos==0)      dataPos=54; // The BMP header is done that way


  // Create a buffer
  data = (unsigned char *)malloc(imageSize);

  // Read the actual data from the file into the buffer
  fread(data,1,imageSize,file);

    int i;
    for(i = 0; i < width * height ; ++i){
     int index = i*3;
     unsigned char B,R;
     B = data[index];
     R = data[index+2];
     data[index] = R;
     data[index+2] = B;
    }

  //Everything is in memory now, the file can be closed
  fclose(file);

}

void init(void)
{
   //glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
   glClearColor (0.0, 0.0, 0.0, 0.0);

}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  //glColor3f (1.0, 1.0, 1.0);

  glRasterPos2i (0, 0);
  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

  filtering();

  glRasterPos2i (width, 0);
  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data_filter);

  glFlush();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho (0, w, 0, h, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(0);
  }
}

int main(int argc, char** argv)
{
    loadBMP(argv[1]);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width*2, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}