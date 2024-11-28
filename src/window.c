#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "shader.h"

GLFWwindow* window;

GLFWwindow* createWindowAndInitGl(){

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Terap", NULL, NULL);
  glfwMakeContextCurrent(window);
  if (window == 0){
    printf("Failed to create OpenGL window !");
    glfwTerminate();
  }

  int version = gladLoadGL();
  if (version == 0){
    printf("Failed to init OpenGL context\n");
  }
  glViewport(0, 0, WIDTH, HEIGHT);
  glEnable(GL_DEPTH_TEST); 
  glEnable(GL_CULL_FACE);

  printf("Loaded OpenGL ! YAY !\n");
  
  return window;
}

int clearFunc(){
    glfwDestroyWindow(window);
    glfwTerminate();
}