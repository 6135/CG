/*
Em linux, para compilar:
$ gcc -o letraH letraH.c -lGL -lGLU -lglut -lm
*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159
static GLfloat spin = 0.0;
int i;

void init(void)
{
    glClearColor (0.0, 0.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_FILL);
/*    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE); */

    glPushMatrix();
/*    glTranslatef(-10.0,-10.0,0.0);  */
    glLoadIdentity();
/*    glRotatef(spin, 0.0, 1.0, 0.0); */
    glRotatef(spin, 1.0+sin(spin), 1.0-sin(spin), 1.0+cos(spin));  
    glScalef(3.0, 3.0, 3.0);
    
    /*glColor3f (1.0, 0.0, 0.0);*/
    glColor3f(0.5, 0.5, 0.5);
   /* glBegin(GL_POLYGON); { //Main shaft
        glVertex3f(0,-5,0);
        glVertex3f(-2,-5,0);
        glVertex3f(-2,3,0);
        glVertex3f(0,3,0);

    } glEnd();
    { //back stroke curve
        glBegin(GL_POLYGON); { 
            glVertex3f(0,-5,0);
            glVertex3f(0,-6.5,0);
            glVertex3f(-6,-6.5,0);
            glVertex3f(-6,-5,0);
        } glEnd();
    }
    

    glBegin(GL_POLYGON); { //back stroke
        glVertex3f(0,-5,0);
        glVertex3f(0,-6.5,0);
        glVertex3f(-6,-6.5,0);
        glVertex3f(-6,-5,0);
    } glEnd();*/
     
    /*glBegin(GL_QUAD_STRIP);          
    glEnd();*/

    glBegin(GL_QUAD_STRIP); {
        
    } glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void spinDisplay(void)
{
    spin+=0.0001;
    if (spin > 60.0)
        spin=spin-360.0; 
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
    switch (button) {
      case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
	  glutIdleFunc(spinDisplay);
        break;
      case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
	  glutIdleFunc(NULL);
        break;
      default:
        break;
      }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

