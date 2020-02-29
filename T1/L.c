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
     * Front
     */{
        glBegin(GL_QUAD_STRIP); { //Main block
            glVertex3f(0,-5,0);glVertex3f(0,7,0);
            glVertex3f(-1.5,-5,0);glVertex3f(-1.5,7,0);
        } glEnd();
        
        glBegin(GL_QUAD_STRIP); { //down stroke
            glVertex3f(-3.5,-5,0);glVertex3f(-3.5,-6,0);
            glVertex3f(-2,-5,0);glVertex3f(-1,-6,0);
            
            glVertex3f(-2,-5,0);glVertex3f(-2,-6,0); //start curve
            glVertex3f(-1.75,-4.7,0);glVertex3f(-1.75,-6,0);//midle of the curve
            glVertex3f(-1.5,-4.5,0);glVertex3f(-1.5,-6,0);//end end

            glVertex3f(0,-4.5,0);glVertex3f(0,-6,0);//start curve
            glVertex3f(.25,-4.7,0);glVertex3f(.25,-6,0);//midle of the curve
            glVertex3f(.5,-5,0);glVertex3f(.5,-6,0); //end end

            //dist entre cada X aumenta por 0.1 para cada ponto
            /**
             * 5.9 - 5.8 = 0.1
             * 5.8 - 5.6 = 0.2
             * 5.6 - 5.3 = 0.3
             * 5.3 - 4.9 = 0.4 etc
             **/
            
            glVertex3f(3.9,-5,0);glVertex3f(3.9,-6,0);
            glVertex3f(4.4,-4.9,0);glVertex3f(5.7,-5.9,0);
            glVertex3f(4.9,-4.8,0);glVertex3f(5.9,-5,0);
            glVertex3f(5.3,-4.5,0);glVertex3f(6,-4.5,0);
            glVertex3f(5.6,-4,0);glVertex3f(6,-4,0);
            glVertex3f(5.8,-3.5,0);glVertex3f(6,-3.5,0);
            glVertex3f(5.9,-3,0);glVertex3f(6,-3,0);
            
            
        } glEnd();
        
        glBegin(GL_QUAD_STRIP); { //top stroke
            glVertex3f(-4,7,0);glVertex3f(-4,8,0);               
            glVertex3f(-2,7,0); glVertex3f(-2,8,0);

            glVertex3f(-2,7,0);glVertex3f(-2,8,0); //start curve
            glVertex3f(-1.75,6.7,0);glVertex3f(-1.75,8,0);//midle of the curve
            glVertex3f(-1.5,6.5,0);glVertex3f(-1.5,8,0);//end end

            glVertex3f(0,6.5,0);glVertex3f(0,8,0);//start
            glVertex3f(.25,6.7,0);glVertex3f(.25,8,0);//midle of the curve
            glVertex3f(.5,7,0);glVertex3f(.5,8,0); //end   

            glVertex3f(2.5,7,0);glVertex3f(2.5,8,0);
        } glEnd();

    }
    /**
     * Depth
     */
    glColor3f (0.5, 0.5, 0.5);
    glBegin(GL_QUAD_STRIP);{ //starting at the top leftmost point of the bottom part of the letter
        glVertex3f(-3.5,-5,0);glVertex3f(-3.5,-5,-1);
        glVertex3f(-2,-5,0);glVertex3f(-2,-5,-1);
           
        glVertex3f(-2,-5,0);glVertex3f(-2,-5,-1); //start bottom left curve
        glVertex3f(-1.75,-4.7,0);glVertex3f(-1.75,-4.7,-1);//midle of the curve
        glVertex3f(-1.5,-4.5,0);glVertex3f(-1.5,-4.5,-1);//end
        //start going up the main block//
        glVertex3f(-1.5,6.5,0);glVertex3f(-1.5,6.5,-1); // hits the curved bit top left
        glVertex3f(-1.75,6.7,0);glVertex3f(-1.75,6.7,-1);//midle of the curve
        glVertex3f(-2,7,0);glVertex3f(-2,7,-1); // finished curved

        glVertex3f(-4,7,0);glVertex3f(-4,7,-1);               
        glVertex3f(-4,8,0);glVertex3f(-4,8,-1); // top cover
        glVertex3f(2.5,8,0);glVertex3f(2.5,8,-1);
        glVertex3f(2.5,7,0);glVertex3f(2.5,7,-1);
        
        glVertex3f(.5,7,0);glVertex3f(.5,7,-1); //start of the top right curved bit
        glVertex3f(.25,6.7,0);glVertex3f(.25,6.7,-1);//midle of the curve
        glVertex3f(0,6.5,0);glVertex3f(0,6.5,-1);//end
        //start going down the main block
        glVertex3f(0,-4.5,0);glVertex3f(0,-4.5,0-1);//start curve
        glVertex3f(.25,-4.7,0);glVertex3f(.25,-4.7,-1);//midle of the curve
        glVertex3f(.5,-5,0);glVertex3f(.5,-5,-1); //end end
        //botom with upstroke
        glVertex3f(3.9,-5,0);glVertex3f(3.9,-5,-1);
        glVertex3f(4.4,-4.9,0);glVertex3f(4.4,-4.9,-1);
        glVertex3f(4.9,-4.8,0);glVertex3f(4.9,-4.8,-1);
        glVertex3f(5.3,-4.5,0);glVertex3f(5.3,-4.5,-1);
        glVertex3f(5.6,-4,0); glVertex3f(5.6,-4,-1);
        glVertex3f(5.8,-3.5,0);glVertex3f(5.8,-3.5,-1);
        glVertex3f(5.9,-3,0); glVertex3f(5.9,-3,-1);        
        //continue
        glVertex3f(6,-3,0);  glVertex3f(6,-3,-1);        
        glVertex3f(6,-3.5,0);glVertex3f(6,-3.5,-1);
        glVertex3f(6,-4,0);glVertex3f(6,-4,-1);
        glVertex3f(6,-4.5,0);glVertex3f(6,-4.5,-1);
        glVertex3f(5.9,-5,0);glVertex3f(5.9,-5,-1);
        glVertex3f(5.7,-5.9,0);glVertex3f(5.7,-5.9,-1);
        glVertex3f(3.9,-6,0);glVertex3f(3.9,-6,-1);
        //bottom strip and bottom left strip
        glVertex3f(-3.5,-6,0);glVertex3f(-3.5,-6,-1);
        glVertex3f(-3.5,-5,0);glVertex3f(-3.5,-5,-1);
    } glEnd();

    /**
     * Back
     */{
        glColor3f(0.0,1.0,0.0);
        glBegin(GL_QUAD_STRIP); { //Main block
            glVertex3f(0,-5,-1);glVertex3f(0,7,-1);
            glVertex3f(-1.5,-5,-1);glVertex3f(-1.5,7,-1);

        } glEnd();
        
        glBegin(GL_QUAD_STRIP); { //down stroke
            glVertex3f(-3.5,-5,-1);glVertex3f(-3.5,-6,-1);
            glVertex3f(-2,-5,-1);glVertex3f(-1,-6,-1);
            
            glVertex3f(-2,-5,-1);glVertex3f(-2,-6,-1); //start curve
            glVertex3f(-1.75,-4.7,-1);glVertex3f(-1.75,-6,-1);//midle of the curve
            glVertex3f(-1.5,-4.5,-1);glVertex3f(-1.5,-6,-1);//end end

            glVertex3f(0,-4.5,-1);glVertex3f(0,-6,-1);//end end
            glVertex3f(.25,-4.7,-1);glVertex3f(.25,-6,-1);//midle of the curve
            glVertex3f(.5,-5,-1);glVertex3f(.5,-6,-1); //start curve

            //dist entre cada X aumenta por 0.1 para cada ponto
            /**
             * 5.9 - 5.8 = 0.1
             * 5.8 - 5.6 = 0.2
             * 5.6 - 5.3 = 0.3
             * 5.3 - 4.9 = 0.4 etc
             **/
            glVertex3f(3.9,-5,-1);glVertex3f(3.9,-6,-1);
            glVertex3f(4.4,-4.9,-1);glVertex3f(5.7,-5.9,-1);
            glVertex3f(4.9,-4.8,-1);glVertex3f(5.9,-5,-1);
            glVertex3f(5.3,-4.5,-1);glVertex3f(6,-4.5,-1);
            glVertex3f(5.6,-4,-1);glVertex3f(6,-4,-1);
            glVertex3f(5.8,-3.5,-1);glVertex3f(6,-3.5,-1);
            glVertex3f(5.9,-3,-1);glVertex3f(6,-3,-1);
            
        } glEnd();
        
        glBegin(GL_QUAD_STRIP); { //top stroke
            glVertex3f(-4,7,-1);glVertex3f(-4,8,-1);               
            glVertex3f(-2,7,-1); glVertex3f(-2,8,-1);

            glVertex3f(-2,7,-1);glVertex3f(-2,8,-1); //start curve
            glVertex3f(-1.75,6.7,-1);glVertex3f(-1.75,8,-1);//midle of the curve
            glVertex3f(-1.5,6.5,-1);glVertex3f(-1.5,8,-1);//end end

            glVertex3f(0,6.5,-1);glVertex3f(0,8,-1);//end end
            glVertex3f(.25,6.7,-1);glVertex3f(.25,8,-1);//midle of the curve
            glVertex3f(.5,7,-1);glVertex3f(.5,8,-1); //start curve    

            glVertex3f(2.5,7,-1);glVertex3f(2.5,8,-1);
        } glEnd();
    }
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(750, 750);
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

