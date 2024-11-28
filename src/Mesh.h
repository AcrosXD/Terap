#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "shader.h"
#include "texture.h"
#include "camera.h"

#ifndef MESH_H
#define MESH_H

typedef struct {
    GLuint VAO, VBO, EBO;
    Shader shader;
    Texture texture;
    //GLuint indexSize[];
    vec3 pos;
} Mesh;

Mesh setMesh(GLfloat* verts, size_t vertSize, GLuint* indices, size_t indexSize, Shader shader, Texture texture);

void modifyMeshAttribf(Mesh mesh, const char* attribute, float value);
void modifyMeshAttribMat4(Mesh mesh, const char* attribute, mat4 value);

void renderMesh(Mesh mesh, Camera camera, GLFWwindow* window, vec3 pos, GLsizei exeptedTriangles);
void deleteMesh(Mesh mesh);

#endif