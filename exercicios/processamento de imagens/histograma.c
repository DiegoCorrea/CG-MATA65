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
unsigned char* data_histogram; // Actual RGB data
int grayLevel[256] = {0};
int totalGray = 0;
float pr[256] = {0};
float sk[256] = {0};


void cinzao(){
  float z = 0.0;
   data_histogram = (unsigned char *)malloc(imageSize);

  for (int i = 0; i < imageSize; i += 3){
    grayLevel[data[i]]++;
    totalGray++;
  }

  for (int i = 0; i < 256; ++i){
    pr[i] = (float)((float)grayLevel[i]/(float)totalGray);
    z += pr[i];
    sk[i] = z*256;
  }
  for (int i = 0; i < imageSize; i += 3){
    data_histogram[i] = sk[data[i]];
    data_histogram[i+1] = sk[data[i]];
    data_histogram[i+2] = sk[data[i]];
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

  cinzao();

  glRasterPos2i (width, 0);
  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data_histogram);
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