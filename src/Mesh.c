#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Mesh.h"

Mesh setMesh(GLfloat* verts, size_t vertSize, GLuint* indices, size_t indexSize, Shader shader, Texture texture) {
    useShader(shader);

    Mesh mesh;
    mesh.texture = texture;
    mesh.shader = shader;

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertSize, verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);

    /*
        Layout 0 => Vertex Coords
        Layout 1 => Vertex Colors
        Layout 2 => Texture Coords

        LAYOUT_INDEX, LAYOUT_SIZE, DATA_TYPE, NOMALIZED, OFFSET/STRIDE_LENGTH, POINTER?
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    printf("Mesh created with VAO: %d, VBO: %d, EBO: %d\n", mesh.VAO, mesh.VBO, mesh.EBO);

    return mesh;
}

void modifyMeshAttribf(Mesh mesh, const char* attribute, float value){
    //getting the uniform variable attribute to change in the shader
    GLuint uniID = glGetUniformLocation(mesh.shader.ID, attribute);
    glUniform1f(uniID, value);
}

void renderMesh(Mesh mesh, Camera camera, GLFWwindow* window, vec3 pos, GLsizei exeptedTriangles) {
    glm_vec3_copy(pos, mesh.pos);

    useShader(mesh.shader);

    Matrix(45.0f, 0.1f, 100.0f, &mesh.shader, "camMatrix", camera);

    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, mesh.pos);
    glUniformMatrix4fv(glGetUniformLocation(mesh.shader.ID, "model"), 1, GL_FALSE, (const GLfloat*)model);

    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, exeptedTriangles * 3, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

// void renderMeshInstanced(Mesh mesh, Camera camera, GLFWwindow* window, vec3 pos, GLsizei exeptedTriangles) {
//     glm_vec3_copy(pos, mesh.pos);

//     mat4 model;
//     glm_mat4_identity(model);
//     glm_translate(model, mesh.pos);
//     glUniformMatrix4fv(glGetUniformLocation(mesh.shader.ID, "model"), 1, GL_FALSE, (const GLfloat*)model);

//     Matrix(45.0f, 0.1f, 100.0f, &mesh.shader, "camMatrix", camera); //Camera camera

//     useShader(mesh.shader);
//     glActiveTexture(GL_TEXTURE0);
//     bindTexture(mesh.texture);
    
//     glBindVertexArray(mesh.VAO);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);

//     glDrawElements(GL_TRIANGLES, 3*exeptedTriangles, GL_UNSIGNED_INT, 0);

//     glBindVertexArray(0);
//     unBindTexture(mesh.texture);
// }


void deleteMesh(Mesh mesh) {
    glDeleteVertexArrays(1, &mesh.VAO);
    glDeleteBuffers(1, &mesh.VBO);
    glDeleteBuffers(1, &mesh.EBO);
}