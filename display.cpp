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
// Title: CSG Display Program
// Course: CS 200 
// Semester: Spring year
// Instructor: D. Byrnes
// Date: 2/19/18
// Sources consulted: any books consulted in writing the program
// Program description: Using the function in stlReader.cpp, create a model of a CSG object with OpenGL's TRIANGLES primitive.
// Known bugs: Program does not check to see if the file is of type STL before running. On occasion, some triangles on the shape will not be drawn correctly; this issue is resolved on repeat executions.
// Instructions: Compile and run on the command line. Type the name of the STL file as the first command line option when running. Click and move the mouse to rotate the object in space. Press 'q' to exit the program.

GLint window_width = 500;
GLint window_height = 500;
static int moving = 0, startx = 0, starty = 0;
static GLfloat angle = 0;
static GLfloat angle2 = 0;
std::string filename = "";

void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  std::vector<Facet> newShape = readFile(filename);

  GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_position[] = {0.0, 2.0, -10.0, 0.0};

  GLfloat mat_shininess[] = {50.0};
  GLfloat mat_specular[] = {1.0, 0.0, 0.0, 1.0};
  
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glPushMatrix();
  glRotatef(-1*angle2, 1.0, 0.0, 0.0);
  glRotatef(-1*angle, 0.0, 1.0, 0.0);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_TRIANGLES);
  for(int i = 0; i<newShape.size(); i++){
	glNormal3f(newShape[i].normal[0], newShape[i].normal[1], newShape[i].normal[2]);
	for(int j = 2; j>=0; j--){
	  glVertex3f(newShape[i].vertices[j][0], newShape[i].vertices[j][1], newShape[i].vertices[j][2]);
	}
  }
  glEnd();
  glPopMatrix();
  glutSwapBuffers();
}

void init(){
  glClearColor(0.4, 0.8, 0.9, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -10, 10, -10, 10);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glShadeModel(GL_SMOOTH);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void key(unsigned char keystroke, int x, int y){
  switch(keystroke){
  case 'q':
	exit(0);
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
  if(w <= h)
	glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w, 1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
  else
	glOrtho (-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
  glOrtho(-10, 10, -10, 10, -10, 10);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glutPostRedisplay();
}

int main(int argc, char **argv){
  glutInit(&argc, argv);
  if(argc > 1){
	filename = argv[1];
  }
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(window_width, window_height);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Test Shape");
  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(key);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutMainLoop();
}
