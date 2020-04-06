
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


#include "our_strings.h"
#include "our_strings.c"

#include "importmodel.h"
#include "importmodel.c"

#include "resources/house.h"
#include "resources/house.c"

#include "resources/balloon.h"
#include "resources/balloon.c"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define NELEMS(x) (sizeof(x)/sizeof(x[0]))
#define PI 3.14159
#define ON 1
#define OFF 0
bool mouseDown = false;
double spinSpeed = 3;
int representation = 1, shading = 0, light = 1, antialiasing = 0, hangtime = 500; //menu labels
GLfloat size = 20.0f, tilt = 0.0f, spin = 0.0, angle, fAspect;
GLint delta = 301, balloonY = 0, balloonMov = 1;
GLfloat camera[] = {0.0f, 0.0f, 200.0f};

FILE *fp;
const char** objectNameArray;
const char** objectPathArray;
const char** objectOutHArray;
const char** objectOutCArray;
const char** objectTextArray;
int objects;
//Model* objectsArray;
int objectsNumber;
GLfloat testY = 5;
void andTheBalloonGoesAndUpAndDown_UpAndDown_UpAndDown(){
    balloonY+=balloonMov;
    if(balloonY>=delta-1){
        balloonMov = -1;
    }else if(balloonY<=0){
        balloonMov = 1;
    }
}

void upAndDown_Helper(int i){
    //printf("Y: %d\n",balloonY);
    if(balloonY>=delta-1 || (balloonY==3 && balloonMov==-1)){
        //printf("Time to wait!");
        if(i<=0 ) {
            balloonY-=2;
            glutTimerFunc(5,upAndDown_Helper,hangtime);
        }
        else {
           // printf("I: %d\n",i);
            glutTimerFunc(5,upAndDown_Helper,--i);
        }
    } else {
        andTheBalloonGoesAndUpAndDown_UpAndDown_UpAndDown();
        glutPostRedisplay();
        glutTimerFunc(5,upAndDown_Helper, i);
    }
}

void init(void){
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);


    glLightfv(GL_LIGHT0, GL_POSITION, light_position);	

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela será preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	
	
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
	//Habilita antialising
	glEnable(GLUT_MULTISAMPLE);
    angle=45;
    //glClearColor (1, 1.0, 1.0, 1.0);


    
}

// Função callback chamada para fazer o desenho
void display(void)
{
    glPushMatrix();
    //menu for lighting
    if(light==ON){	
		glEnable(GL_LIGHTING);
	   	glEnable(GL_LIGHT0);
	   	glEnable(GL_DEPTH_TEST);
	}
	else{
		glDisable(GL_LIGHTING);
	   	glDisable(GL_LIGHT0);
	   	glDisable(GL_DEPTH_TEST);
	}

	//menu for shading
	if (shading==ON)
		glShadeModel (GL_FLAT);
	else
		glShadeModel(GL_SMOOTH);
	
	//menu for antialiasing
	if (antialiasing==ON){
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glEnable(GLUT_MULTISAMPLE);
	}
	else{
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDisable(GLUT_MULTISAMPLE);
	}
		
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT, GL_FILL);
    glRotatef(spin, 0, 1.0-sin(spin), 0); 
    glRotatef(tilt, 1-sin(tilt), 0, 0);
    glTranslatef(0,balloonY,0);
    
    //
    if ((representation==ON))
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    render_object_balloon();
    glScalef(0.25, 0.25, 0.25);           
    glPopMatrix();
    //glPushMatrix();
    render_object_house();
    //glPopMatrix();
    glutSwapBuffers();
	
}

void spinDisplayClockWise(void)
{
    spin=spin+spinSpeed;
    if (spin > 360.0)
        spin=spin-360.0; 
    glutPostRedisplay();
}

void spinDisplayAntiClockWise(void)
{
    spin=spin-spinSpeed;
    if (spin < 0)
        spin=spin+360.0; 
    glutPostRedisplay();
}

void tiltDisplay(int downUp){
    if(downUp == 1){
        tilt+=spinSpeed;
        if(tilt > 360)
            tilt-=360;
        //tilt*=downUp;
    } else if(downUp == -1){
         tilt-=spinSpeed;
        if(tilt < 0)
            tilt+=360;
        //tilt*=downUp;        
    }
    glutPostRedisplay();
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
    //printf("angleVision: %f",angle);
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
    gluPerspective(angle,fAspect,10,10000);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
    gluLookAt(camera[0],camera[1],camera[2], 0,0,0, 0,1,0);
}

void reshape(int w, int h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) 
        h = 1;

	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void MenuPrincipal(){}

//representation menu (flat/wireframe)
void MenuRepresentation(int op)
{
   switch(op) {
            case 0:
                     representation = ON;
                     break;
            case 1:
                     representation = OFF;
                     break;
    }
    glutPostRedisplay();
}  

//lighting menu 
void MenuIluminacao(int op)
{
   switch(op) {
            case 0:
                     light = OFF;
                     break;
            case 1:
                     light = ON;
                     break;
    }
    glutPostRedisplay();
}  

//shading menu
void MenuShading(int op)
{
   switch(op) {
            case 0:
                     shading = OFF;
                     break;
            case 1:
                     shading = ON;
                     break;
    }
    glutPostRedisplay();
} 

//antialising menu
void MenuAntialiasing(int op)
{
   switch(op) {
            case 0:
                     antialiasing = OFF;
                     break;
            case 1:
                     antialiasing = ON;
                     break;
    }
    glutPostRedisplay();
} 


// Criacao do Menu
void CriaMenu() 
{
    int menu, representationMenu, iluminacaoMenu, shadingMenu, antialiasingMenu;

    representationMenu = glutCreateMenu(MenuRepresentation);
    glutAddMenuEntry("Flat",0);
    glutAddMenuEntry("Wireframe",1);
 

    iluminacaoMenu = glutCreateMenu(MenuIluminacao);
    glutAddMenuEntry("On",1);
    glutAddMenuEntry("Off",0);

    shadingMenu = glutCreateMenu(MenuShading);
    glutAddMenuEntry("On",0);
    glutAddMenuEntry("Off",1);

    antialiasingMenu = glutCreateMenu(MenuAntialiasing);
    glutAddMenuEntry("On",0);
    glutAddMenuEntry("Off",1);

    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Representacao",representationMenu);
    glutAddSubMenu("Iluminacao",iluminacaoMenu);
    glutAddSubMenu("Shading",shadingMenu);
    glutAddSubMenu("Antialiasing",antialiasingMenu);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


//deal with mouse          
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN) 
            CriaMenu();
         
    glutPostRedisplay();
}


// Função callback chamada para gerenciar eventos do teclado   
// para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciais(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) 
        spinDisplayAntiClockWise();
    else if(key == GLUT_KEY_RIGHT) 
        spinDisplayClockWise();
    else if(key == GLUT_KEY_UP) 
       tiltDisplay(-1);
    else if(key == GLUT_KEY_DOWN) 
       tiltDisplay(1);
    else if(key == GLUT_KEY_F1){
        angle=45;
    	camera[0]= 1000.0f; 
    	camera[1]= 0.0f;
    	camera[2]= 0.0f;
        EspecificaParametrosVisualizacao();
    } else if(key == GLUT_KEY_F2){
        angle=45;
    	camera[0]= -1000.0f; 
    	camera[1]= 0.0f;
    	camera[2]= 0.0f;
        EspecificaParametrosVisualizacao();
    } else if(key == GLUT_KEY_F3){
        angle=45;
    	camera[0]= 0.0f; 
    	camera[1]= 0.0f;
    	camera[2]= 1500.0f;
        EspecificaParametrosVisualizacao();
    } else if(key == GLUT_KEY_F4){
        angle=45;
    	camera[0]= 0.0f; 
    	camera[1]= 0.0f;
    	camera[2]= -1500.0f;
        EspecificaParametrosVisualizacao();
    } else if(key == GLUT_KEY_F5){
        angle=45;
    	camera[0]= 0.0f; 
    	camera[1]= -30.0f;
    	camera[2]= 1.0f;
        EspecificaParametrosVisualizacao();
    } else if(key == GLUT_KEY_F6){
        angle=45;
    	camera[0]= 0.0f; 
    	camera[1]= 1000.0f;
    	camera[2]= 1.0f;
        EspecificaParametrosVisualizacao();
    }
    glutPostRedisplay();

}

//deals with normal keys (low key segregation in my opnion)
void NormalKeyHandler (unsigned char key, int x, int y)
{
    if (key == 'z' && spinSpeed>0)//spins slower
        spinSpeed-=1;
    else if (key == 'a')		//spins faster
        spinSpeed+=1;
    else if(key == 27)
      	exit (0);	
    else if(key == 43){ // Zoom-in
		angle -= 5;
		EspecificaParametrosVisualizacao();
	}
    else if(key == 45){ //zoom out
      	angle += 5;
      	EspecificaParametrosVisualizacao();
    } else  if(key == 'p') {
        camera[1]+=-5.0f;
        EspecificaParametrosVisualizacao();
    }
    //printf("%f\n",spinSpeed);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    objectNameArray = malloc(100*sizeof(char*));
    objectPathArray = malloc(100*sizeof(char*));
    objectOutHArray = malloc(100*sizeof(char*));
    objectOutCArray = malloc(100*sizeof(char*));
    objectTextArray = malloc(100*sizeof(char*));
    objectsNumber = form_data("objectList.txt",objectNameArray,objectPathArray,objectOutHArray,objectOutCArray,objectTextArray);
    printf("formed!\n");
    Model modelArray[objectsNumber];
    for(int i = 0; i<objectsNumber;i++){
        modelArray[i]=get_object_info(objectPathArray[i],objectNameArray[i],objectTextArray[i]);
        printf("MATERIALS: %d\n",modelArray[i].materials);
        modelData(modelArray[i],objectPathArray[i],objectOutHArray[i],objectOutCArray[i],objectTextArray[i]);
    }

    //to_format(objectNameArray[0],".obj");
    //to_format(objectOutCArray)
    //printf("%s",objectNameArray[0]);

    //our_strings.c importmodel.c Normalsballon.c
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutSpecialFunc(TeclasEspeciais); 
    glutKeyboardFunc (NormalKeyHandler);
    glutTimerFunc(5, upAndDown_Helper,hangtime);
    glutMainLoop();
    return 0;
}