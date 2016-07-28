/*
#################################################################
# This program demonstrates chasing of two objects.             #
# Use keyboard arrows (up/down/left/right) to navigate cube 1.  #
# Cube 2 chases cube 2 using vectors.	   		        #
# Use x/X/y/Y/z/Z keyboard keys to rotate objects.		#
# Increase/decrease speed of chasing using p2Speed variable.    #
#################################################################
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
#define MIN_NR_VERTEX 20
#define NR_COLORS 24 

#define MAX_PLAYERS 3

GLfloat rotateX = 0.0f;
GLfloat rotateY = 0.0f;
GLfloat rotateZ = 0.0f; 
GLfloat startZ = 5.0f;

//Init pos of players
struct coordinate p[MAX_PLAYERS];
struct coordinate pCurr[MAX_PLAYERS];

GLfloat WALK_STEP = 0.1f;

int now_t = 0, prev_t = 0;

Object player1 = {
  .point = {  -0.05f, 0.00f, 0.05f,
              -0.05f, 0.05f, 0.05f,
               0.05f, 0.05f, 0.05f,
               0.05f, 0.00f, 0.05f,
	      -0.05f, 0.00f,-0.05f,
              -0.05f, 0.05f,-0.05f,
               0.05f, 0.05f,-0.05f,
               0.05f, 0.00f,-0.05f,	
	},

//front, back, left, right, top, bottom
	.c = { 0.0f, 0.5f, 0.0f,
               0.0f, 0.5f, 0.0f,
               0.0f, 0.5f, 0.0f,
               0.0f, 0.5f, 0.0f,
               0.05f, 0.0f, 0.0f,
               0.0f, 0.0f, 0.0f,
               0.05f, 0.0f, 0.0f,
               0.05f, 0.0f, 0.0f,
               0.0f, 0.0f, 0.05f,
               0.0f, 0.0f, 0.05f,
               0.0f, 0.0f, 0.05f,
               0.0f, 0.0f, 0.05f,
               0.05f, 0.05f, 0.0f,
               0.05f, 0.05f, 0.0f,
               0.05f, 0.05f, 0.0f,
               0.05f, 0.05f, 0.0f,
               1.0f, 0.3f, 1.0f,
               1.0f, 0.3f, 1.0f,
               1.0f, 0.3f, 1.0f,
               1.0f, 0.3f, 1.0f,
               1.0f, 1.0f, 0.0f,
               1.0f, 1.0f, 0.0f,
               1.0f, 1.0f, 0.0f,
               1.0f, 1.0f, 0.0f, 
	},
};

Object player2 = {
  .point = {  -0.5f, 0.00f, 0.05f,
              -0.5f, 0.05f, 0.05f,
              -0.45f, 0.05f, 0.05f,
              -0.45f, 0.00f, 0.05f,
	      -0.5f, 0.00f,-0.05f,
              -0.5f, 0.05f,-0.05f,
              -0.45f, 0.05f,-0.05f,
              -0.45f, 0.00f,-0.05f,	
	},

//front, back, left, right, top, bottom
	.c = { 0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f,
               0.0f, 0.0f, 1.0f, 
	},
};

void init() {

  p[1].x = pCurr[1].x = 0.0f;
  p[1].y = pCurr[1].y = 0.0f; 
  p[1].z = pCurr[1].z = 0.0f;
  
  p[2].x = pCurr[2].x = -0.475f;
  p[2].y = pCurr[2].y = 0.00f; 
  p[2].z = pCurr[2].z = 0.0f;

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

  switch (key) {
    case GLUT_KEY_UP: 
      pCurr[1].z -= WALK_STEP;
    break;

    case GLUT_KEY_DOWN:
      pCurr[1].z += WALK_STEP;
    break;

    case GLUT_KEY_LEFT:
      pCurr[1].x -= WALK_STEP;
    break;

    case GLUT_KEY_RIGHT:
      pCurr[1].x += WALK_STEP;
    break;
  }
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

void DrawPlayer(Object *obj) {

  glBegin(GL_QUADS);
    DrawSquare(obj, 0, 1, 2, 3, 0, 1, 2, 3);     //Front  
    DrawSquare(obj, 4, 5, 6, 7, 4, 5, 6, 7);     //Back
    DrawSquare(obj, 0, 1, 5, 4, 8, 9, 10, 11);   //Left 
    DrawSquare(obj, 2, 3, 7, 6, 12, 13, 14, 15); //Right
    DrawSquare(obj, 1, 2, 6, 5, 16, 17, 18, 19); //Top
    DrawSquare(obj, 0, 3, 7, 4, 20, 21, 22, 23); //Bottom
  glEnd(); 
}

void display() {
  float x, z;
  float deltaTime;
  float p2Speed = 0.20f;
  float stepX, stepZ;
  int i = 0;
  Vec chase;
  Vec move;
  float len = 0;

  now_t = glutGet(GLUT_ELAPSED_TIME);
  deltaTime = (now_t - prev_t) / 1000.0f;
  prev_t = now_t;  

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glPushMatrix();
    gluLookAt (rotateX, rotateY, startZ + rotateZ,
               0.0, 0.0, 0.0,
               0.0, 1.0, 0.0);

    glRotatef(10, 0, 1, 0);
    glRotatef(20, 1, 0, 0);
    drawLines();

    stepX = 0.08f;
    stepZ = 0.08f;    

    //Draw surface 
    for (z = -1; z < 0.99; z += stepZ) {
      for (x = -1; x < 0.99f; x += stepX) {

        if ((i++) % 2) { 		
          dSquare( x, 	       0.0f, z, 
                   x + stepX,  0.0f, z, 	
                   x + stepX,  0.0f, z + stepZ,
                   x,  	       0.0f, z + stepZ,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f);
        } else {
 	  dSquare( x, 	       0.0f, z, 
                   x + stepX,  0.0f, z, 	
                   x + stepX,  0.0f, z + stepZ,
                   x,  	       0.0f, z + stepZ,
                   1.0f, 0.0f, 0.0f,
                   1.0f, 0.0f, 0.0f,
                   1.0f, 0.0f, 0.0f,
                   1.0f, 0.0f, 0.0f);
        } 
     }
  }  
  glPopMatrix();

  glPushMatrix();
    gluLookAt (rotateX, rotateY, startZ + rotateZ,
               0.0, 0.0, 0.0,
               0.0, 1.0, 0.0);

    glRotatef(10, 0, 1, 0);
    glRotatef(20, 1, 0, 0);

    chase.x = pCurr[1].x - pCurr[2].x;
    chase.y = pCurr[1].y - pCurr[2].y;
    chase.z = pCurr[1].z - pCurr[2].z;

    len = sqrt((chase.x * chase.x) + (chase.y * chase.y) + 
	       (chase.z * chase.z)); 

    //Normalize vector
    move.x = chase.x / len;
    move.y = chase.y / len;
    move.z = chase.z / len;

    pCurr[2].x += (move.x * p2Speed) * deltaTime; 
    pCurr[2].y += (move.y * p2Speed) * deltaTime; 
    pCurr[2].z += (move.z * p2Speed) * deltaTime;

    glTranslatef(pCurr[2].x - p[2].x,  
		 pCurr[2].y - p[2].y,
		 pCurr[2].z - p[2].z);
    DrawPlayer(&player2);

  glPopMatrix();

  glPushMatrix();
    gluLookAt (rotateX, rotateY, startZ + rotateZ,
               0.0, 0.0, 0.0,
               0.0, 1.0, 0.0);

    glRotatef(10, 0, 1, 0);
    glRotatef(20, 1, 0, 0);
  
    glTranslatef(pCurr[1].x, pCurr[1].y, pCurr[1].z);
    DrawPlayer(&player1);
  glPopMatrix();

  glFlush();
  glutSwapBuffers();

  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  glutInitWindowSize(WIDTH, HEIGHT);	
  glutCreateWindow("Chase");
 
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

