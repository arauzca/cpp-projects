#include <GL/gl3w.h>    // OpenGL headers
#include <GLFW/glfw3.h> // GLFW GUI library
#include <glm/glm.hpp>  // OpenGL Mathematics
#include <iostream>     // Standard iostreams objects

using namespace glm;

// Main procedure
int main(int argc, char* argv[])
{
  // Initialize GL context and O/S window by using the GLFW helper library
  if (!glfwInit())
  {
    std::cerr << "failed to initialize GLFW\n";
    return -1;
  }

  // Set the properties of the window
  glfwWindowHint(GLFW_SAMPLES, 4);                                // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL

  // Open a window and create its OpenGL context
  GLFWwindow *window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
  if (!window)
  {
    std::cerr << "failed to open GLFW window.\nVersion 3.3 might not be compatible.\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (gl3wInit() != GL3W_OK)
  {
    std:: cerr << "failed to initialize OpenGL.\n";
    return -1;
  }

  if (!gl3wIsSupported(3, 3))
  {
    std::cerr << "OpenGL 3.3 not supported\n";
    return -1;
  }

  // Get version info
  const GLubyte *renderer = glGetString(GL_RENDERER); // Get renderer string
  const GLubyte *version = glGetString(GL_VERSION);  // Get version string
  std::cout << "Renderer: " << renderer << "\n"
            << "OpenGL version supported " << version << "\n";

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  do
  {
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
