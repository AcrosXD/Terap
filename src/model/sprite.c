#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "sprite.h"
#include "../Mesh.h"
#include "../texture.h"

Sprite createSprite(const char* textureFile){
    GLuint spriteIndices[] = {
        0, 1, 2,
        2, 3, 0
    };
    GLfloat spriteVerts[] = {
        0.0f, 1.0f, 0.0f,   0.93f, 0.12f, 0.56f,    0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,   0.93f, 0.12f, 0.56f,    0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,   0.93f, 0.12f, 0.56f,    1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,   0.93f, 0.12f, 0.56f,    1.0f, 1.0f
    };

    Shader spriteShader = createNewShader("sprite.vert", "sprite.frag");
    Texture texture = createTexture(textureFile, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Mesh mesh = setMesh(spriteVerts, sizeof(spriteVerts), spriteIndices, sizeof(spriteIndices), spriteShader, texture);

    return (Sprite){texture, spriteShader, mesh};
}

void drawSprite(Sprite sprite, vec3 pos, Camera camera, GLFWwindow* window){
    renderMesh(sprite.mesh, camera, window, pos, 2);
}

void cleanSprite(Sprite sprite){
    deleteShader(sprite.shader);
    deleteMesh(sprite.mesh);
}