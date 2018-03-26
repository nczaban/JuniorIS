#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include "GL/freeglut.h"
#endif

#include "stlReader.cpp"

// Name: Nicholas Czaban
// Assignment: Final Project 
// Title: CSG Asteroid Game
// Course: CS 200 
// Semester: Spring year
// Instructor: D. Byrnes
// Date: 2/21/18
// Sources consulted: any books consulted in writing the program
// Program description: A simple game where the user navigates a spaceship through an asteroid.
// Known bugs: 
// Creativity: 
// Instructions: Compile and run on the command line.

GLint window_width = 700;
GLint window_height = 700;
static int moving = 0, startx = 0, starty = 0;
static GLfloat angle = 0;
static GLfloat angle2 = 0;
static GLfloat xpos = 0;
static GLfloat ypos = 0;
static GLfloat zpos = 0;
static GLfloat speed = 0.2;

std::vector<Facet> asteroids = readFile("pipes.stl");
std::vector<Facet> spaceship = readFile("spaceship.stl");

bool upKey, leftKey, rightKey, downKey;

void test_draw(){
  gluLookAt(0,0,0,
			0,0,1,
			0,0,1);
  glBegin(GL_TRIANGLES);
  glVertex3f(-1,-1,1);
  glVertex3f(0,1,1);
  glVertex3f(1,-1,1);
  glEnd();
}

void display (void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	test_draw();
	glutSwapBuffers();
}

void init(){
  glClearColor(0.1, 0.1, 0.1, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(85, window_width/window_height, 1, 25);
  
  glShadeModel(GL_SMOOTH);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
}

void key(unsigned char keystroke, int x, int y){
  switch(keystroke){
  case 'q':
	exit(0);
	break;
  case 'a':
	leftKey = true;
	break;
  case 'd':
	rightKey = true;
	break;
  case 'w':
	upKey = true;
	break;
  case 's':
	downKey = true;
	break;
  }
}
void keyUp(unsigned char keystroke, int x, int y){
  switch(keystroke){
  case 'a':
	leftKey = false;
	break;
  case 'd':
	rightKey = false;
	break;
  case 'w':
	upKey = false;
	break;
  case 's':
	downKey = false;
	break;
  }
}

static void mouse(int button, int state, int x, int y){
  if (button == GLUT_LEFT_BUTTON){
    if (state == GLUT_DOWN){
      moving = 1;
      startx = x;
      starty = y;
    }
    if (state == GLUT_UP){
      moving = 0;
    }
  }
}

static void motion(int x, int y){
  if(moving){
	angle = angle + (x - startx);
	angle2 = angle2 + (y - starty);
	startx = x;
	starty = y;
	glutPostRedisplay();
  }
}

void reshape(int w, int h){
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(85, w/h, 1, 25);
  /*
  if(w <= h)
	glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w, 1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
  else
	glOrtho (-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
  glOrtho(-10, 10, -10, 10, -10, 10);
  */
  glutPostRedisplay();
}

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(window_width, window_height);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Spaceship");
  init();

  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  //  glutIdleFunc(flight);
  glutKeyboardFunc(key);
  glutKeyboardUpFunc(keyUp);
  glutSetKeyRepeat(0);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutMainLoop();
  return 0;
}
