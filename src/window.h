#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#define WIDTH 2000
#define HEIGHT 900

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Mesh.h"

GLFWwindow* createWindowAndInitGl();
int clearFunc();

#endif