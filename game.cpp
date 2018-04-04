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
static GLfloat angle2 = 180;
static GLfloat xpos = 0;
static GLfloat ypos = 0;
static GLfloat zpos = 0;
static GLfloat speed = 0.2;

GLfloat light_specular[] = {1, 1, 1, 1.0};
GLfloat light_position[] = {0.0, 3.0, -5.0, 0.0};

std::vector<Facet> asteroids = readFile("asteroid.stl");
std::vector<Facet> spaceship = readFile("spaceship.stl");

bool upKey, leftKey, rightKey, downKey;

void flight(){
  // Change spaceship position
  zpos += speed;
  if(zpos >= 100){
	zpos = 0;
	speed += 0.01;
  }
  if(leftKey){
	if(xpos > -10) xpos -= 0.2;
	else xpos = -10;
  }
  if(rightKey){
	if(xpos < 10) xpos += 0.2;
	else xpos = 10;
  }
  if(upKey){
	if(ypos < 10) ypos += 0.2;
	else ypos = 10;	
  }
  if(downKey){
	if(ypos > -10) ypos -= 0.2;
	else ypos = -10;
  }
  glutPostRedisplay();
}

void setup_scene(){
  gluLookAt(0, -1, 5,    0, 0, 0,     0,1,0);

  glRotatef(-25,0,1,0);
  // Draw the spaceship
  glPushMatrix();
  glColor3f(0.4, 0.4, 0.4);
  glTranslatef(xpos, ypos, 1);
  if(leftKey) glRotatef(15, 0, 0, 1);
  if(rightKey) glRotatef(-15, 0, 0, 1);
  if(upKey) glRotatef(-15, 1, 0, 0);
  if(downKey) glRotatef(15, 1, 0, 0);
  
  glBegin(GL_TRIANGLES);
  for(int i = 0; i<spaceship.size(); i++){
	glNormal3f(spaceship[i].normal[0], spaceship[i].normal[1], spaceship[i].normal[2]);
	if((spaceship[i].normal[2] == -1) && (spaceship[i].vertices[0][2] < -1.5)) glColor3f(.4, .6, 1);
	for(int j = 2; j>=0; j--){
	  glVertex3f(spaceship[i].vertices[j][0], spaceship[i].vertices[j][1], spaceship[i].vertices[j][2]);
	}
	glColor3f(0.4, 0.4, 0.4);
  }
  glEnd();
  glPopMatrix();

  // Draw an asteroid
  glPushMatrix();
  glTranslatef(0, 0, 50-zpos);
  glColor3f(0.5, 0.25, 0.25);
  glBegin(GL_TRIANGLES);
  for(int i = 0; i<asteroids.size(); i++){
  	glNormal3f(asteroids[i].normal[0], asteroids[i].normal[1], asteroids[i].normal[2]);
  	for(int j = 2; j>=0; j--){
  	  glVertex3f(asteroids[i].vertices[j][0], asteroids[i].vertices[j][1], asteroids[i].vertices[j][2]);
  	}
  }
  glEnd();
  glPopMatrix();
}

void display (void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setup_scene();
	glutSwapBuffers();
}

void init(){
  glClearColor(0.1, 0.1, 0.1, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // gluPerspective(85, window_width/window_height, 1, 25);
  glOrtho(-10.5, 10.5, -10.5, 10.5, -5, 50);
  
  glShadeModel(GL_SMOOTH);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
}

void reshape(int w, int h){
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // gluPerspective(85, w/h, 1, 25);

  if(w <= h)
  	glOrtho (-10.5, 10.5, -10.5*(GLfloat)h/(GLfloat)w, 10.5*(GLfloat)h/(GLfloat)w, -50.0, 15.0);
  else
  	glOrtho (-10.5*(GLfloat)w/(GLfloat)h, 10.5*(GLfloat)w/(GLfloat)h, -10.5, 10.5, -50.0, 15.0);

  glutPostRedisplay();
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

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(window_width, window_height);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Spaceship");
  init();

  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(flight);
  glutKeyboardFunc(key);
  glutKeyboardUpFunc(keyUp);
  glutSetKeyRepeat(0);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutMainLoop();
  return 0;
}
