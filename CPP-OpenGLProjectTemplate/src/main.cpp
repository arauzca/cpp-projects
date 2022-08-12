// Include standard headers
#include <iostream>

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

int main()
{
  // Initialize GL context and O/S window by using the GLFW helper library
  if(!glfwInit())
  {
    std::cerr << "Error: Failed to initialize GLFW\n";
    return 1;
  }
  
  // Set the properties of the window
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

  // Open a window and create its OpenGL context
  GLFWwindow* window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
  if(!window){
    std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
  
  // Start GLEW extension handler
  glewExperimental=true;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW\n";
    return 1;
  }
  
  // Get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); // Get renderer string
  const GLubyte* version  = glGetString(GL_VERSION);  // Get version string
  std::cout << "Renderer: " << renderer << "\n";
  std::cout << "OpenGL version supported " << version << "\n";
  
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  do{
      // Draw nothing, see you in tutorial 2 !
      glClear( GL_COLOR_BUFFER_BIT );

      // Swap buffers
      glfwSwapBuffers(window);
      glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0 );
  
  return 0;
}
