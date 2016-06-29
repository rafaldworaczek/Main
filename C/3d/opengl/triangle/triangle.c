#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define WIDTH 500
#define HEIGHT 500

GLfloat rotateX = 0.0f;
GLfloat rotateY = 0.0f;
GLfloat rotateZ = 0.0f; 
GLfloat startZ = 10.0f;

void keyboard(unsigned char key, int x, int y) {

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  switch (key) {
    case 'x':
      rotateX -= 0.1f; 
      gluLookAt (rotateX, rotateY, startZ + rotateZ, 
	       0.0, 0.0, 0.0, 
	       0.0, 1.0, 0.0);
      break;

    case 'X':
      rotateX += 0.1f;
      gluLookAt (rotateX, rotateY, startZ + rotateZ, 
		 0.0, 0.0, 0.0, 
		 0.0, 1.0, 0.0);
      break; 

    case 'y':
      rotateY -= 0.1f;
      gluLookAt (rotateX, rotateY, startZ + rotateZ, 
		 0.0, 0.0, 0.0, 
		 0.0, 1.0, 0.0);
      break;

    case 'Y':
      rotateY += 0.1f;
      gluLookAt (rotateX, rotateY, startZ + rotateZ, 
		 0.0, 0.0, 0.0, 
		 0.0, 1.0, 0.0);
      break;

    case 'z': 	 
      rotateZ -= 0.1f;           
      gluLookAt (rotateX, rotateY, startZ + rotateZ, 
                 0.0, 0.0, 0.0, 
		 0.0, 1.0, 0.0);
      break; 

    case 'Z':
      rotateZ += 0.1f;
      gluLookAt (rotateX, rotateY, startZ + rotateZ, 
	       0.0, 0.0, 0.0, 
	       0.0, 1.0, 0.0);
      break;

    default:
      gluLookAt (rotateX, rotateY, startZ + rotateZ, 
	       0.0, 0.0, 0.0, 
	       0.0, 1.0, 0.0);
      break;
}
  glutPostRedisplay(); 

}

void dTiangle(float x1, float y1, float z1,
              float x2, float y2, float z2,
              float x3, float y3, float z3, 
              float V1ColorR, float V1ColorG, float V1ColorB,
              float V2ColorR, float V2ColorG, float V2ColorB,
              float V3ColorR, float V3ColorG, float V3ColorB)

{
  glBegin(GL_TRIANGLES);
    glColor3f(V1ColorR, V1ColorG, V1ColorB);
    glVertex3f(x1, y1, z1);	
    glColor3f(V2ColorR, V2ColorG, V2ColorB);
    glVertex3f(x2, y2, z2);	
    glColor3f(V3ColorR, V3ColorG, V3ColorB);
    glVertex3f(x3 ,y3, z3);
  glEnd();				
 
  glFlush(); 
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
 
  glFlush();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  dTiangle(0, 0, 0, 
	   1, 0, 0, 	
	   0, -0.5, 0,
	   0.3f, 0.0f, 0.0f,
	   0.0f, 0.3f, 0.5f,
	   0.0f, 0.0f, 0.3f);

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
	   0.0f, -1.0f, 0.0f, 
	   0.1f, 0.3f, 0.3f,
	   0.1f, 0.3f, 0.3f); 

  glutSwapBuffers();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGHT);	
  glutCreateWindow("Triangle");

  glMatrixMode (GL_PROJECTION);       
  glLoadIdentity ();
  gluPerspective(20, (GLfloat) WIDTH /(GLfloat) HEIGHT , 0.00, 10.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0, 0, 10,
            0, 0, 0,
            0, 1, 0);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

  return 0;
}



 
