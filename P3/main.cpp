#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gamma.cpp"

/******SIDES*******/
int operate = 0;

#define NOPER 0
#define FORWAD 1
#define BACK 2
#define LEFT 3
#define RIGHT 4
#define TOP 5
#define BOTTOM 6

/*************/
#define TITLE "Gamma 3D"
#define MAX_TIME_SECONDS 30

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput();

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
" FragColor = fragmentColor;\n"
"}\n\0";


unsigned int MatrixID;
glm::mat4 Model = glm::mat4(1.0f);
glm::mat4 View = glm::mat4(1.0f);
glm::mat4 Projection = glm::mat4(1.0f);
glm::mat4 MVP;

const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 900;
GLfloat red = 0.6f;
GLfloat green = 0.5f;
GLfloat blue = 0.1f;
GLfloat alpha = 1.0f;

GLuint colorbuffer;
unsigned int VBO, VAO, EBO;
unsigned int shaderProgram, vertexShader,fragmentShader;
GLFWwindow* window;

void changeCameraAndRotation(glm::vec3 eye, glm::vec3 target = glm::vec3(0,0,0), glm::vec3 up = glm::vec3(0,1,0)){
    View = glm::lookAt(eye,target,up);
    MVP = Projection * View * Model;
}

void vertex_data_init(){
    glEnableVertexAttribArray(1);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Model = glm::rotate(Model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    changeCameraAndRotation(glm::vec3(0,0,1));
    Projection = glm::ortho(-1.0f,1.0f,-1.0f,1.0f,0.0f,100.0f);
    MVP = Projection * View * Model;

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);   
}

void shader_setup(){
        //shader compile 
    // -----------
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for vertex shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders : puts together the vertex and the fragment shaders
    // into a "shader program object"
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for shader linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // delete shaders, we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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
    shader_setup();

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

        glBindVertexArray(VAO);
        // seeing as we only have a single VAO there's no need to bind
        // it every time, but we'll do so to keep things a bit more organized
    

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glDrawElements(GL_TRIANGLES, triangle_count ,GL_UNSIGNED_INT,0);
        // glBindVertexArray(0); // no need to unbind it every time 
        
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


void processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) { //Esquerda
        changeCameraAndRotation(glm::vec3(-1,0,0));
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { //Direita
        changeCameraAndRotation(glm::vec3(1,0,0));
    }
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) { //Frente
        changeCameraAndRotation(glm::vec3(0,0,1));
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { //Atras
        changeCameraAndRotation(glm::vec3(0,0,-1));
    }
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {//Cima
        changeCameraAndRotation(glm::vec3(0.0, 1.0f, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
    }
    if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {//Baixo
        changeCameraAndRotation(glm::vec3(0.0, -1.0f, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
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

 
