#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "stb_image.h"

typedef struct {
    GLuint ID;
    const char* image;
    GLenum textureType;
    GLenum slot;
    GLenum format;
    GLenum pixelType;
} Texture;

Texture createTexture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType);

void textureUnit(Shader shader, const char* uniformn, GLuint unit);

void deleteTexture(Texture texture);
void unBindTexture(Texture texture);
void bindTexture(Texture texture);

#endif