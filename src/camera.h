#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "shader.h"

#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

typedef struct {
    vec3 pos;
    vec3 orientation;
    vec3 up;

    int width;
    int height;

    float sensitivity;
    float speed;
} Camera;

Camera createCamera(int width, int height, vec3 pos);

void Matrix(float FOV, float nearPlane, float farPlane, Shader* shader, const char* uniform, Camera camera);
void Inputs(GLFWwindow* window, Camera camera);

#endif