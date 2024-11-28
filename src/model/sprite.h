#ifndef SPITE_H
#define SPITE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Mesh.h"

typedef struct {
    Texture texture;
    Shader shader;
    Mesh mesh;
} Sprite;

Sprite createSprite(const char* texture);
void drawSprite(Sprite block, vec3 pos, Camera camera, GLFWwindow* window);
void cleanSprite(Sprite block);

#endif