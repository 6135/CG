#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "letras.cpp"

/******SHOWCASED LETTER*******/

#define DAVID GLFW_KEY_F1
#define VIVIANA GLFW_KEY_F2
#define DIOGO GLFW_KEY_F3
#define GUI GLFW_KEY_F4
#define RICHARD GLFW_KEY_F5
int current = DAVID;

/*************/
int rot=0;

#define TITLE "Letras 3D"
#define MAX_TIME_SECONDS 30

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput();

Objetcs symbols[5];

symbols[5]={"A58604","A61172","A61171","A61213","A61039"};

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 vertexColor;\n"
    "out vec3 fragmentColor;\n"
    "uniform mat4 MVP;\n"
    "void main()\n""{\n"
    "   gl_Position = MVP * vec4(aPos, 1.0);\n"
    "   fragmentColor = vertexColor;\n"
    "}\0";

// declare and define fshader, position in color vector declaration
// are RGBA from [0,1] simply in and out
const char *fragmentShaderSource = "#version 330 core\n"
    "in vec3 fragmentColor;\n;"
    "out vec3 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = fragmentColor;\n"
    "}\n\0";


unsigned int MatrixID, MatrixID2;

glm::mat4 View = glm::mat4(1.0f);
glm::mat4 Models[] = {
    glm::mat4(1.0f),    //F1
    glm::mat4(1.0f),    //F2
    glm::mat4(1.0f),    //F3
    glm::mat4(1.0f),    //F4
    glm::mat4(1.0f),    //F5
};
glm::mat4 ActiveModel = Models[DAVID-290];

glm::mat4 Projection = glm::mat4(1.0f);
glm::mat4 MVP;
glm::mat4 MVP1;

const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 900;
GLfloat red = 0.6f;
GLfloat green = 0.5f;
GLfloat blue = 0.1f;
GLfloat alpha = 1.0f;
GLfloat spinSpeed = 1.0f;

GLuint colorbuffer;
unsigned int VBOs[5];
unsigned int VAOs[5];
unsigned int david,viviana,diogo,gui,richard,VAO,VBO,VAO2;
unsigned int shaderProgram, vertexShader,fragmentShader;
GLFWwindow* window;

void changeCameraAndRotation(glm::vec3 eye, glm::vec3 target = glm::vec3(0,0,0), glm::vec3 up = glm::vec3(0,1,0)){
    View = glm::lookAt(eye,target,up);
    MVP = Projection * View * ActiveModel;
}

void Rotation(double rotate, float sp, glm::vec3 axis){
    rot+=rotate;
    ActiveModel = glm::rotate(ActiveModel, glm::radians(float(rot)*sp), axis);

    MVP = Projection * View * ActiveModel;
}

void vertex_data_init(){
    glEnableVertexAttribArray(1);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA61171), verticesA61171, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    ActiveModel = glm::rotate(ActiveModel, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    changeCameraAndRotation(glm::vec3(0.0f,0.0f,8.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
    Projection = glm::perspective(glm::radians(70.0f), 4.0f / 3.0f, 1.0f, 100.0f);

    MVP = Projection * View * ActiveModel;

    // glGenBuffers(1, &colorbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof( colorsA61171), colorsA61171, GL_STATIC_DRAW);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);
    // glEnableVertexAttribArray(0);
    
    // glEnableVertexAttribArray(1);

    //glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    glGenBuffers(1, &viviana);
    glBindBuffer(GL_ARRAY_BUFFER, viviana);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA61039), verticesA61039, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    MVP1 = Projection * View * ActiveModel; 
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
    

    for(int i = 0 ; i < 5; i++){
        symbols[0] = Object();
    }
    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);   
}

static unsigned int CompileShader(unsigned int type, const std::string& source){
     unsigned int id = glCreateShader(type);
     const char* src = source.c_str();
     glShaderSource(id, 1, &src, NULL);
     glCompileShader(id);

     int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

      if (!success){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char*)alloca(length * sizeof(char));      
          glGetShaderInfoLog(id, length, &length, message);
          std::cout << "ERROR::SHADER::"<< (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
      }

      return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
      unsigned int shaderProgram = glCreateProgram();
      unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
      unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

      glAttachShader(shaderProgram, vs);
      glAttachShader(shaderProgram, fs);
      glLinkProgram(shaderProgram);
      glValidateProgram(shaderProgram);

      glDeleteShader(vs);
      glDeleteShader(fs);

      return shaderProgram;
}

int glfw_create_window(){
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, TITLE, NULL,NULL);

    if (window == NULL)
    {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
    // glad: load all OpenGL function pointers
    // ---------------------------------------
     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
    }
    return 0;
}

int main()
{

     // glfw: initialize and configure
     // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES,8);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  
    // glfw window creation
    // --------------------
    int res = glfw_create_window();
    if(res == -1) return -1;
    vertex_data_init();
    shaderProgram = CreateShader(vertexShaderSource,fragmentShaderSource);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // render
        // ------
        processInput();
        
        //glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //grey rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   //green? rendering


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw our first triangle: using shader program
        glUseProgram(shaderProgram);

        
        // seeing as we only have a single VAO there's no need to bind
        // it every time, but we'll do so to keep things a bit more organized
    
        //glBindVertexArray(VAO);
        //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        //glDrawArrays(GL_TRIANGLES, 0, vertices_count_A61171);
        //
        ////glBindVertexArray(0);
        //glBindVertexArray(VAO2);
        //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
        //glDrawArrays(GL_TRIANGLES, 0, vertices_count_A61039);
        for(int i = 0; i < 5; i++){
            glBindVertexArray(symbols.VAO);
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, symbols.MVP[0][0]);
            glDrawArrays(GL_TRIANGLES, 0, vertices_count_A61171);
        }
        //; // no need to unbind it every time 
        
        /* glfw: swap buffers and poll IO events (keys pressed/released, 
        mouse moved etc.)
        --------------------------------------------------------------*/
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------        
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

/* sets color specified in arguments
-----------------------------------------------------------------------*/
void glSetColor(GLfloat r, GLfloat g, GLfloat b,GLfloat a){
  red = r;
  green = g;
  blue = b;
  alpha = a;
}

/* process all input: query GLFW whether relevant keys are pressed/released 
this frame and react accordingly 
-----------------------------------------------------------------------*/
int keyPressLock = 0;

void processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, DAVID)){
        current = DAVID;
    }
    if(glfwGetKey(window, VIVIANA)){
        current = VIVIANA;
    }
    if(glfwGetKey(window, DIOGO)){
        current = DIOGO;
    }
    if(glfwGetKey(window, GUI)){
        current = GUI;
    }
    if(glfwGetKey(window, RICHARD)){
        current = RICHARD;
    }
    if(glfwGetKey(window, GLFW_KEY_UP) && keyPressLock!= GLFW_KEY_UP){//Cima
        Rotation(10.0, 1, glm::vec3(1.0f, 0.0f, 0.0f)); 
        keyPressLock= GLFW_KEY_UP;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) && keyPressLock!= GLFW_KEY_DOWN) {//Baixo
        Rotation(-10.0, 1, glm::vec3(1.0f, 0.0f, 0.0f));
        keyPressLock= GLFW_KEY_DOWN;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT)) {//Direita
        Rotation(3.0, spinSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT)) {//Esquerda
        Rotation(-3.0, spinSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    
    if(glfwGetKey(window, GLFW_KEY_A)) {//Speed Up
        spinSpeed = (spinSpeed+0.005f)*(spinSpeed<10.0f);
        printf("%lf\n",spinSpeed);
    }
    if(glfwGetKey(window, GLFW_KEY_Z)) {//Slow down
        
        spinSpeed = (spinSpeed-0.005f)*(spinSpeed>0.0f);

        printf("%lf\n",spinSpeed);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE)){//Initial position
      
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)){//Move Letter
        
    }

}

/* glfw: whenever the window size changed (by OS or user resize) this
   callback function executes
   -------------------------------------------------------------------*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that
  // width and height will be significantly larger than specified on
  // retina displays.
  glViewport(0, 0, width, height);
}

 
class Objects {
    public:
        unsigned int VBO,VAO;
        glm::mat4 Model,View,Projection,MVP;
        string symbol;
        int vertices_count;
        Objects(string symbol,glm::mat4 Model,glm::mat4 View,glm::mat4 Projection,glm::mat4 MVP, float *vertices){
            string vertices = "vertices" + symbol;
            vertices_count = 

            glEnableVertexAttribArray(1);
            glGenVertexArrays(1, &this.VAO);
            glBindVertexArray(this.VAO);
            glGenBuffers(1, &this.VBO);
            glBindBuffer(GL_ARRAY_BUFFER, this.VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            this.symbol = symbol;
            this.Model = Model;
            this.View = View;
            this.Projection = Projection;
            this.MVP = MVP;
        }

        void setModel(glm::mat4 m) {
            Model = m;
            setMVP();
        }

        void setView(glm::mat4 v){
            View = v;
            setMVP();
        }
        
    private:
        void setMVP(){
            MVP = Projection * View * Model;
        }
}
    
