#ifndef BLOCK_H
#define BLOCK_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Mesh.h"

typedef struct {
    Texture texture;
    Shader shader;
    Mesh mesh;
} Block;

Block createBlock(const char* texture);
void placeBlock(Block block, vec3 pos, Camera camera, GLFWwindow* window);

#endif