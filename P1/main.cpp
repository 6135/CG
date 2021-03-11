#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#define TITLE "Janela Temporizada"
#define MAX_TIME_SECONDS 30

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 400;
const unsigned int SCR_HEIGHT = 400;
GLfloat red = 0.2f;
GLfloat green = 0.2f;
GLfloat blue = 0.2f;
GLfloat alpha = 1.0f;
int main()
{

  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  
  // glfw window creation
  // --------------------
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, TITLE, NULL,NULL);

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

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
    {
      glClearColor(red,green,blue, alpha);
      glClear(GL_COLOR_BUFFER_BIT);

      if( ((int) glfwGetTime()) >= MAX_TIME_SECONDS)
        glfwSetWindowShouldClose(window, true);

      // input
      // -----
      processInput(window);
      
      /* glfw: swap buffers and poll IO events (keys pressed/released, 
	 mouse moved etc.)
	 --------------------------------------------------------------*/
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}
/* sets color specified in arguments
-----------------------------------------------------------------------*/
void glSetClearColor(GLfloat r, GLfloat g, GLfloat b,GLfloat a){
  red = r;
  green = g;
  blue = b;
  alpha = a;
}

/* process all input: query GLFW whether relevant keys are pressed/released 
this frame and react accordingly 
-----------------------------------------------------------------------*/

void processInput(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
    glSetClearColor(1.0f,0.0f,0.0f,1.0f);
  }
  if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS){
    glSetClearColor(0.0f,1.0f,0.0f,1.0f);
  }
  if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS){
      glSetClearColor(0.0f,0.0f,1.0f,1.0f);
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

 
