#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define WIDTH 500
#define HEIGHT 500

float angleY = 0;

void keyboard(unsigned char key, int x, int y) {

}

void reshape(int width, int height)
{
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(20, width / (float) height, 0.5f, 15.0f);
  glViewport(0, 0, width, height);

  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

void dLine3D(float x1, float y1, float z1,
             float x2, float y2, float z2,
             float V1ColorR, float V1ColorG, float V1ColorB,
	     float V2ColorR, float V2ColorG, float V2ColorB)
{
  glBegin(GL_LINES);
    glColor3f(V1ColorR, V1ColorG, V1ColorB);
    glVertex3f(x1, y1, z1);
    glColor3f(V2ColorR, V2ColorG, V2ColorB);
    glVertex3f(x2, y2, z2);
  glEnd();
}

void dSquare( float x1, float y1, float z1,
              float x2, float y2, float z2,
              float x3, float y3, float z3, 
	      float x4, float y4, float z4, 
              float V1ColorR, float V1ColorG, float V1ColorB,
              float V2ColorR, float V2ColorG, float V2ColorB,
              float V3ColorR, float V3ColorG, float V3ColorB,
	      float V4ColorR, float V4ColorG, float V4ColorB)
{
  glBegin(GL_QUADS);
    glColor3f(V1ColorR, V1ColorG, V1ColorB);
    glVertex3f(x1, y1, z1);	
    glColor3f(V2ColorR, V2ColorG, V2ColorB);
    glVertex3f(x2, y2, z2);	
    glColor3f(V3ColorR, V3ColorG, V3ColorB);
    glVertex3f(x3, y3, z3);	
    glColor3f(V4ColorR, V4ColorG, V4ColorB);
    glVertex3f(x4, y4, z4);	
  glEnd();				
}

void drawLines() {
  dLine3D(-1.0f, 0.0f, 0.0f, 
           0.0f, 0.0f, 0.0f,
 	   0.0f, 0.5f, 0.0f,
	   0.0f, 0.5f, 0.0f); 

  dLine3D( 0.0f, 0.0f, 0.0f, 
           1.0f, 0.0f, 0.0f,
 	   0.0f, 0.0f, 0.5f,
	   0.0f, 0.0f, 0.5f); 

  dLine3D( 0.0f, 0.0f, 0.0f, 
	   0.0f, 0.0f, -1.0f, 
	   1.0f, 1.0f, 0.0f,
	   1.0f, 1.0f, 0.0f); 

  dLine3D( 0.0f, 0.0f, 0.0f, 
	   0.0f, 0.0f, 1.0f, 
	   0.5f, 0.0f, 0.0f,
	   0.5f, 0.0f, 0.0f); 

  dLine3D( 0.0f, 0.0f, 0.0f, 
	   0.0f, 1.0f, 0.0f, 
	   0.5f, 0.5f, 0.3f,
	   0.5f, 0.5f, 0.3f); 

  dLine3D( 0.0f, 0.0f, 0.0f, 
	   0.0f,-1.0f, 0.0f, 
	   0.1f, 0.3f, 0.3f,
	   0.1f, 0.3f, 0.3f); 
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glPushMatrix();
    glTranslatef(0, 0, -5);
    drawLines();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 0, -5);
    glRotatef(20, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);

    //TOP
    dSquare(-0.5f, 0.5f, 0.5f, 
       	     0.5f, 0.5f, 0.5f, 	
 	     0.5f, 0.5f,-0.5f,
   	    -0.5f, 0.5f,-0.5f,
 	     1.0f, 0.3f, 1.0f,
 	     1.0f, 0.3f, 1.0f,
  	     1.0f, 0.3f, 1.0f,
             1.0f, 0.3f, 1.0f);

    //BOTTOM
    dSquare(-0.5f,-0.5f, 0.5f, 
      	     0.5f,-0.5f, 0.5f, 	
	     0.5f,-0.5f,-0.5f,
	    -0.5f,-0.5f,-0.5f,
	     1.0f, 1.0f, 0.0f,
	     1.0f, 1.0f, 0.0f,
  	     1.0f, 1.0f, 0.0f,
             1.0f, 1.0f, 0.0f);
  
    //LEFT
    dSquare(-0.5f,-0.5f, 0.5f, 
	    -0.5f, 0.5f, 0.5f, 	
	    -0.5f, 0.5f,-0.5f,
	    -0.5f,-0.5f,-0.5f,
	     0.0f, 0.0f, 0.5f,
	     0.0f, 0.0f, 0.5f,
  	     0.0f, 0.0f, 0.5f,
             0.0f, 0.0f, 0.5f);

    //RIGHT
    dSquare( 0.5f,-0.5f, 0.5f, 
  	     0.5f, 0.5f, 0.5f, 	
  	     0.5f, 0.5f,-0.5f,
  	     0.5f,-0.5f,-0.5f,
  	     0.5f, 0.5f, 0.0f,
  	     0.5f, 0.5f, 0.0f,
    	     0.5f, 0.5f, 0.0f,
             0.5f, 0.5f, 0.0f);
    //BACK
    dSquare(-0.5f,-0.5f,-0.5f, 
	    -0.5f, 0.5f,-0.5f, 	
	     0.5f, 0.5f,-0.5f,
	     0.5f,-0.5f,-0.5f,
	     0.5f, 0.0f, 0.0f,
	     0.5f, 0.0f, 0.0f,
  	     0.5f, 0.0f, 0.0f,
             0.5f, 0.0f, 0.0f);

    //FRONT
    dSquare(-0.5f,-0.5f, 0.5f, 
  	    -0.5f, 0.5f, 0.5f, 	
	     0.5f, 0.5f, 0.5f,
	     0.5f,-0.5f, 0.5f,
	     0.0f, 0.5f, 0.0f,
	     0.0f, 0.5f, 0.0f,
  	     0.0f, 0.5f, 0.0f,
             0.0f, 0.5f, 0.0f);
  glPopMatrix();

  angleY += 0.1;

  glFlush();
  glutSwapBuffers();

  glutPostRedisplay();

}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  glutInitWindowSize(WIDTH, HEIGHT);	
  glutCreateWindow("Spinning Cube");
 
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(&reshape);
  glutMainLoop();

  return 0;
}



 
