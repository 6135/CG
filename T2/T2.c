#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "our_strings.h"
#include "importmodel.h"

#define PI 3.14159
#define ON 1
#define OFF 0
bool mouseDown = false;
double spinSpeed = 3;
int representation = 1, shading = 0, light = 1, antialiasing = 0; //menu labels
GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};
GLfloat size = 20.0f, tilt = 3.0f, spin = 0.0, angle, fAspect;

FILE *fp;
const char** objectNameArray;
const char** objectOutHArray;
const char** objectOutCArray;
int objects;
//Model* objectsArray;
int objectsNumber;

void init(void){	
	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );	

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
	//menu for lighting
	if(light==ON){	
		luzAmbiente[0]=0.2;
		luzAmbiente[1]=0.2;
		luzAmbiente[2]=0.2;
		luzAmbiente[3]=1.0;
	}
	else{
		for (int i = 0; i < 4; ++i)
			luzAmbiente[i]=0;
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
    glPushMatrix();
    glRotatef(spin, 0, 1.0-sin(spin), 0); 
    glColor3f(0.0f, 0.0f, 1.0f);
    
    //
    if (representation==ON)
    	glutSolidTeapot(size);
    else
    	glutWireTeapot(size);
        
    glScalef(1.0, 1.0, 1.0);           
    glPopMatrix();
    glutSwapBuffers();
    // Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	
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

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
    gluPerspective(angle,fAspect,0.4,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
    gluLookAt(0,80,200, 0,0,0, 0,1,0);
}

void reshape(int w, int h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

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
                     representation = OFF;
                     break;
            case 1:
                     representation = ON;
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
    glutAddMenuEntry("On",0);
    glutAddMenuEntry("Off",1);

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
    if(key == GLUT_KEY_LEFT) {
        //glutIdleFunc(spinDisplayAntiClockWise); //spins anti clockwise
        spinDisplayAntiClockWise();
    }
    if(key == GLUT_KEY_RIGHT) {
        //glutIdleFunc(spinDisplayClockWise);   	//spins clockwise
        spinDisplayClockWise();
    }
    if(key == GLUT_KEY_UP) {
       glRotatef(-tilt, 1-sin(tilt), 0, 0);			//tilt up
    }
    if(key == GLUT_KEY_DOWN) {
        glRotatef(+tilt, 1+sin(tilt), 0, 0);			//tilt down
    }
    glutPostRedisplay();

}

//deals with normal keys (low key segregation in my opnion)
void NormalKeyHandler (unsigned char key, int x, int y)
{
    if (key == 'z' && spinSpeed>0)//spins slower
        spinSpeed-=0.02;
    else if (key == 'a')		//spins faster
        spinSpeed+=0.02;
    else if(key == 27)
      	exit (0);	
    else if(key == 43){ // Zoom-in
		angle -= 5;
		EspecificaParametrosVisualizacao();
	}
    else if(key == 45){ //zoom out
      	angle += 5;
      	EspecificaParametrosVisualizacao();
    }	
    
	glutPostRedisplay();
}
void printmodeData(float positions[][3], float texels[][2], float normals[][3], int faces[][12]){
    printf("P1: %f %f %f\nT1: %f %f\nN1: %f %f %f\nF1V1: %d %d %d",
        positions[0][0], positions[0][1], positions[0][2],
        texels[0][0], texels[0][1],
        normals[0][0], normals[0][1], normals[0][2],
        faces[0][0], faces[0][1], faces[0][2]
    );
}
void modelData(Model a, char* filepath){
    float positions[a.positions][3];    // XYZ
    float texels[a.texels][2];          // UV
    float normals[a.normals][3];        // XYZ
    int faces[a.faces][12];              // PTN PTN PTN PTN
    extractOBJdata(filepath, positions, texels, normals, faces);
    printmodeData(positions,texels,normals,faces);
}

int main(int argc, char** argv)
{
    objectNameArray = malloc(1000*sizeof(char*));
    objectOutHArray = malloc(1000*sizeof(char*));
    objectOutCArray = malloc(1000*sizeof(char*));
    objectsNumber = form_data("objectList.txt",objectNameArray,objectOutHArray,objectOutCArray);

    Model a = get_object_info("cube.obj");
    //model_info_print(a);
    modelData(a,"cube.obj");
    //to_format(objectNameArray[0],".obj");
    //printf("%s",objectNameArray[0]);

    //our_strings.c importmodel.c
    /*glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutSpecialFunc(TeclasEspeciais); 
    glutKeyboardFunc (NormalKeyHandler);
    glutMainLoop();*/
    return 0;
}