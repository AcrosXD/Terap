#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shader.h"

static char* readFile(const char* filename) {
    char totalFilePath[1024] = "C:\\Users\\rayan\\Terap\\src\\shaders\\";
    char filePath[1024];
    strncpy(filePath, totalFilePath, sizeof(filePath) - 1);
    filePath[sizeof(filePath) - 1] = '\0';
    strncat(filePath, filename, sizeof(filePath) - strlen(filePath) - 1);
    FILE* file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filePath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "Could not allocate memory for file %s\n", filePath);
        fclose(file);
        return NULL;
    }

    memset(buffer, 0, length + 1);

    //SUM VALIDATION BC WE ARE NEVER SURE
    size_t bytesRead = fread(buffer, 1, length, file);
    if (bytesRead != length) {
        fprintf(stderr, "Warning: Number of bytes read (%zu) does not match expected length (%ld)\n", bytesRead, length);
    }
    buffer[length] = '\0';

    fclose(file);

    return buffer;
}

static void checkCompileErrors(GLuint shader, const char* type) {
    GLint success;
    GLchar infoLog[1024];
    if (strcmp(type, "PROGRAM") != 0) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n", type, infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n", type, infoLog);
        }
    }
}

Shader createNewShader(const char* vertexPath, const char* fragmentPath) {
    Shader shader;
    char* vertexCode = readFile(vertexPath);
    char* fragmentCode = readFile(fragmentPath);

    if (!vertexCode || !fragmentCode) {
        shader.ID = 0;
        return shader;
    }

    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const GLchar* const*)&vertexCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const GLchar* const*)&fragmentCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    shader.ID = glCreateProgram();
    glAttachShader(shader.ID, vertex);
    glAttachShader(shader.ID, fragment);
    glLinkProgram(shader.ID);
    checkCompileErrors(shader.ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free(vertexCode);
    free(fragmentCode);

    return shader;
}

void useShader(Shader shader) {
    glUseProgram(shader.ID);
}

void deleteShader(Shader shader) {
    glDeleteProgram(shader.ID);
}