/*
Em linux, para compilar:
$ gcc -o letraH letraH.c -lGL -lGLU -lglut -lm
*/
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PI 3.14159
float xdiff = 0.0f;
float ydiff = 0.0f;
float xrot = 0.0f;
float yrot = 0.0f;
static GLfloat spin = 0.0;
bool mouseDown = false;
bool moving = false;

typedef struct {
    double x,y,z;
} ve3f;
ve3f start;

void init(void)
{
    glClearColor (0.0, 0.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}

void spinDisplayPos(void)
{
    spin+=0.1;
    if (spin > 60.0)
        spin=spin-360.0; 
    glutPostRedisplay();
}

void spinDisplayNeg(void){
    spin-=0.1;
    if (spin < 60.0)
        spin=spin+360.0; 
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

void idle()
{
    if (!mouseDown) {
        xrot += 0.3f;
        yrot += 0.4f;
    }
    glutPostRedisplay();
}

void moveObject(int x, int y, int z, ve3f *b){

    double model[16],proj[16],rx,ry,rz;
    int view[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, model); //The params parameter returns 16 values: the modelview matrix on the top of the modelview matrix stack
    glGetDoublev(GL_PROJECTION_MATRIX, proj); //The params parameter returns 16 values: the projection matrix on the top of the projection matrix stack
    glGetIntegerv(GL_VIEWPORT, view); //The params parameter returns four values: the x and y window coordinates of the viewport, followed by its width and height

    gluUnProject(x,y,z,model,proj,view,&rx,&ry,&rz); //The gluUnProject function maps the specified window coordinates into object coordinates using modelMatrix, projMatrix, and viewport.
    //converting then input mouse coordinates to object coordinates as the mouse moves through space
    b[0].x = rx;
    b[0].y = ry;
    b[0].z = rz;
}

void moveShape(int x, int y) {
    moving = true; //bloquear todos os outros movimentos
    ve3f a;  
    moveObject(x,y,0,&a);
    start.x = a.x/5; //dividir para abrandar os movimentos devido a escala
    start.y = a.y/5;
    glutPostRedisplay();
}

void mouse(int button, int state) {
    switch (button) {
      case GLUT_LEFT_BUTTON:
        if (moving == false && state == GLUT_UP) {
	        glutIdleFunc(spinDisplayPos);
            moving = true;
        } else if( moving == true && state == GLUT_DOWN) {
            glutIdleFunc(NULL);
            moving = false;
        }   
        break;
      case GLUT_RIGHT_BUTTON:
        if (moving == false && state == GLUT_UP) {
	        glutIdleFunc(spinDisplayNeg);
            moving = true;
        } else if(moving == true && state == GLUT_DOWN ) {
            glutIdleFunc(NULL);
            moving = false;
        }
        break;
      default:
        break;
      }
    
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();  
    glLoadIdentity();
    glScalef(5.0, 5.0, 5.0);

    glRotatef(spin, 0.0, 1.0, 0.0); 
    glTranslated(start.x,-start.y,0);//grabs the change from mouse and applies to matrix

    glColor3f (0.0, 0.0, 0.0);
    /**
     * Front
     */
    {
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
    glColor3f (1.0, 1.0, 1.0);
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
    glColor3f (0.0, 0.0, 0.0);
    /**
     * Back
     */{
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
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(moveShape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

