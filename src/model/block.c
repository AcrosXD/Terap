#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "block.h"
#include "../Mesh.h"
#include "../texture.h"

Block createBlock(const char* textureFile){
    GLuint blockIndices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLfloat blockVerts[] = {
        0.5f, 0.5f, 0.0f, 0.93f, 0.12f, 0.56f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.93f, 0.12f, 0.56f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.93f, 0.12f, 0.56f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.93f, 0.12f, 0.56f, 1.0f, 0.0f
    };

    Shader blockShader = createNewShader("block.vert", "block.frag");
    Texture texture = createTexture(textureFile, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Mesh mesh = setMesh(blockVerts, sizeof(blockVerts), blockIndices, sizeof(blockIndices), blockShader, texture);

    return (Block){texture, blockShader, mesh};
}

void placeBlock(Block block, vec3 pos, Camera camera, GLFWwindow* window){
    renderMesh(block.mesh, camera, window, pos, 2);
}