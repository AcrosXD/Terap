#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct {
    GLuint ID;
} Shader;

Shader createNewShader(const char* vertexPath, const char* fragmentPath);
void useShader(Shader shader);
void deleteShader(Shader shader);

#endif