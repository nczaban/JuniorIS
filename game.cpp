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
static GLfloat xpos = 0;
static GLfloat ypos = 0;
static GLfloat zpos = 50;
static GLfloat speed = 0.2;

GLfloat light_specular[] = {1, 1, 1, 1.0};
GLfloat light_position[] = {0.0, 1.0, -3.0, 0.0};

std::vector<Facet> asteroids = readFile("asteroid.stl");
std::vector<Facet> spaceship = readFile("spaceship.stl");

struct GameObject{
  double position[3];
  double rotation[3];

  GameObject(){
	for(int i=0;i<3;i++){
	  position[i]=0;
	  rotation[i]=0;
	}
  }
};

std::vector<GameObject> obstacles;

bool upKey, leftKey, rightKey, downKey;

void flight(){
  // Change spaceship position
  zpos -= speed;
  if(zpos <= -100){
	if(speed<1) speed += 0.02;
	zpos = 50*speed+25;
	if(speed*10==int(speed*10)) obstacles.push_back(GameObject());
	for(int i=0; i<obstacles.size(); i++){
	  for(int j=0; j<3; j++){
		obstacles[i].position[j]=float(rand())/RAND_MAX;
		obstacles[i].rotation[j]=float(rand())/RAND_MAX;
	  }
	}
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
  glTranslatef(0,0,-10);
  gluLookAt(xpos, ypos+1, 5,    xpos, ypos, 0,     0,1,0);
  
  glColor3f(0.5, 0.25, 0.25);
  for(int i=0; i<obstacles.size(); i++){
	glPushMatrix();
	glTranslatef(30*obstacles[i].position[0]-15, 30*obstacles[i].position[1]-15, -90*obstacles[i].position[2]-zpos);
	glRotatef(-1.5*zpos, 2*obstacles[i].rotation[0]-1, 2*obstacles[i].rotation[1]-1, 2*obstacles[i].rotation[2]-1);
	glBegin(GL_TRIANGLES);
	for(int j=0; j<asteroids.size(); j++){
	  glNormal3f(-1*asteroids[j].normal[0], -1*asteroids[j].normal[1], asteroids[j].normal[2]);
	  for(int k=2; k>=0; k--){
		glVertex3f(asteroids[j].vertices[k][0], asteroids[j].vertices[k][1], -1*asteroids[j].vertices[k][2]);
	  }
	}
	glEnd();
	glPopMatrix();
  }

  // Draw the spaceship
  glPushMatrix();
  glColor3f(0.4, 0.4, 0.4);
  glTranslatef(xpos, ypos, 1);
  if(leftKey) glRotatef(15, 0, 0, 1);
  if(rightKey) glRotatef(-15, 0, 0, 1);
  if(upKey) glRotatef(15, 1, 0, 0);
  if(downKey) glRotatef(-15, 1, 0, 0);
  
  glBegin(GL_TRIANGLES);
  for(int i = 0; i<spaceship.size(); i++){
	glNormal3f(spaceship[i].normal[0], spaceship[i].normal[1], spaceship[i].normal[2]);
	if((spaceship[i].normal[2] == -1) && (spaceship[i].vertices[0][2] < -1.5)) glColor3f(.4, .6, 1);
	for(int j = 2; j>=0; j--){
	  glVertex3f(spaceship[i].vertices[j][0], spaceship[i].vertices[j][1], -1*spaceship[i].vertices[j][2]);
	}
	glColor3f(0.4, 0.4, 0.4);
  }
  glEnd();
  glPopMatrix();
}

void display (void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setup_scene();
	
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glutSwapBuffers();
}

void init(){
  for(int i=0;i<7;i++){
	GameObject tmp;
	obstacles.push_back(tmp);
	for(int j=0; j<3; j++){
	  obstacles[i].position[j]=float(rand())/RAND_MAX;
	  obstacles[i].rotation[j]=float(rand())/RAND_MAX;
	}
  }
  
  glClearColor(0.1, 0.1, 0.1, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(85, window_width/window_height, 1, 50);
  
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
  gluPerspective(85, GLfloat(w)/GLfloat(h), 1, 50);

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

int main(int argc, char **argv){
  srand(time(NULL));
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
  glutMainLoop();
  return 0;
}
