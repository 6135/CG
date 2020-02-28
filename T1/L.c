/*
Em linux, para compilar:
$ gcc -o letraH letraH.c -lGL -lGLU -lglut -lm
*/
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.14159
float xdiff = 0.0f;
float ydiff = 0.0f;
float xrot = 0.0f;
float yrot = 0.0f;
bool mouseDown = false;
bool fullscreen = false;

void init(void)
{
    glClearColor (0.0, 0.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}


/*
void spinDisplay(void)
{
    spin+=0.0001;
    if (spin > 60.0)
        spin=spin-360.0; 
    glutPostRedisplay();
}*/

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle()
{
    if (!mouseDown) {
        xrot += 0.3f;
        yrot += 0.4f;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
    case 27 :
        exit(1);
        break;
    }
}

void specialKeyboard(int key, int x, int y) {
    if (key == GLUT_KEY_F1) {
        fullscreen = !fullscreen;

    if (fullscreen)
        glutFullScreen();
    else {
        glutReshapeWindow(500, 500);
        glutPositionWindow(50, 50);
    }
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;

        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
    
}

void mouseMotion(int x, int y) {
    if (mouseDown){
        yrot = x - xdiff;
        xrot = y + ydiff;
        glutPostRedisplay();
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_FILL);

    glPushMatrix();  
    glLoadIdentity();

    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    glScalef(5.0, 5.0, 5.0);
    
    glColor3f (1.0, 0.0, 0.0);

    /**
     * 
     * Front
     *
     */{
        glBegin(GL_POLYGON); { //Main block
            glVertex3f(0,-5,0);
            glVertex3f(-1.5,-5,0);
            glVertex3f(-1.5,7,0);
            glVertex3f(0,7,0);

        } glEnd();
        
        glBegin(GL_POLYGON); { //down stroke
            glVertex3f(6,-5,0);
            glVertex3f(6,-6,0);
            glVertex3f(-3,-6,0);
            glVertex3f(-3,-5,0);
        } glEnd();

        glBegin(GL_POLYGON); { //Bottom, upwards stroke
            glVertex3f(6,-5,0);
            glVertex3f(5.2,-5,0);
            glVertex3f(5.2,-3,0);
            glVertex3f(6,-3,0);

        } glEnd();
        
        glBegin(GL_POLYGON); { //top stroke
            glVertex3f(2.5,7,0);
            glVertex3f(2.5,8,0);
            glVertex3f(-4,8,0);
            glVertex3f(-4,7,0);
        } glEnd();
    }
    /**
     * 
     * Depth
     * 
     */
    {
        glColor3f (0.5, 0.5, 0.5);
        //Main block Right

    glBegin(GL_QUAD_STRIP);
        //Bottom Top Right
        glVertex3f(5.2,-5,0); glVertex3f(5.2,-5,-1);
        glVertex3f(0,-5,0); glVertex3f(0,-5,-1);   

        //Main right
        glVertex3f(0,7,0); glVertex3f(0,7,-1);
        //Top stroke
        glVertex3f(2.5,7,0); glVertex3f(2.5,7,-1);
        glVertex3f(2.5,8,0); glVertex3f(2.5,8,-1);
        glVertex3f(-4,8,0); glVertex3f(-4,8,-1);

        //Main block Left
        //glVertex3f(-1.5,-5,0); glVertex3f(-1.5,7,0);
        //glVertex3f(-1.5,-5,-1); glVertex3f(-1.5,7,-1);     

        //


        /* bOOT
        glBegin(GL_QUAD_STRIP); { 
        

        //Bottom stroke Bottom part
           /* glVertex3f(-1.5,-5,0); glVertex3f(-1.5,7,0);
            glVertex3f(-1.5,-5,-1); glVertex3f(-1.5,7,-1);*/            
    glEnd();
    }
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

