/*
##########################################################################
# This program demonstrates the use of trigonometric functions (sin,cos) #   
# to rotate object around point 0,0.                                     # 
# You can modify ANGLE macro to change degrees of rotation               #
# (default is 1 degree).                                                 #
# Use x/X/y/Y/z/Z keyboard keys to rotate plane.                         #
##########################################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "general.h"

#define WIDTH 800
#define HEIGHT 800

#define ANGLE 1.0f

GLfloat rotateX = 0.0f;
GLfloat rotateY = 0.0f;
GLfloat rotateZ = 0.0f; 
GLfloat startZ = 5.0f;

Object square1 = {
  .nrPoints = 4,
  .angle = 0.0f,
  .point = { 0.20f, 0.00f, 0.00f,
             0.40f, 0.00f, 0.00f,
             0.40f, 0.05f, 0.00f,
             0.20f, 0.05f, 0.00f,
   	   },

	.c = { 0.5f, 0.5f, 0.0f,
               0.5f, 0.5f, 0.0f,
               0.5f, 0.5f, 0.0f,
               0.5f, 0.5f, 0.0f,
	},
};

void init() {

}

void keyboard(unsigned char key, int x, int y) {

  switch (key) {
    case 'x':
      rotateX -= 0.1f; 
      break;

    case 'X':
      rotateX += 0.1f;
      break; 

    case 'y':
      rotateY -= 0.1f;
      break;

    case 'Y':
      rotateY += 0.1f;
      break;

    case 'z': 	 
      rotateZ -= 0.1f;           
      break; 

    case 'Z':
      rotateZ += 0.1f;
      break;

  }
}

void keyboardSpecial(int key, int x, int y) {

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

void DrawSquare(Object *obj, int x1, int x2, int x3, int x4,
		        int c1, int c2, int c3, int c4) 	
{
  glBegin(GL_QUADS);
    glColor3f(obj->c[c1].r, obj->c[c1].g, obj->c[c1].b);
    glVertex3f(obj->point[x1].x, obj->point[x1].y, obj->point[x1].z);

    glColor3f(obj->c[c2].r, obj->c[c2].g, obj->c[c2].b);
    glVertex3f(obj->point[x2].x, obj->point[x2].y, obj->point[x2].z);

    glColor3f(obj->c[c3].r, obj->c[c3].g, obj->c[c3].b);
    glVertex3f(obj->point[x3].x, obj->point[x3].y, obj->point[x3].z);

    glColor3f(obj->c[c4].r, obj->c[c4].g, obj->c[c4].b);
    glVertex3f(obj->point[x4].x, obj->point[x4].y, obj->point[x4].z);

  glEnd(); 
}

void rotateAroundZeroZero(Object *obj, float angle, int NrPoints) {
  int i;
  float x, y;

  for (i = 0; i < NrPoints; i++) {
       x = obj->point[i].x;
       y = obj->point[i].y;
  
       obj->point[i].x = (x * cos(angle)) - 
		         (y * sin(angle));

       obj->point[i].y = (x * sin(angle)) + 
		         (y * cos(angle));
   }
}

float degreeToRadian(float degrees) {
  return (M_PI * degrees) / 180;
}

void display() {
  float x, z;
  int i = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glPushMatrix();
    gluLookAt (rotateX, rotateY, startZ + rotateZ,
               0.0, 0.0, 0.0,
               0.0, 1.0, 0.0);

    glRotatef(10, 0, 1, 0);
    glRotatef(20, 1, 0, 0);
    drawLines();
    DrawSquare(&square1, 0, 1, 2, 3, 0, 1, 2, 3); 
    square1.angle = degreeToRadian(ANGLE); 
    rotateAroundZeroZero(&square1, square1.angle, square1.nrPoints);

  glPopMatrix();

  glFlush();
  glutSwapBuffers();

  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  glutInitWindowSize(WIDTH, HEIGHT);	
  glutCreateWindow("rotateMath");
 
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);

  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboardSpecial);
  glutReshapeFunc(&reshape);
  glutMainLoop();

  return 0;
}

